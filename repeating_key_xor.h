#include <string>
#include <vector>
#include <sstream> 
#include "binaryManip.h"

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

std::string repeating_key_xor(std::string plain, std::vector<char> encryptChars) {
  std::vector<bool> bin;

  while (plain.size()) {
    
    char a = plain[0];
    
    for (int i=0; i<8; ++i) {
      bin.push_back(!!((a << i) & 0x80));
    }
    plain = plain.substr(1);
  }

  std::vector<std::vector<bool>> encryptBytes;
  for (char c: encryptChars) {
    std::vector<bool> d;
    for (int i=0; i<8; ++i) {
      d.push_back(!!((c << i) & 0x80));
    }
    encryptBytes.push_back(d);
  }

  int i=0;
  std::string Xored;
  
  while (bin.size()) {
    std::vector<bool> XorByte = encryptBytes[i];
    std::vector<bool> byteToXor;
    
    for (int j=0; j<8; ++j) {
      byteToXor.push_back(bin[j]);
    }
    
    for (int j=0; j<8; ++j) {
      bool b = byteToXor[j] ^ XorByte[j];
      Xored += b ? '1' : '0';
    }

    bin = slice(bin, 8, bin.size()-1);

    if (i == encryptBytes.size()-1) {
      i=0;
    }

    else {
      ++i;
    }
  }

  std::stringstream ssResult; 
  std::string process;
  binaryManip manipulator;

  while (Xored.size()) {
    
    for (int i=0; i<4; ++i) {
      process += Xored[i];
    }

    ssResult << manipulator.binaryToHex(process);

    Xored = Xored.substr(4);
    process = "";
  }

  return ssResult.str();
}