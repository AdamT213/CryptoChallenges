#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iso646.h>
#include <fstream>
#include "hexManip.h"
#include "informationTheory.h"
#include "decrypt_1byte_xor_cipher.h"
#include "repeating_key_xor.h"

using namespace std;

string readfileAsString(string path)
{

  string buffer;
  ifstream infile(path);
  string line;

  while (getline(infile, line))
  {
    buffer += line;
  }
  return buffer;
}

vector<char> find_key(string text)
{
  int keysize;
  float bestEditDistance = INFINITY;
  int bestScorer;

  for (keysize = 2; keysize < 41; ++keysize)
  {

    vector<string> first20KeysizesWorthOfBytes;
    string determineKeysize = text;

    for (int i = 0; i < 40; ++i)
    {

      string keysizeWorthOfBytes;

      for (int j = 0; j < keysize; ++j)
      {

        char a = determineKeysize[j];

        for (int k = 0; k < 8; ++k)
        {
          bool b = (!!((a << k) & 0x80));
          keysizeWorthOfBytes += b ? '1' : '0';
        }
      }
      determineKeysize = determineKeysize.substr(keysize);
      first20KeysizesWorthOfBytes.push_back(keysizeWorthOfBytes);
    }

    int firstEditDistance = hammingDistance(first20KeysizesWorthOfBytes[0], first20KeysizesWorthOfBytes[1]);
    int secondEditDistance = hammingDistance(first20KeysizesWorthOfBytes[2], first20KeysizesWorthOfBytes[3]); 
    int thirdEditDistance = hammingDistance(first20KeysizesWorthOfBytes[4], first20KeysizesWorthOfBytes[5]);
    int fourthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[6], first20KeysizesWorthOfBytes[7]); 
    int fifthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[8], first20KeysizesWorthOfBytes[9]); 
    int sixthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[10], first20KeysizesWorthOfBytes[11]);int seventhEditDistance = hammingDistance(first20KeysizesWorthOfBytes[12], first20KeysizesWorthOfBytes[13]);int eigthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[14], first20KeysizesWorthOfBytes[15]);int ninthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[16], first20KeysizesWorthOfBytes[17]);int tenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[18], first20KeysizesWorthOfBytes[19]);int eleventhEditDistance = hammingDistance(first20KeysizesWorthOfBytes[20], first20KeysizesWorthOfBytes[21]);int twelfthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[22], first20KeysizesWorthOfBytes[23]);int thirteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[24], first20KeysizesWorthOfBytes[25]);int fourteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[26], first20KeysizesWorthOfBytes[27]);int fifteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[28], first20KeysizesWorthOfBytes[29]);int sixteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[30], first20KeysizesWorthOfBytes[31]);int seventeenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[32], first20KeysizesWorthOfBytes[33]);int eighteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[34], first20KeysizesWorthOfBytes[35]);int nineteenthEditDistance = hammingDistance(first20KeysizesWorthOfBytes[36], first20KeysizesWorthOfBytes[37]);int twentiethEditDistance = hammingDistance(first20KeysizesWorthOfBytes[38], first20KeysizesWorthOfBytes[39]);

    float average = (firstEditDistance + secondEditDistance + thirdEditDistance + fourthEditDistance + fifthEditDistance + sixthEditDistance + seventhEditDistance + eigthEditDistance + ninthEditDistance + tenthEditDistance +  eleventhEditDistance + twelfthEditDistance + thirteenthEditDistance + fourteenthEditDistance + fifteenthEditDistance + sixteenthEditDistance + seventeenthEditDistance + eighteenthEditDistance + nineteenthEditDistance +twentiethEditDistance)/20.0;

    float normalized = average / (keysize * 1.0); 

    if (normalized < bestEditDistance)
    {
      bestEditDistance = normalized;
      bestScorer = keysize;
    }
  }
  vector<string> keysizeLengthBlocks;
  int leftover = text.size() % bestScorer;
  while (text.size() > leftover)
  {
    string keysizeLengthBlock;
    for (int i = 0; i < bestScorer; ++i)
    {
      keysizeLengthBlock += text[i];
    }
    keysizeLengthBlocks.push_back(keysizeLengthBlock);
    text = text.substr(bestScorer);
  }
  vector<char> key;
  for (int i = 0; i < bestScorer; ++i)
  {
    string ithCharsOfKeysizeLengthBlocks;
    for (string s : keysizeLengthBlocks)
    {
      ithCharsOfKeysizeLengthBlocks += (s[i]);
    }
    string ithCharsAsBits;
    for (int j = 0; j < ithCharsOfKeysizeLengthBlocks.size(); ++j)
    {
      char a = ithCharsOfKeysizeLengthBlocks[j];
      for (int k = 0; k < 8; ++k)
      {
        bool b = (!!((a << k) & 0x80));
        ithCharsAsBits += b ? '1' : '0';
      }
    } 
    char ithByteOfkey = decrypt_1byte_xor_cipher(ithCharsAsBits).first;
    key.push_back(ithByteOfkey);
  }
  return key;
}

string break_vigenere_cipher(string text)
{
  binaryManip manipulator;
  string bin = manipulator.base64ToBinary(text);
  vector<char> key = find_key(bin);
  return repeating_key_xor(bin, key);
}

int main()
{
  hexManip hexifier;
  string text = readfileAsString("../../../Downloads/xoredBase64encryptedtext.txt"); 
  string hex = break_vigenere_cipher(text);
  cout << hexifier.hexDecode(hex); 
  binaryManip manipulator;
  string bin = manipulator.base64ToBinary(text);  
  
}
