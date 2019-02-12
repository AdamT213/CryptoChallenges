#include <map>
#include <string>
#include <sstream>
#include <bitset>
#include <iostream>

class hexManip { 
  public:
  std::string hexToBinary(std::string text) {
    std::map <char, std::string> hexToBin;
    hexToBin['0'] = "0000"; hexToBin['1'] = "0001"; hexToBin['2']= "0010"; hexToBin['3'] = "0011"; hexToBin['4'] = "0100"; hexToBin['5'] = "0101"; hexToBin['6'] = "0110"; hexToBin['7'] = "0111"; hexToBin['8'] = "1000"; hexToBin['9'] = "1001"; hexToBin['a'] = "1010"; hexToBin['b'] = "1011"; hexToBin['c'] = "1100"; hexToBin['d'] = "1101"; hexToBin['e'] = "1110"; hexToBin['f'] = "1111";

    std::string bin;

    for (char c: text) {
      bin += hexToBin[c];
    }
    return bin;
  }

  std::string hexDecode(std::string text)  { 
    std::string bin = hexToBinary(text);
    std::stringstream ssResult(bin);
    std::string output;

    while(ssResult.good()) { 
      std::bitset<8> bits;
      ssResult >> bits;
      char c = char(bits.to_ulong());
      output += c;
    }
    std::cout << output << std::endl;
    return output;
    }
};