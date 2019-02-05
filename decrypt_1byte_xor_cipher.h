#include <vector> 
#include <bitset> 
#include <boost/dynamic_bitset.hpp>
#include <sstream> 
#include <iso646.h>
#include <iostream>
#include <cmath> 
#include "chiSquared.h" 
#include "hexManip.h"

class decrypt_1byte_xor_cipher { 
  
  public:
  double decrypt(std::string hex) { 
    
    chiSquared statsify;
    hexManip manipulator;
    std::string bin = manipulator.hexToBinary(hex);
    std::vector<std::string> results;
    double bestScore = INFINITY;
    std::string bestScorer;

    for (int i = 0; i < 256; ++i) {
      std::bitset<8> b(i);
      int padding = bin.size()/8;
      std::string process;

      for (int j=0; j < padding; ++j) {
        process += b.to_string();
      } 

      unsigned long n = process.size();

      // need to change size of bitset based on input since bitset size is read at compile time. May or not be a better way to do this
      std::bitset<240> result = std::bitset<240>(bin) ^ std::bitset<240>(process);
      
      std::stringstream ssResult(result.to_string());
      std::string output;

      while(ssResult.good()) {
            std::bitset<8> bits;
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

      double score = std::abs(Qscore - critical_val);
      
      if (score < bestScore) {
        bestScore = score;
        bestScorer = f;
      }
    }
    std::cout << bestScorer << std::endl;
    return bestScore;
  }
};

