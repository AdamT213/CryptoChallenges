#include <string> 
#include <vector>
#include <fstream>
#include <iostream> 
#include <cmath>
#include "hexManip.h"
#include "informationTheory.h"

using namespace std; 

static vector<string>  readFileOfStrings(const string& path) { 
  vector<string> strings; 
  ifstream infile(path);
  string line; 
  
  while (getline(infile, line)) {
      string  buffer;
      while (buffer.size() < 320) { 
          buffer += line;
      }
    strings.push_back(buffer);
  }
  return strings;
}  

pair<int, int> determineBlocksize(string& text) { 
    float bestEditDistance = INFINITY;
    int bestScorer;
    float bestScore;
    for (int blocksize = 16; blocksize < 40; blocksize += 8) { 
      vector<string> blocksizesWorthOfBytes; 
      string determineBlocksize = text; 
      int leftover = determineBlocksize.size() % blocksize;
      while (determineBlocksize.size() > leftover)
      {

        string blocksizeWorthOfBytes;

        for (int i = 0; i < blocksize; ++i)
        {

          char a = determineBlocksize[i];

          for (int j = 0; j < 8; ++j)
          {
            bool b = (!!((a << j) & 0x80));
            blocksizeWorthOfBytes += b ? '1' : '0';
          }
        }
        determineBlocksize = determineBlocksize.substr(blocksize);
        blocksizesWorthOfBytes.push_back(blocksizeWorthOfBytes);
        }
        int total = 0; 
        int numberOfEditDists = 0;
        for (int i=0; i<blocksizesWorthOfBytes.size()-1; i+=2){
          int editDistance = hammingDistance(blocksizesWorthOfBytes[i], blocksizesWorthOfBytes[i+1]); 
          total += editDistance; 
          numberOfEditDists++;
        }
        float average = total * 1.0/numberOfEditDists * 1.0; 
        float normalized = average/blocksize * 1.0; 
        if (normalized < bestEditDistance) {
          bestEditDistance = normalized;
          bestScorer = blocksize; 
          bestScore = normalized;
        }
      }
      return { bestScorer, bestScore };
}

string detect_AES128_in_ECB_cipher(vector<string>& strings)  { 
    hexManip decoder; 
    float lowestOverallEditDistance = INFINITY; 
    string bestScoringString; 
    for (string s: strings) {
        string raw = decoder.hexDecode(s); 
        int bestEditDistance = determineBlocksize(raw).second;
        if (bestEditDistance < lowestOverallEditDistance) {
          lowestOverallEditDistance = bestEditDistance;
          bestScoringString = s; 
        } 
    } 
    cout << endl << endl << endl << bestScoringString <<  endl << endl << endl;
    return bestScoringString;
}

int main() {
    vector<string> strings = readFileOfStrings("../../../Downloads/hexEncodedStrings.txt"); 
    detect_AES128_in_ECB_cipher(strings);
}