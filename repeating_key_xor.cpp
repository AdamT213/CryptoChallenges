#include <iostream> 
#include <string> 
#include <vector> 
#include "repeating_key_xor.h"

using namespace std;

int main() {
  vector<char> ice = {'I', 'C', 'E'};
  string actual = repeating_key_xor("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", ice);

  string expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  bool b = (actual == expected); 

  if (b) { 
    cout << "theyre fucking equal goddamit!";
  } 
  else {

    for (int i=0; i<expected.size(); ++i) { 
      if (actual[i] != expected[i]) { 
        cout << "position: " << i << " " << "should be: " << expected[i] << " " << "is: " << actual[i] << endl;
      }
    };
  }
}