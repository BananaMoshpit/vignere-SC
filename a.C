#include <bits/stdc++.h>

using namespace std;

char FIRST_CHAR = 30; // space
char LAST_CHAR = 221; // 'z'


char encrypt(char data, char key){
    char enc = data + key - FIRST_CHAR; 
    if(enc > static_cast<int>(LAST_CHAR)) {
        enc += FIRST_CHAR - LAST_CHAR - 1;
    }
  return  static_cast<char>(enc);  
}

// ENC[I] =  data[i] + key[k]  - LAST_CHAR - 1 -> data[i] = - key[k]  + LAST_CHAR - enc[i] + 1
//  L + Y - Z - 1 = J -> L = J - Y + 1
char decrypt(char enc, char key){
    char dec = enc - key + FIRST_CHAR;             
    if(dec < static_cast<int>(FIRST_CHAR)){             // keep from trespassing alphabet boundaries
        dec =  enc - key  + LAST_CHAR + 1;      //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(dec); 
}
/* 
char decrypt(char data, char key){
    char dec = data - key + FIRST_CHAR;             
    if(dec < static_cast<int>(FIRST_CHAR)){             // keep from trespassing alphabet boundaries
        dec =  data - key  + LAST_CHAR + 1;      //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(dec); 
} */

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
// FIXME: NOT N-SORTED: RECEIVES N-SORTED GROUPS
vector<tuple<char,float>> get_frequency (string nGroup){
    vector<tuple<char,float>> frequencies;
    float nGroupSize, count;
    char aux;
    nGroupSize = nGroup.size(); count = 0;

    sort(nGroup.begin(), nGroup.end());
    for (int i = 0; i < nGroupSize; i++)
    {
        aux = static_cast<char>(nGroup[i]);
        count = nGroup.find_last_of(aux) - nGroup.find_first_of(aux) + 1;
        frequencies.push_back(make_tuple(aux, count/nGroupSize));
    }
    
    return frequencies;
}

char find_key(char data, char enc){
    char key = enc - data + FIRST_CHAR;             
    if(key < static_cast<int>(FIRST_CHAR)){             // keep from trespassing alphabet boundaries
        key =  enc - data  + LAST_CHAR + 1;      //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(key); 
}

void break_vigenere(int opt, string data, int keySize){
    vector<tuple<char,float>> nFrequency;
    vector<vector<tuple<char,float>>> allGroupsFrequencies;
    string nGroup;;
    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < data.size(); i += keySize)
        {
            nGroup += data[i];
        }
        cout << nGroup << " ";
        nFrequency = get_frequency(nGroup);
    }
    
    cout << data << endl;
}

int main(){
    string aux;

    cout << find_key( 'B',encrypt('B', 'C')) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    aux = vigenere( "encrypt", "HELLOSDKFJHG", "SDBNO");
    cout << aux << endl; //zhmyckglsxzj 
    aux = vigenere( "decrypt", aux, "SDBNO");

    cout << encrypt('B', 'C') << endl; //zhmyckglsxzj 

    get_frequency("w1rrr3aaaa4");
    break_vigenere(0, "azbycx", 2);
    break_vigenere(0, "abcdefabcdefabcdefabcdeff1", 6);
  return 0;
}

/* BUG REPORT 
char LAST_CHAR = 221+;
    cout << find_key( 'B',encrypt('B', 'C')) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    !!WRONG KEYS FOUND
    
 */