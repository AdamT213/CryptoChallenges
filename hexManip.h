#include <map>
#include <string> 
using namespace std;

class hexManip { 
  public:
  string hexToBinary(string text) {
    map <char, string> hexToBin;
    hexToBin['0'] = "0000"; hexToBin['1'] = "0001"; hexToBin['2']= "0010"; hexToBin['3'] = "0011"; hexToBin['4'] = "0100"; hexToBin['5'] = "0101"; hexToBin['6'] = "0110"; hexToBin['7'] = "0111"; hexToBin['8'] = "1000"; hexToBin['9'] = "1001"; hexToBin['a'] = "1010"; hexToBin['b'] = "1011"; hexToBin['c'] = "1100"; hexToBin['d'] = "1101"; hexToBin['e'] = "1110"; hexToBin['f'] = "1111";

    string bin;

    for (char c: text) { 
      bin += hexToBin[c];
    }
    return bin;
  } 
};