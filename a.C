#include <bits/stdc++.h>

using namespace std;

// Both alphabets' frequency analysis from: https://pt.wikipedia.org/wiki/Frequ%C3%AAncia_de_letras
const vector<pair<char,float>> ENG = {
    {'a', 	8.167 / 100},
    {'b', 	1.492 / 100},
    {'c', 	2.782 / 100},
    {'d', 	4.253 / 100},
    {'e', 	12.702 / 100},
    {'f', 	2.228 / 100},
    {'g', 	2.015 / 100},
    {'h', 	6.094 / 100},
    {'i', 	6.966 / 100},
    {'j', 	0.153 / 100},
    {'k', 	0.772 / 100},
    {'l', 	4.025 / 100},
    {'m', 	2.406 / 100},
    {'n', 	6.749 / 100},
    {'o', 	7.507 / 100},
    {'p', 	1.929 / 100},
    {'q', 	0.095 / 100},
    {'r', 	5.987 / 100},
    {'s', 	6.327 / 100},
    {'t', 	9.056 / 100},
    {'u', 	2.758 / 100},
    {'v', 	0.978 / 100},
    {'w', 	2.360 / 100},
    {'x', 	0.150 / 100},
    {'y', 	1.974 / 100},
    {'z', 	0.074 / 100}
};
const vector<pair<char,float>> PT = {
    {'a',   14.63 / 100},
    {'b',   1.04 / 100},
    {'c',   3.88 / 100},
    {'d',   4.99 / 100},
    {'e',   12.57 / 100},
    {'f',   1.02 / 100},
    {'g',   1.30 / 100},
    {'h',   1.28 / 100},
    {'i',   6.18 / 100},
    {'j',   0.40 / 100},
    {'k',   0.02 / 100},
    {'l',   2.78 / 100},
    {'m',   4.74 / 100},
    {'n',   5.05 / 100},
    {'o',   10.73 / 100},
    {'p',   2.52 / 100},
    {'q',   1.20 / 100},
    {'r',   6.53 / 100},
    {'s',   7.81 / 100},
    {'t',   4.34 / 100},
    {'u',   4.63 / 100},
    {'v',   1.67 / 100},
    {'w',   0.01 / 100},
    {'x',   0.21 / 100},
    {'y',   0.01 / 100},
    {'z',   0.47 / 100}
};

