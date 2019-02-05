#include "decrypt_1byte_xor_cipher.h"
#include <vector> 
#include <bitset> 
#include <sstream> 
#include <iso646.h>
#include <iostream>
#include <cmath> 
#include <fstream> 

using namespace std;

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
  decrypt_1byte_xor_cipher decryptor;
  
  for (auto f: samples) { 
    
    double score = decryptor.decrypt(f);
    
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