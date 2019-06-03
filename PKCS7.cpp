#include <string> 
 #include <iostream>
 #include <sstream>

 std::string PKCS7_enc(std::string &plain, int &blockSize)  {
    int padBytes = blockSize - plain.size() % blockSize;
    if (plain.size() % blockSize == 0) { 
         padBytes = blockSize;
     }
    std::stringstream sstream;
    sstream << "/x" << (padBytes < 10 ? 0 : NULL) << std::hex << padBytes;
    std::string result = sstream.str();
    for (int i=0; i<padBytes; ++i) {
        plain += result;
    }
    return plain;
 }

 int main() {
     std::string in = "YELLOW SUBMARINE";
     int size = 20;
     std::cout << PKCS7_enc(in, size);
 }