char FIRST_CHAR = 97; // space
char LAST_CHAR = 122; // 'z'
int F_TABLE_SIZE = 26;


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
vector<pair<char,float>> get_frequency (string nGroup){
    vector<pair<char,float>> frequencies;
    float nGroupSize, count;
    char aux;
    nGroupSize = nGroup.size(); count = 0;

    sort(nGroup.begin(), nGroup.end());
    for (int i = 0; i < nGroupSize; i++)
    {
        aux = static_cast<char>(nGroup[i]);
        count = nGroup.find_last_of(aux) - nGroup.find_first_of(aux) + 1;
        frequencies.push_back(make_pair(aux, count/nGroupSize));
        i += count - 1;
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
// Returns index of first pair w alphabetic char
int first_alpha(vector<pair<char,float>> data){
    auto it = std::find_if(data.begin(), data.end(), [](const pair<char, float>& e) {return isalpha(get<0>(e)); } );
    if (it != data.end()) {
        return std::distance( data.begin(), it );
    }
    return -1;
}

float shifted_freq( vector<pair<char,float>> data, int shift,vector<pair<char,float>> table) {
    int turnAround, firstAlpha, alphaSizeData, i;
    float diffSum, diff;
    sort(data.begin(), data.end()); // by letter
   /*  firstAlpha = first_alpha(data);
    alphaSizeData = data.size() -  firstAlpha; // TEST ON DATA[0] = 'A' // amount of different letters in data
  */   diffSum = 0; i = 0; turnAround = 0; alphaSizeData = data.size();
    
     while (i < alphaSizeData && i < F_TABLE_SIZE)
    {
        if(shift + i < alphaSizeData){
            diff = abs(get<1>(table[i]) - get<1>(data[i + shift]));
        }
        else
        {
            diff = abs(get<1>(table[i]) - get<1>(data[turnAround]));
        }
        diffSum += diff;
        i++;
    } 
    
    return diffSum;
    
}
// receives alpha sorted frequency of characters and reference freq table
// figures out the most fitting shift(key) in cipher
// input has alphabetic order, guesses key by finding shift with least disparangement between both
// i.e. compares freq diff between A B C & B C A , by index value
// FIXME : NEEDS TO COMPARE 1ST TABLE -> 1ST DATA, NOT A -> 1ST DATA
pair<char,float> find_shift(vector<pair<char,float>> nFrequency, vector<pair<char,float>> table){
    int shift;
    float aux, fitness;
    char key, cipherA;
    
    fitness = 999;
    shift = FIRST_CHAR;

    for (int i = 0; i < LAST_CHAR - FIRST_CHAR; i++)
    {
        aux = shifted_freq(nFrequency,i,ENG);
        if(aux < fitness){
            shift = i;
            fitness = aux;
        }
    }
    // matching WHAT IF THERE ARE NO A/ FIRST TO FIRST BRO
    cipherA = get<0>(nFrequency[0 + shift]); 
    key = find_key(get<0>(table[0]), cipherA);
    nasw = make_pair(key, fitness);
    return nasw;
    
}


void break_vigenere(int opt, string data, int keySize){
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    float bestMatch;
    vector<vector<pair<char,float>>> allGroupsFrequencies;
    string nGroup;;

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < data.size(); i += keySize)
        {
            nGroup += data[i];
        }
        std::cout << nGroup << " ";
        nFrequency = get_frequency(nGroup);
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
        
        key = find_shift(nFrequency, ENG);
        std::cout << "KEY FOUND " << get<0>(key) << get<0>(key) << "    ";
        //shifted_freq(nFrequency,0,ENG);

    }
    
    std::cout << data << endl;
    
}

int main(){
    string aux;

/*     cout << find_key( 'B',encrypt('B', 'C')) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    aux = vigenere( "encrypt", "HELLOSDKFJHG", "SDBNO");
    cout << aux << endl; //zhmyckglsxzj 
    aux = vigenere( "decrypt", aux, "SDBNO");

    cout << encrypt('B', 'C') << endl; //zhmyckglsxzj 

    get_frequency("w1rrr3aaaa4");
    break_vigenere(0, "azbycx", 2);
    break_vigenere(0, "abcdefabcdefabcdefabcdeff1", 6);
 */
  pair<char,float> testResult; 
    vector<pair<char,float>> testENG = {
        {'e', 	12.702 / 100},
        {'f', 	2.228 / 100},
        {'g', 	2.015 / 100},
        {'h', 	6.094 / 100},
        {'i', 	6.966 / 100},
        {'j', 	0.153 / 100},
        {'k', 	0.772 / 100},
        {'l', 	4.025 / 100},
        {'m', 	2.406 / 100},
        {'n', 	6.749 / 100},
        {'o', 	7.507 / 100},
        {'p', 	1.929 / 100},
        {'q', 	0.095 / 100},
        {'r', 	5.987 / 100},
        {'s', 	6.327 / 100},
        {'t', 	9.056 / 100},
        {'a', 	8.167 / 100},
{'b', 	1.492 / 100},
{'c', 	2.782 / 100},
    {'v', 	0.978 / 100},
    {'w', 	2.360 / 100},
    {'x', 	0.150 / 100},
    {'y', 	1.974 / 100},
    {'z', 	0.074 / 100}
    };
    testResult = find_shift(testENG, ENG);
    std::cout << "BREKA \n\n" << static_cast<char>( get<0>(testResult)) << get<1>(testResult) ;
std::cout << "\n\n";
    
  return 0;
}

/* BUG REPORT 
char LAST_CHAR = 221+;
    cout << find_key( 'B',encrypt('B', 'C')) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    !!WRONG KEYS FOUND
    
 */