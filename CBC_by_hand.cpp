#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <limits>
#include "openssl/evp.h"
#include "openssl/rand.h"
 #include "openssl/crypto.h"
#include "binaryManip.h"

static const unsigned int BLOCK_SIZE = 32;

template <typename T>
struct zallocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address (reference v) const {return &v;}
    const_pointer address (const_reference v) const {return &v;}

    pointer allocate (size_type n, const void* hint = 0) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();
        return static_cast<pointer> (::operator new (n * sizeof (value_type)));
    }

    void deallocate(pointer p, size_type n) {
        OPENSSL_cleanse(p, n*sizeof(T));
        ::operator delete(p); 
    }
    
    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof (T);
    }
    
    template<typename U>
    struct rebind
    {
        typedef zallocator<U> other;
    };

    void construct (pointer ptr, const T& val) {
        new (static_cast<T*>(ptr) ) T (val);
    }

    void destroy(pointer ptr) {
        static_cast<T*>(ptr)->~T();
    }

#if __cpluplus >= 201103L
    template<typename U, typename... Args>
    void construct (U* ptr, Args&&  ... args) {
        ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
#endif
};

using namespace std; 
typedef unsigned char byte;
typedef basic_string<char, char_traits<char>, zallocator<char> > secure_string;
using EVP_CIPHER_CTX_free_ptr = unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;  

void gen_params(byte iv[BLOCK_SIZE]);
void aes_encrypt(const unsigned char* key, const byte iv[BLOCK_SIZE], const secure_string& ptext, secure_string& ctext);

void aes_encrypt(const unsigned char* key, const byte iv[BLOCK_SIZE], const string& ptext, secure_string& ctext) 
{
     EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_128_ecb(), NULL, key, iv);
    if (rc != 1)
      throw runtime_error("EVP_EncryptInit_ex failed");

     // Cipher text expands up to BLOCK_SIZE
    ctext.resize(ptext.size() +BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1, (byte*)&ptext[0] , (int)ptext.size());
    if (rc != 1)
      throw runtime_error("EVP_EncryptUpdate failed");
  
      int out_len2 = (int)ctext.size() - out_len1;
    rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw runtime_error("EVP_EncryptFinal_ex failed");
    
    // Set cipher text size now that we know it
    ctext.resize(out_len1 + out_len2);
}

int main()
{

  string ptext = "A nigga like me man, I love the game, I love the hustle man I be feeling like one of them ball player niggas you know Like Bird, Magic or something Yeah you know a nigga got dough, a nigga can leave the league But if I leave… the fans still gone love me man? I get love out here in harlem man I done sold coke on these streets man hash weed, heroine As long as niggas is feeling it, a nigga like me could hustle it That’s my gift in life A… you know?";
    
    // Load the necessary cipher
    unsigned char ciphertext[512];
    EVP_add_cipher(EVP_aes_128_ecb());
    secure_string ctext;
    byte iv[BLOCK_SIZE];
    gen_params(iv);
    unsigned char *key = (unsigned char *)"YELLOW SUBMARINE";
  
    aes_encrypt(key, iv, ptext, ctext);

    OPENSSL_cleanse(iv, BLOCK_SIZE);

    ofstream myfile;
    myfile.open ("./ECBenc.txt");
    myfile << ctext;
    myfile.close();

    // cout << "Encrypted message:\n" << ctext << endl;

    // Check output using decrypt_AES_in_ECBmode to make sure it matches ptext

    return 0;
}

void gen_params(byte iv[BLOCK_SIZE])
{
    // would do the same thing for key if generating a random key
    int rc = RAND_bytes(iv, BLOCK_SIZE);
    if (rc != 1)
      throw runtime_error("RAND_bytes for iv failed");
}

