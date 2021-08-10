#include <bits/stdc++.h>
//CURRENTLY CONSIDERS CIPHER AS A MTRAIX OF UPPERCASE ALPHABET ASCCI
// tried to clean mess went wrong -- bc treated string as vec?

using namespace std;

char UPPER_FIRST_CHAR = 9; // space
char UPPER_LAST_CHAR = 253; // 'z'

// !FIXME : BOTH INPUTS MUST BE UPPERCASE to work
string encrypt(string data, string key){
    int dataSize, keySize, charSum, i, k;
    string enc = data;
    dataSize = data.size(); keySize = key.size();

    for (i = 0, k = 0; i < dataSize; i++)
    {
        charSum = data[i] + key[k] - UPPER_FIRST_CHAR; 
        if(charSum > static_cast<int>(UPPER_LAST_CHAR)) // keep from trespassing alphabet boundaries
            charSum += UPPER_FIRST_CHAR - UPPER_LAST_CHAR - 1;
            //charSum = UPPER_FIRST_CHAR + (charSum  - UPPER_LAST_CHAR) - 1;
        
        enc[i] = static_cast<char>(charSum);
        k++;
        if(k >= keySize)
            k = 0;
    }

    return enc;
    
}

// data[i] =  charSum - key[k] + UPPER_FIRST_CHAR; <-  charSum = data[i] + key[k] - UPPER_FIRST_CHAR;
// ENC[I] =  data[i] + key[k]  - UPPER_LAST_CHAR - 1 -> data[i] = - key[k]  + UPPER_LAST_CHAR - enc[i] + 1
//  L + Y - Z - 1 = J -> L = J - Y + 1
// !FIXME : BOTH INPUTS MUST BE UPPERCASE to work
string decrypt(string encrypted, string key){
    int dataSize, keySize, charSum, i, k;
    string dec = encrypted;
    dataSize = encrypted.size(); keySize = key.size();

    for (i = 0, k = 0; i < dataSize; i++)
    {
        charSum = encrypted[i] - key[k] + UPPER_FIRST_CHAR;               
        if(charSum < static_cast<int>(UPPER_FIRST_CHAR))                 // keep from trespassing alphabet boundaries
            charSum =  encrypted[i] - key[k]  + UPPER_LAST_CHAR + 1; //  L + Y - Z - 1 = J -> L = J - Y + 1
        dec[i] = static_cast<char>(charSum);
        k++;
        if(k >= keySize)
            k = 0;
    }

    return dec;
    
}

int main(){
/*     cout << static_cast<char>('L' + 'Y' - 'A') << endl; // what i needed
    cout << static_cast<char>('L' + 'Y' - 'Z' - 1) << endl; // what i needed

    cout << encrypt("p \r <-para", "asZ") << endl; //rijvs
    cout << decrypt( encrypt("p \n <-para", "asZ"), "KEY") << endl; //rijvs */
    cout << decrypt( encrypt("Hel>~lO Wo\nrlD", "KEY"), "KEY") << endl; //rijvs // FIXME: TERMINAL DECRYPTS '~' AS '\n'

    cout << encrypt("HEÂLLO", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("HEÃLLO", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("HELLO WORLD", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("HELLO WORLD", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("F123rom there, we just need to split it into 6 columns (I mean in Python it would be tab  paragraph \n r \r what ", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("F123rom there, we just need to split it into 6 columns (I mean in Python it would be tab     paragraph \n r \r what ", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("HELLO", "SDBNO") << endl; //zhmyc
    cout << decrypt( encrypt("HELLO", "SDBNO"), "SDBNO") << endl; //zhmyc
    cout << encrypt("HELLOSDKFJHG", "SDBNO") << endl; //zhmyckglsxzj 
    cout << decrypt( encrypt("HELLOSDKFJHG", "SDBNO"), "SDBNO") << endl; //zhmyckglsxzj 
  return 0;
}