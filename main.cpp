#include <iostream> 
#include <string> 
#include "hexManip.h"
#include "binaryManip.h"

int main() {
  
  // 1.1
  string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  hexManip manipulator; 
  binaryManip instigator;

  string bin = manipulator.hexToBinary(hex);

  string base64 = instigator.binaryToBase64(bin);

  cout << base64;
  
}