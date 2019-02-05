#include <iostream> 
#include <string>
#include "binaryManip.h" 
#include "decrypt_1byte_xor_cipher.h"

using namespace std;

int main() {
  
  // 1.1
  // string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  // hexManip manipulator; 
  // binaryManip instigator;

  // string bin = manipulator.hexToBinary(hex);

  // string base64 = instigator.binaryToBase64(bin);

  // cout << base64; 

  // 1.3 
  decrypt_1byte_xor_cipher decryptor; 

  cout << decryptor.decrypt("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
  
}