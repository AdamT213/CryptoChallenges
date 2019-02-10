#include <string> 
#include <vector>  
#include <iso646.h> 

int hammingDistance(std::string s1, std::string s2) { 
  std::vector<bool> bin1; 
  std::vector<bool> bin2;

  while (s1.size()) {
    
    char a = s1[0];
    
    for (int i=0; i<8; ++i) {
      bin1.push_back(!!((a << i) & 0x80));
    }
    s1 = s1.substr(1);
  } 

  while (s2.size()) {
    
    char a = s2[0];
    
    for (int i=0; i<8; ++i) {
      bin2.push_back (!!((a << i) & 0x80));
    }
    s2 = s2.substr(1);
  }

  int distance = 0;  
  for(int i =0; i<bin1.size(); ++i) { 
   bool b = bin1[i] ^ bin2[i];  
   if (b) { 
     distance++;
   }
  }
  return distance;
}