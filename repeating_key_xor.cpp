#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream>
#include <iso646.h>
#include "binaryManip.h"

using namespace std;

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

string repeating_key_xor(string plain, vector<char> encryptChars) {  
  vector<bool> bin;

  while (plain.size()) {
    
    char a = plain[0];
    
    for (int i=0; i<8; ++i) {
      bin.push_back(!!((a << i) & 0x80));
    }
    plain = plain.substr(1);
  }

  vector<vector<bool>> encryptBytes;
  for (char c: encryptChars) {
    vector<bool> d;
    for (int i=0; i<8; ++i) {
      d.push_back(!!((c << i) & 0x80));
    }
    encryptBytes.push_back(d);
  }

  int i=0;
  string Xored;
  
  while (bin.size()) {
    vector<bool> XorByte = encryptBytes[i];
    vector<bool> byteToXor;
    
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

  stringstream ssResult; 
  string process;
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

int main() {
  vector<char> ice = {'I', 'C', 'E'};
  string actual = repeating_key_xor("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", ice); 

  string expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  bool b = (actual == expected); 

  if (b) { 
    cout << "theyre fucking equal goddamit!";
  } 
  else {

    for (int i=0; i<expected.size(); ++i) { 
      if (actual[i] != expected[i]) { 
        cout << "position: " << i << " " << "should be: " << expected[i] << " " << "is: " << actual[i] << endl;
      }
    };
  }
}