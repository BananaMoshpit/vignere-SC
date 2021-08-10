#include <bits/stdc++.h>
//CURRENTLY CONSIDERS CIPHER AS A MTRAIX OF UPPERCASE ALPHABET ASCCI
// tried to clean mess went wrong -- bc treated string as vec?

using namespace std;

char UPPER_FIRST_CHAR = 'A';
char UPPER_LAST_CHAR = 'Z';
string DATA, KEY, ENCRYPTED;

string encrypt(string lddata, string lkkey){
    int lddataSize, lkkeySize, charSum, i, k;
    string enc = lddata;
    lddataSize = lddata.size(); lkkeySize = lkkey.size();

    for (i = 0, k = 0; i < lddataSize; i++)
    {
        charSum = lddata[i] + lkkey[k] - UPPER_FIRST_CHAR; // BOTH INPUTS MUST BE UPPERCASE to work
        if(charSum > static_cast<int>(UPPER_LAST_CHAR)) // keep from trespassing alphabet boundaries
            charSum = UPPER_FIRST_CHAR + (charSum  - UPPER_LAST_CHAR) - 1;
        
        enc[i] = static_cast<char>(charSum);
        k++;
        if(k >= lkkeySize)
            k = 0;
    }

    return enc;
    
}

int main(){
    cout << static_cast<char>('L' + 'Y' - 'A') << endl; // what i needed
   /*  cout << static_cast<char>('d' + 'd' - 'a') << endl; // what i needed
    cout << ('a' + 'b') << endl;
    cout << ('a' + 0) << endl ; */

    cout << encrypt("HELLO", "KEY") << endl; //rijvs
    cout << encrypt("HELLO", "SDBNO") << endl; //zhmyc
    cout << encrypt("HELLOSDKFJHG", "SDBNO") << endl; //zhmyckglsxzj
  return 0;
}