#include <bits/stdc++.h>

using namespace std;

char FIRST_CHAR = 32; // space
char LAST_CHAR = 122; // 'z'


char encrypt(char data, char key){
    char enc = data + key - FIRST_CHAR; 
    if(enc > static_cast<int>(LAST_CHAR)) {
        enc += FIRST_CHAR - LAST_CHAR - 1;
    }
  return  static_cast<char>(enc);  
}

// ENC[I] =  data[i] + key[k]  - LAST_CHAR - 1 -> data[i] = - key[k]  + LAST_CHAR - enc[i] + 1
//  L + Y - Z - 1 = J -> L = J - Y + 1
char decrypt(char data, char key){
    char dec = data - key + FIRST_CHAR;             
    if(dec < static_cast<int>(FIRST_CHAR)){             // keep from trespassing alphabet boundaries
        dec =  data - key  + LAST_CHAR + 1;      //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(dec); 
}

string vigenere(string opt, string data, string key){
    int dataSize, keySize, i, k;
    char aux;
    string vig = data;
    dataSize = data.size(); keySize = key.size();

    for (i = 0, k = 0; i < dataSize; i++)
    {
        if(opt == "encrypt"){
            aux = encrypt(data[i], key[k]);
        }
        else if (opt == "decrypt") {
            aux = decrypt(data[i], key[k]);
        }
        
        vig[i] = static_cast<char>(aux);
        k++;
        if(k >= keySize){
            k = 0; 
        }
    }

    return vig;
    
}

vector<tuple<char,long int>> get_frequencies (string data, int keySize){
    vector<tuple<char,long int>> frequencies;
    int dataSize, count;
    char aux;
    dataSize = data.size(); count = 0;

    sort(data.begin(), data.end());
    for (int i = 0; i < dataSize; i++)
    {
        aux = static_cast<char>(data[i]);
        count = data.find_last_of(aux) - data.find_first_of(aux) + 1;
        cout << aux << " " << count << "    ";
    }
    
    return frequencies;
}

int main(){
    string aux;

/*     cout << static_cast<char>('L' + 'Y' - 'A') << endl; // what i needed
    cout << static_cast<char>('L' + 'Y' - 'Z' - 1) << endl; // what i needed

    cout << encrypt("p \r <-para", "asZ") << endl; //rijvs
    cout << decrypt( encrypt("p \n <-para", "asZ"), "KEY") << endl; //rijvs */
/*     cout << decrypt( encrypt("Hel>~lO Wo\nrlD", "KEY"), "KEY") << endl; //rijvs // FIXME: TERMINAL DECRYPTS '~' AS '\n'

    cout << encrypt("HEÂLLO", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("HEÃLLO", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("HELLO WORLD", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("HELLO WORLD", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("F123rom there, we just need to split it into 6 columns (I mean in Python it would be tab  paragraph \n r \r what ", "KEY") << endl; //rijvs
    cout << decrypt( encrypt("F123rom there, we just need to split it into 6 columns (I mean in Python it would be tab     paragraph \n r \r what ", "KEY"), "KEY") << endl; //rijvs

    cout << encrypt("HELLO", "SDBNO") << endl; //zhmyc
    cout << decrypt( encrypt("HELLO", "SDBNO"), "SDBNO") << endl; //zhmyc
    cout << encrypt("HELLOSDKFJHG", "SDBNO") << endl; //zhmyckglsxzj 
    cout << decrypt( encrypt("HELLOSDKFJHG", "SDBNO"), "SDBNO") << endl; //zhmyckglsxzj  */

    aux = vigenere( "encrypt", "HELLOSDKFJHG", "SDBNO");
    cout << aux << endl; //zhmyckglsxzj 
    aux = vigenere( "decrypt", aux, "SDBNO");

    cout << aux << endl; //zhmyckglsxzj 

    get_frequencies("w1rrr3aaaa4", 3);
  return 0;
}