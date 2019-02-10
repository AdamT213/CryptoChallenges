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

pair <char, double> decrypt_1byte_xor_cipher(string hex) { 
  
  chiSquared statsify;
  hexManip manipulator;
  string bin = manipulator.hexToBinary(hex);
  vector<string> results;
  double bestScore = INFINITY;
  string bestScorer; 
  char bestScoringKey;

  vector<bool> determinant; 

  for (int i=0; i<bin.size(); ++i) { 
    bool b = bin[i] == '1';
      determinant.push_back(b);
  }

  for (int i=0; i<256; ++i) {
    vector<bool> b;
    string result;
    for (int j=0; j<8; ++j) {
      b.push_back(!!((i << j) & 0x80));
    }
    int padding = bin.size()/8;
    vector<bool> process;
    for (int k=0; k<padding; ++k) {
      for (bool c: b) {
        process.push_back(c);
      }
    } 

    for (int k=0; k<determinant.size(); ++k) {
      bool b = determinant[k] ^ process[k]; 
      result += b ? '1' : '0';
    } 

    stringstream ssResult(result);
    string output;

    while(ssResult.good()) {
      bitset<8> bits;
      ssResult >> bits;
      char c = char(bits.to_ulong());
      output += c;
    }
    results.push_back(output);
  }

  for (int i=0; i<256; ++i) { 
    
    double Qscore = statsify.scoreText(results[i]); 

    // critical value for a distribution with n=70 degrees of freedom and a 5% margin for error
    double critical_val = 90.5312;

    double score = abs(Qscore - critical_val);
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = results[i]; 
      bestScoringKey = char(i);
    }
  }
  cout << bestScorer << " " <<  bestScore << endl;
  return {bestScoringKey, bestScore};
}

vector<string> readfileOfStrings(string path) {

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
    
    double score = decrypt_1byte_xor_cipher(f).second;
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = f;
    }
  }
  cout << bestScorer << " " << endl;
  return bestScore;
}

int main() {
  cout << detect_xored_string(readfileOfStrings("../../../Downloads/60charstrings.txt"));

  // cout << decrypt_1byte_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").first << endl <<decrypt_1byte_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").second;
}

