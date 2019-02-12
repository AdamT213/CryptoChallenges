#include <vector>
#include <iostream>
#include <fstream> 
#include "hexManip.h"
#include "decrypt_1byte_xor_cipher.h"

using namespace std;

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

    hexManip manipulator;
    string bin = manipulator.hexToBinary(f);
    
    double score = decrypt_1byte_xor_cipher(bin).second;
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = f;
    }
  }
  cout << bestScorer << " " << endl;
  return bestScore;
}

int main() {

// 1.4
  cout << detect_xored_string(readfileOfStrings("../../../Downloads/60charstrings.txt"));

// 1.3
  hexManip manipulator;
  string hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  string bin = manipulator.hexToBinary(hex); 
  cout << decrypt_1byte_xor_cipher(bin).first << endl << decrypt_1byte_xor_cipher(bin).second;
}

