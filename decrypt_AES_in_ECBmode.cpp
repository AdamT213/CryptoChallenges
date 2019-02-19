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
void aes_decrypt(const unsigned char* key, const byte iv[BLOCK_SIZE], const secure_string& ctext, secure_string& rtext);

string readfileAsString(const string& path)
{
  string buffer;
  ifstream infile(path);
  string line;

  while (getline(infile, line))
  {
    buffer += line;
  }
  return buffer;
} 

void aes_decrypt(const unsigned char* key, const byte iv[BLOCK_SIZE], const string& ctext, secure_string& rtext) 
{
     EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_128_ecb(), NULL, key, iv);
    if (rc != 1)
      throw runtime_error("EVP_DecryptInit_ex failed");

      // Recovered text contracts upto BLOCK_SIZE
    rtext.resize(ctext.size());
    int out_len1 = (int)rtext.size();

    rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1, (byte*)&ctext[0] , (int)ctext.size());
    if (rc != 1)
      throw runtime_error("EVP_DecryptUpdate failed");
  
      int out_len2 = (int)rtext.size() - out_len1;
    rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw runtime_error("EVP_DecryptFinal_ex failed");
    
    // Set recovered text size now that we know it
    rtext.resize(out_len1 + out_len2);
}

int main()
{

  binaryManip manipulator; 
  string text = readfileAsString("../../../Downloads/ECBencrypted.txt");
  string bin = manipulator.base64ToBinary(text);
    
    // Load the necessary cipher
    EVP_add_cipher(EVP_aes_128_ecb());
    string ctext = bin;
    secure_string rtext; 
    byte iv[BLOCK_SIZE];
    gen_params(iv);
    unsigned char *key = (unsigned char *)"YELLOW SUBMARINE";
  
    aes_decrypt(key, iv, ctext, rtext);
    
    OPENSSL_cleanse(iv, BLOCK_SIZE);

    cout << "Recovered message:\n" << rtext << endl;

    return 0;
}

void gen_params(byte iv[BLOCK_SIZE])
{
    // would do the same thing for key if generating a random key
    int rc = RAND_bytes(iv, BLOCK_SIZE);
    if (rc != 1)
      throw runtime_error("RAND_bytes for iv failed");
}

