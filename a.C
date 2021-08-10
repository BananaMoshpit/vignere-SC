#include <bits/stdc++.h>

using namespace std;

char UPPER_FIRST_CHAR = 'A';
string DATA, KEY, ENCRYPTED;

string encrypt(string lddata, string lkkey){
    int lddataSize, lkkeySize, i, k;
    lddataSize = lddata.size(); lkkeySize = lkkey.size();

    ENCRYPTED.clear(); ENCRYPTED = lddata; //TO ACCESS ENCRYOTED LETTERS BY INDEX, CLEANIN GLOBAL
    //for (i = 0, k = 0; i < lddataSize, k < lkkeySize; i++, k++)
    for (i = 0, k = 0; i < lddataSize; i++)
    {
        ENCRYPTED[i] = static_cast<char>(lddata[i] + lkkey[k] - UPPER_FIRST_CHAR); // BOTH INPUTS MUST BE UPPERCASE to work
        k++;
        if(k >= lkkeySize - 1)
            k = 0;
    }

    return ENCRYPTED;
    
}
int main(){
    cout << static_cast<char>('B' + 'C' - 'A') << endl; // what i needed
   /*  cout << static_cast<char>('d' + 'd' - 'a') << endl; // what i needed
    cout << ('a' + 'b') << endl;
    cout << ('a' + 0) << endl ; */

    cout << encrypt("HELLO", "KEY") << endl; //rijvs
  return 0;
}