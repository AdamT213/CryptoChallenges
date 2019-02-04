#include "hexManip.h"
#include <vector> 
#include <bitset> 
#include <sstream> 
#include <iso646.h>
#include <iostream>
#include <cmath>

using namespace std;

int chiSquaredScore(string text) {

  double total = text.size() * 1.0; 
  double Q = 0.0;

  // based on actual sample of 40,000 words. Frequency of punctuation and special chars is estimated, but ordered properly relative to letters and itself. Since each string is 34 chars and has one null char, set frequency of null char to 1/34 so it would not affect score;
  map <char, double> charsByFrequency; 
  charsByFrequency[' '] = .1692; charsByFrequency['e'] = .1202; charsByFrequency['t'] = .0910; charsByFrequency['a'] = .0812; charsByFrequency['o'] = .0768; charsByFrequency['i'] = .0731; charsByFrequency['n'] = .0695; charsByFrequency['s'] = .0628; charsByFrequency['r'] = .0602; charsByFrequency['h'] = .0592; charsByFrequency['d'] = .0432; charsByFrequency['l'] = .0398;
  charsByFrequency['\0'] = .0294; charsByFrequency['u'] = .0288; charsByFrequency['c'] = .0271; charsByFrequency['m'] = .0261; charsByFrequency['f'] = .0230; charsByFrequency['y'] = .0211; charsByFrequency['w'] = .0209;
  charsByFrequency['\r'] = .0206;  charsByFrequency['g'] = .0203; charsByFrequency['p'] = .0182; charsByFrequency['b'] = .0149; charsByFrequency[','] = .0144; 
  charsByFrequency['.'] = .0139; charsByFrequency['v'] = .0111; charsByFrequency['k'] = .0069; charsByFrequency['-'] = .0064;
  charsByFrequency['"'] = .0059; charsByFrequency['_'] = .0054;
  charsByFrequency['\''] = .0049; charsByFrequency['x'] = .0017; 
  charsByFrequency[')'] = .0016; charsByFrequency['('] = .0015;
  charsByFrequency[';'] = .0014; charsByFrequency['0'] = .0013; 
  charsByFrequency['1'] = .0012; charsByFrequency['q'] = .0011; charsByFrequency['j'] = .0010; charsByFrequency['='] = .0009; charsByFrequency['2'] = .0008; charsByFrequency[':'] = .0007;charsByFrequency['z'] = .0007; charsByFrequency['/'] = .0006;
  charsByFrequency['*'] = .0006; charsByFrequency['!'] = .0006;charsByFrequency['?'] = .0006; charsByFrequency['$'] = .0005;charsByFrequency['3'] = .0005; charsByFrequency['5'] = .0005;charsByFrequency['>'] = .0005; charsByFrequency['{'] = .0005;charsByFrequency['}'] = .0004; charsByFrequency['4'] = .0004;charsByFrequency['9'] = .0004; charsByFrequency['['] = .0004;charsByFrequency[']'] = .0004; charsByFrequency['8'] = .0004;charsByFrequency['6'] = .0003; charsByFrequency['7'] = .0003;charsByFrequency['\\'] = .0003; charsByFrequency['+'] = .0003;charsByFrequency['|'] = .0003; charsByFrequency['&'] = .0003;charsByFrequency['<'] = .0003; charsByFrequency['%'] = .0003;charsByFrequency['@'] = .0003; charsByFrequency['#'] = .0002;charsByFrequency['^'] = .0002; charsByFrequency['`'] = .0002;charsByFrequency['~'] = .0002;

  map <char, int> charsByAppearance; 
  charsByAppearance[' '] = 0; charsByAppearance['e'] = 0; charsByAppearance['t'] = 0; charsByAppearance['a'] = 0; charsByAppearance['o'] = 0; charsByAppearance['i'] = 0; charsByAppearance['n'] = 0; charsByAppearance['s'] = 0; charsByAppearance['r'] = 0; charsByAppearance['h'] = 0; charsByAppearance['d'] = 0; charsByAppearance['l'] = 0;
  charsByAppearance['\0'] = 0; charsByAppearance['u'] = 0; charsByAppearance['c'] = 0; charsByAppearance['m'] = 0; charsByAppearance['f'] = 0; charsByAppearance['y'] = 0; charsByAppearance['w'] = 0;charsByAppearance['\r'] = 0; charsByAppearance['g'] = 0; charsByAppearance['p'] = 0; charsByAppearance['b'] = 0; charsByAppearance[','] = 0; 
  charsByAppearance['.'] = 0; charsByAppearance['v'] = 0; charsByAppearance['k'] = 0; charsByAppearance['-'] = 0;
  charsByAppearance['"'] = 0; charsByAppearance['_'] = 0;
  charsByAppearance['\''] = 0; charsByAppearance['x'] = 0; 
  charsByAppearance[')'] = 0; charsByAppearance['('] = 0;
  charsByAppearance[';'] = 0; charsByAppearance['0'] = 0; 
  charsByAppearance['1'] = 0; charsByAppearance['q'] = 0; charsByAppearance['j'] = 0; charsByAppearance['='] = 0; charsByAppearance['2'] = 0; charsByAppearance[':'] = 0;charsByAppearance['z'] = 0; charsByAppearance['/'] = 0;
  charsByAppearance['*'] = 0; charsByAppearance['!'] = 0;charsByAppearance['?'] = 0; charsByAppearance['$'] = 0;charsByAppearance['3'] = 0; charsByAppearance['5'] = 0;charsByAppearance['>'] = 0; charsByAppearance['{'] = 0;charsByAppearance['}'] = 0; charsByAppearance['4'] = 0;charsByAppearance['9'] = 0; charsByAppearance['['] = 0;charsByAppearance[']'] = 0; charsByAppearance['8'] = 0;charsByAppearance['6'] = 0; charsByAppearance['7'] = 0;charsByAppearance['\\'] = 0; charsByAppearance['+'] = 0;charsByAppearance['|'] = 0; charsByAppearance['&'] = 0;charsByAppearance['<'] = 0; charsByAppearance['%'] = 0;charsByAppearance['@'] = 0; charsByAppearance['#'] = 0;charsByAppearance['^'] = 0; charsByAppearance['`'] = 0;charsByAppearance['~'] = 0;

  for (char c: text) {
    charsByAppearance[tolower(c)] ++;
  }

  for (char c: text) {
    double O = charsByAppearance[tolower(c)] * 1.0; 
    double E = charsByFrequency[tolower(c)] * total;
    double deviation = pow((O-E), 2.0)/E;
    Q += deviation;
  }

  return Q;

}

string decrypt_1btye_xor_cipher(string hex) {  
 
  hexManip manipulator;
  string bin = manipulator.hexToBinary(hex);
  vector<string> results;
  double bestScore = INFINITY;
  string bestScorer;

  for (int i = 0; i < 256; ++i) { 
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
    
    double Qscore = chiSquaredScore(f);

    // critical value for a distribution with n=25 degrees of freedom and a 5% margin for error;
    double critical_val = 37.6525;

    double score = abs(Qscore - critical_val);
    
    if (score < bestScore) {
      bestScore = score;
      bestScorer = f;
    }
  }
  return bestScorer;
}

int main() { 
  // 1.3
  cout << decrypt_1btye_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
} 

