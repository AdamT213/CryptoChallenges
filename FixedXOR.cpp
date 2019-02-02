#include <sstream>
#include <bitset>
#include "binaryManip.h"
#include "hexManip.h"
#include <iso646.h>
#include <iostream>

using namespace std;

string FixedXOR(string s1, string s2) { 
  hexManip manipulator; 
  binaryManip manipulator2;
  string bin1 = manipulator.hexToBinary(s1);
  string bin2 = manipulator.hexToBinary(s2);

  bitset<144> result = bitset<144>(bin1) ^ bitset<144>(bin2);

  string binResult = result.to_string();

  stringstream ssResult; 
  string process;
 
  while (binResult.size()) {
    
    for (int i = 0; i < 4; ++i) { 
      process += binResult[i];
    } 

    ssResult << manipulator2.binaryToHex(process);

    binResult = binResult.substr(4, binResult.size()-1);
    process = "";
  }

  return ssResult.str();
} 

int main() { 
    // 1.2 
  string uno = "1c0111001f010100061a024b53535009181c", dos = "686974207468652062756c6c277320657965";

  cout << FixedXOR(uno, dos);
}