#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <iso646.h>
#include <cmath>
#include <iostream>
#include "chiSquared.h"

std::pair <char, double> decrypt_1byte_xor_cipher(std::string bin) { 
  
  chiSquared statsify;
  std::vector<std::string> results;
  double bestScore = INFINITY;
  std::string bestScorer; 
  char bestScoringKey;

  std::vector<bool> determinant; 

  for (int i=0; i<bin.size(); ++i) { 
    bool b = bin[i] == '1';
      determinant.push_back(b);
  }

  for (int i=0; i<256; ++i) {
    std::vector<bool> b;
    std::string result;
    for (int j=0; j<8; ++j) {
      b.push_back(!!((i << j) & 0x80));
    }
    int padding = bin.size()/8;
    std::vector<bool> process;
    for (int k=0; k<padding; ++k) {
      for (bool c: b) {
        process.push_back(c);
      }
    } 

    for (int k=0; k<determinant.size(); ++k) {
      bool b = determinant[k] ^ process[k];
      result += b ? '1' : '0';
    }

    std::stringstream ssResult(result);
    std::string output;

    while(ssResult.good()) {
      std::bitset<8> bits;
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

    double score = std::abs(Qscore - critical_val);
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = results[i];
      bestScoringKey = char(i);
    }  
  }
  std::cout << std::endl;
  return {bestScoringKey, bestScore};
}