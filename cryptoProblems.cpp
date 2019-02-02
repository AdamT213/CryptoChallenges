#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <iso646.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <bitset>

using namespace boost::archive::iterators;
using namespace std;

char binaryToHex(string bin) { 
   if (bin == "0000") return '0'; 
   else if (bin == "0001") return '1';
   else if (bin == "0010") return '2';
   else if (bin == "0011") return '3';
   else if (bin == "0100") return '4';
   else if (bin == "0101") return '5';
   else if (bin == "0110") return '6';
   else if (bin == "0111") return '7';
   else if (bin == "1000") return '8';
   else if (bin == "1001") return '9';
   else if (bin == "1010") return 'a';
   else if (bin == "1011") return 'b';
   else if (bin == "1100") return 'c';
   else if (bin == "1101") return 'd';
   else if (bin == "1110") return 'e';
   else if (bin == "1111") return 'f'; 
}

string hexToBinary(string text) {
  map <char, string> hexToBin;
  hexToBin['0'] = "0000"; hexToBin['1'] = "0001"; hexToBin['2']= "0010"; hexToBin['3'] = "0011"; hexToBin['4'] = "0100"; hexToBin['5'] = "0101"; hexToBin['6'] = "0110"; hexToBin['7'] = "0111"; hexToBin['8'] = "1000"; hexToBin['9'] = "1001"; hexToBin['a'] = "1010"; hexToBin['b'] = "1011"; hexToBin['c'] = "1100"; hexToBin['d'] = "1101"; hexToBin['e'] = "1110"; hexToBin['f'] = "1111";

  string bin;

  for (char c: text) { 
    bin += hexToBin[c];
  }
  return bin;
}

string binaryToBase64(string text) { 
  
  typedef insert_linebreaks<base64_from_binary<transform_width<string::const_iterator,6, 1>>, 64> it_base64_t;
  unsigned int writePadChars = (3-text.length()%3)%3;
  string base64(it_base64_t(text.begin()),it_base64_t(text.end()));
  base64.append(writePadChars,'=');
  
  return base64;
}

string FixedXOR(string s1, string s2) { 
  
  string bin1 = hexToBinary(s1);
  string bin2 = hexToBinary(s2);

  bitset<144> result = bitset<144>(bin1) ^ bitset<144>(bin2);

  string binResult = result.to_string();

  stringstream ssResult; 
  string process;
 
  while (binResult.size()) {
    
    for (int i = 0; i < 4; ++i) { 
      process += binResult[i];
    } 

    ssResult << binaryToHex(process);

    binResult = binResult.substr(4, binResult.size()-1);
    process = "";
  }

  return ssResult.str();
} 

int frequencyScore(string text) { 
  // based on actual sample of 40,000 words
  int score = 0;

  map <char, int> lettersByFrequency; 
  lettersByFrequency['e'] = 21912; lettersByFrequency['t'] = 16587;
  lettersByFrequency['a'] = 14810; lettersByFrequency['o'] = 14003;
  lettersByFrequency['i'] = 13318; lettersByFrequency['n'] = 12666;
  lettersByFrequency['s'] = 11450; lettersByFrequency['r'] = 10977;lettersByFrequency['h'] = 10795; lettersByFrequency['d'] = 7874;lettersByFrequency['l'] = 7253; lettersByFrequency['u'] = 5246;lettersByFrequency['c'] = 4943; lettersByFrequency['m'] = 4761;lettersByFrequency['f'] = 4200; lettersByFrequency['y'] = 3853;lettersByFrequency['w'] = 3819; lettersByFrequency['g'] = 3693;lettersByFrequency['p'] = 3316; lettersByFrequency['b'] = 2715;lettersByFrequency['v'] = 2019; lettersByFrequency['k'] = 1257;lettersByFrequency['x'] = 315; lettersByFrequency['q'] = 205;lettersByFrequency['j'] = 188; lettersByFrequency['z'] = 128;

  for (char c: text) { 
    if (lettersByFrequency[tolower(c)]) { 
      score += lettersByFrequency[tolower(c)];
    } 
  }
  return score;
}

string decrypt_1btye_xor_cipher(string hex) {  

  string bin = hexToBinary(hex);
  vector<string> results; 
  int maxScore = 0; 
  string maxScorer;

  for (int i = 0; i < 128; ++i) { 
    bitset<8> b(i);
    int padding = bin.size()/8;
    string process;

    for (int j=0; j < padding; ++j) { 
      process += b.to_string();
    }

    bitset<144> result = bitset<144>(bin) ^ bitset<144>(process);
    
    stringstream ssResult(result.to_string());
    string output; 

    while(ssResult.good())
      {
          bitset<8> bits;
          ssResult >> bits;
          char c = char(bits.to_ulong());
          output += c;
      }
    results.push_back(output);
  }

  for (auto f: results) { 
    int score = frequencyScore(f);
    if (score > maxScore) {
      maxScore = score;
      maxScorer = f;
    }
  }
  return maxScorer;
}

int main() {
  
  // 1.1
  // string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  // string bin = hexToBinary(hex);

  // string base64 = binaryToBase64(bin);

  // cout << base64;
  
  // 1.2 
  // string uno = "1c0111001f010100061a024b53535009181c", dos = "686974207468652062756c6c277320657965";

  // cout << FixedXOR(uno, dos);
// 1.3
cout << decrypt_1btye_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
}
