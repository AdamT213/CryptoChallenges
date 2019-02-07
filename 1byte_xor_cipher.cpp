#include <vector> 
#include <bitset> 
#include <boost/dynamic_bitset.hpp>
#include <sstream> 
#include <iso646.h>
#include <iostream>
#include <cmath> 
#include <fstream>
#include "chiSquared.h" 
#include "hexManip.h" 

using namespace std;

double decrypt_1byte_xor_cipher(string hex) { 
  
  chiSquared statsify;
  hexManip manipulator;
  string bin = manipulator.hexToBinary(hex);
  vector<string> results;
  double bestScore = INFINITY;
  string bestScorer;

  for (int i=0; i<256; ++i) {
    bitset<8> b(i);
    int padding = bin.size()/8;
    string process;

    for (int j=0; j<padding; ++j) {
      process += b.to_string();
    }

    // need to change size of bitset based on input since bitset size is read at compile time. May or not be a better way to do this
    bitset<240> result = bitset<240>(bin) ^ bitset<240>(process);
    
    stringstream ssResult(result.to_string());
    string output;

    while(ssResult.good()) {
          bitset<8> bits;
          ssResult >> bits;
          char c = char(bits.to_ulong());
          output += c;
      }
    results.push_back(output);
  }

  for (auto f: results) { 
    
    double Qscore = statsify.scoreText(f); 

    // critical value for a distribution with n=70 degrees of freedom and a 5% margin for error
    double critical_val = 90.5312;

    double score = abs(Qscore - critical_val);
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = f;
    }
  }
  cout << bestScorer << endl;
  return bestScore;
}

vector<string> readfile(string path) {

  vector<string> strings; 
  ifstream infile(path);
  string line;
  
  while (getline(infile, line)) {
    strings.push_back(line);
  }

  return strings;
}

double detect_xored_string(vector<string> samples) { 
  
  double bestScore = INFINITY; 
  double score;
  string bestScorer;
  
  for (auto f: samples) { 
    
    double score = decrypt_1byte_xor_cipher(f);
    
    if (score < bestScore) { 
      bestScore = score;
      bestScorer = f;
    }
  } 
  cout << bestScorer << " " << endl;
  return bestScore;
}

int main() { 
  cout << detect_xored_string(readfile("../../../Downloads/60charstrings.txt"));
}

