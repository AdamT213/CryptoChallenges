#include "hexManip.h"
#include <vector> 
#include <bitset> 
#include <sstream> 
#include <iso646.h>
#include <iostream>

using namespace std;

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
 
  hexManip manipulator;
  string bin = manipulator.hexToBinary(hex);
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
  // 1.3
  cout << decrypt_1btye_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
}