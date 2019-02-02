#include <string> 
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>

using namespace boost::archive::iterators;
using namespace std;

class binaryManip { 
  public:
  
  string binaryToBase64(string text) { 
  
    typedef insert_linebreaks<base64_from_binary<transform_width<string::const_iterator,6, 1>>, 64> it_base64_t;
    unsigned int writePadChars = (3-text.length()%3)%3;
    string base64(it_base64_t(text.begin()),it_base64_t(text.end()));
    base64.append(writePadChars,'=');
    
    return base64;
  } 

    char binaryToHex(string bin) { 
    if (bin == "0000") return '0'; 
    else if (bin == "0001") return '1';
    else if (bin == "0010") return '2';
    else if (bin == "0011") return '3';
    else if (bin == "0100") return '4';
    else if (bin == "0101") return '5';
    else if (bin == "0110") return '6';
    else if (bin == "0111") return '7';
    else if (bin == "1000") return '8';
    else if (bin == "1001") return '9';
    else if (bin == "1010") return 'a';
    else if (bin == "1011") return 'b';
    else if (bin == "1100") return 'c';
    else if (bin == "1101") return 'd';
    else if (bin == "1110") return 'e';
    else if (bin == "1111") return 'f'; 
  }
};