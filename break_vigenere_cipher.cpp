#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream>
#include <iso646.h>
#include <fstream>
#include "binaryManip.h" 
#include "hexManip.h" 
#include "informationTheory.h" 
#include "1byte_xor_cipher.cpp"
#include "repeating_key_xor.cpp"

using namespace std; 

string readfileAsString(string path) {

  string buffer; 
  ifstream infile(path);
  string line;
  
  while (getline(infile, line)) {
    buffer += line;
  }
  return buffer;
}

string break_vigenere_cipher(string text) { 
  vector<char> key = find_key(text); 
  return repeating_key_xor(text, key);
}

vector<char> find_key(string text) { 
  binaryManip manipulator; 
  string bin = manipulator.base64ToBinary(text); 
  int keysize;
  float bestEditDistance = INFINITY; 
  int bestScorer;
 
  for (keysize =2; keysize<41; ++keysize) {
    
    vector<string>  first4KeysizesWorthOfBytes; 
    string determineKeysize = bin; 
    
    for (int i=0; i<4; ++i) {
      
      string keysizeWorthOfBytes;

      for (int j=0; j<keysize; ++j) {
       
        char a = determineKeysize[j]; 
        
        for (int k=0; k<8; ++k) {
          bool b = (!!((a << k) & 0x80));  
          keysizeWorthOfBytes += b ? '1' : '0';
        }
      } 
      determineKeysize = determineKeysize.substr(keysize);
      first4KeysizesWorthOfBytes.push_back(keysizeWorthOfBytes);
    }
    
    int firstEditDistance = hammingDistance(first4KeysizesWorthOfBytes[0], first4KeysizesWorthOfBytes[1]);

    int secondEditDistance = hammingDistance(first4KeysizesWorthOfBytes[2], first4KeysizesWorthOfBytes[3]);

    float average = (firstEditDistance + secondEditDistance)/2.0;

    float normalized = average/(keysize * 1.0);

    if (normalized < bestEditDistance) {
      bestEditDistance = normalized; 
      bestScorer = keysize; 
    }
  }   
  vector<string> keysizeLengthBlocks; 

  while (bin.size()) {
    string keysizeLengthBlock; 
    for (int i=0; i<bestScorer; ++i) { 
      keysizeLengthBlock += bin[i];
    }
    keysizeLengthBlocks.push_back(keysizeLengthBlock);
    bin = bin.substr(bestScorer);
  } 
  vector<char> key; 
  for (int i=0; i<bestScorer; ++i) {
    string ithCharsOfKeysizeLengthBlocks;
    for (string s : keysizeLengthBlocks) {
      ithCharsOfKeysizeLengthBlocks += (s[i]);
    }
      char ithByteOfkey = decrypt_1byte_xor_cipher(ithCharsOfKeysizeLengthBlocks).first;
      key.push_back( ithByteOfkey);
  }
  return key;
}

int main() { 

    string text = readfileAsString("../../../Downloads/xoredBase64encryptedtext.txt");
    
    cout << find_key(text);
}


