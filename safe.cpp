//TODO: SUGGEST USER WHEN PICK FREQ-- BARRIGA ENG  == Ij b a r r i g a
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

// 31 254 works, tryna a-z
const static char FIRST_CHAR = 97; //01 97 31 
const static char LAST_CHAR = 122; // 254 122 126
const static int F_TABLE_SIZE = 26;

// encrypts data from a key
char encrypt(char data, char key){
    int enc = static_cast<int>(data) + static_cast<int>(key) - static_cast<int>(FIRST_CHAR); 
    if(enc > static_cast<int>(LAST_CHAR)) {// keep from trespassing alphabet boundaries
        enc = static_cast<int>(data) + static_cast<int>(key) - static_cast<int>(LAST_CHAR) - 1;          //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
/*     if(enc < static_cast<int>(FIRST_CHAR)){
        enc = static_cast<int>(data) + static_cast<int>(key);
    } */
  return  static_cast<char>(enc);  
}

// ENC[I] =  data[i] + key[k]  - LAST_CHAR - 1 -> data[i] = - key[k]  + LAST_CHAR - enc[i] + 1
//  L + Y - Z - 1 = J -> L = J - Y + 1
// decrypts cipher from key
char decrypt(char enc, char key){
    int dec = static_cast<int>(enc) - static_cast<int>(key) + static_cast<int>(FIRST_CHAR);             
    if(dec < static_cast<int>(FIRST_CHAR)){   // keep from trespassing alphabet boundaries
        dec =  static_cast<int>(enc) - static_cast<int>(key)  + static_cast<int>(LAST_CHAR) + 1;     //  L + Y - Z - 1 = J -> L = J - Y + 1    
    }
  return static_cast<char>(dec); 
}

// encrypts or decrypts a string from a key 
string vigenere(string opt, string data, string key);
string vigenere(string opt, string data, string key){
    int keySize, k;
    int dataSize, i;
    char aux;
    string vig = data;
    dataSize = data.size(); keySize = key.size();

    for (i = 0, k = 0; i < dataSize; i++)
    {
        if(static_cast<int>(data[i]) >= 97 && (static_cast<int>(data[i]) <= 122) || (static_cast<int>(data[i]) >= 65 && static_cast<int>(data[i]) <= 90))
        {
            if(opt == "encrypt"){
                aux = encrypt(tolower(data[i]), key[k]);
            }
            else if (opt == "decrypt") {
                aux = decrypt(tolower(data[i]), key[k]);
            }
            
            vig[i] = aux;
            k++;
            if(k >= keySize){
                k = 0; 
            }
        }

    }

    return vig;
    
}

// PS: NOT N-SORTED: RECEIVES N-SORTED GROUPS
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

// get key given original data and cipher
char find_key(char data, char enc){
    char key = enc - data + FIRST_CHAR;             
    if(key < static_cast<int>(FIRST_CHAR)){ // keep from trespassing alphabet boundaries
        key =  enc - data  + LAST_CHAR + 1;  //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(key); 
}

float get_char_frequency(vector<pair<char,float>> table, int row){
    return (get<1>(table[row]) * 100.00);
}

//prints 3 frequency tables besides each other: ENG, PT & argument
//ENG max freq = 13, PT max freq = 15
void print_freq_graph(vector<pair<char,float>> data){
    float j, charFreq, engMax, ptMax;
    char aux, line, lineEnd;
    int afarNum = 2;
    engMax = 13;
    ptMax = 15;
    cout << "ENG                 " << "PT                 " << "DATA" <<  endl;
    for (int row = 0; row < F_TABLE_SIZE; row++)
    {
        if(row&1)
        {
            line = '_';
            lineEnd = '|';
        }
        else{
            line = '-';
            lineEnd = ':';
        }
 
// prints a horizontal line as frequency of line drawing + afarNum of spaces
        cout << get<0>(ENG[row]);
        for (int eng = 0; eng < engMax + afarNum ; eng++)
        {
            charFreq = get_char_frequency(ENG, row);
            if(eng < charFreq)
            {
                aux = line;
            }
            else if (eng < charFreq + 1 && charFreq - 1 < eng)
            {
                aux = lineEnd;
            }
            else
            {
                aux = ' ';
            }
            cout << aux;
        }
        
// prints a horizontal line as frequency of line drawing + afarNum of spaces
        cout << get<0>(PT[row]);
        for (int pt = 0; pt < ptMax + afarNum ; pt++)
        {
            charFreq = get_char_frequency(PT, row);
            if(pt < charFreq)
            {
                aux = line;
            }
            else if (pt < charFreq + 1 && charFreq - 1 < pt)
            {
                aux = lineEnd;
            }
            else
            {
                aux = ' ';
            }
            cout << aux;
        }
    
//FIXME: CHANGE HARDCODED 30 FOR THE BIGGEST FREQUENCY IN DATA TABLE
// prints DATA'S horizontal line as frequency of line drawing + afarNum of spaces
        cout << row;
        for (int i = 0; i < 15 + afarNum ; i++)
        {
            charFreq = get_char_frequency(data, row);
            if(i < charFreq)
            {
                aux = line;
            }
            else if (i < charFreq + 1 && charFreq - 1 < i)
            {
                aux = lineEnd;
            }
            else
            {
                aux = ' ';
            }
            cout << aux;
        } 
         std::cout << endl;
    
        
    }
}


char decrypt(char enc, int shift){
    int dec = static_cast<int>(enc) - shift; //+ static_cast<int>(FIRST_CHAR);             
    if(dec < static_cast<int>(FIRST_CHAR)){   // keep from trespassing alphabet boundaries
        dec =  static_cast<int>(enc) + static_cast<int>(LAST_CHAR)  + static_cast<int>(LAST_CHAR) + 1;     //  L + Y - Z - 1 = J -> L = J - Y + 1    
    }
  return static_cast<char>(dec); 
}

vector<pair<char,float>> get_nGroup_freq(string data, int keySize){
    int dataSize = data.size();
    vector<pair<char,float>> nFrequency;
    string nGroup, dec, k;
    int language, shift;

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < dataSize; i += keySize)
        {
            nGroup += data[i];
        }
        nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
    }
    return nFrequency;
}

int find_key_size(string data){
    int stop = 1;
    int keySizeGuess = 1;
    vector<pair<char,float>> nFrequency;
    while (stop != 0){
        std::cout << "serão mostrados múltiplos gráficos de frequências para tamanhos incrementais de chave(a partir de zero), aperte 0 quando o gráfico de dados à direita for o mais similar possível com uma das tabels padrão à esquerda " << endl;
        std::cout << " digite '-1' para diminuir o tamanho da chave em 1; '1' para aumentar ou; 0 para selecionar tamanho de chave  " << endl;
        nFrequency = get_nGroup_freq(data, keySizeGuess);
        print_freq_graph(nFrequency);
        cin >> stop;
        keySizeGuess += stop;


    }
}


// decrypts message by freq analysis based on GLOBAL vars (ENG, PT)
string break_vigenere(string data, int keySize){
    int dataSize = data.size();
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    string nGroup, dec, k;
    int language, shift;

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < dataSize; i += keySize)
        {
            nGroup += data[i];
        }
        nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
        if(language == 1){
            cout << "Frequência das letras de a - b em portugês:" << endl;
            print_freq_graph(PT);
        }
         
        else 
        {
            cout << "Frequência das letras de a - b em Inglês:" << endl;
            print_freq_graph(ENG);
        }
        cout << "Seguem os gráficos de frequência de letras. Compare-os para descobrir a linguagem da mensagem original e encontre a linha que representa 'a' no gráfico de DATA" << endl;
        //cout << "Dica: Em inglês, as colunas de t-e são: t(alta), u-z(muito baixas), a(2a maior), e(maior). Em PT, a > e, t ~= u " << endl;
        cout << "Dica: em inglês, há 1 coluna maior(t) sucedida por 6 baixíssimas(u-z), que antecedem uma das maiores(a), sucedida por 3 menores(b-d) e pela maior(e)." << endl;
        cout << "Considere apenas o gráfico da linguagem escolhida." << endl;
        print_freq_graph(nFrequency);       
        cout << "Digite um número 0-25: " ;
        cin >> shift;
        //k += decrypt('a', get<0>(nFrequency[shift]));
        cout << "caesar:" << find_key('a', get<0>(nFrequency[shift])) << endl;
        k += find_key('a', get<0>(nFrequency[shift]));
    }
    
    cout <<"\nKEY\n" << k << "\n\n"<< endl;
    
    return k;
}
//reads text and ignores spaces
string read_from_in(string fileName){
    string data, read;
   fstream in;
    in.open(fileName);
    while (getline(in, read))
    {
        data += read;
        
    }
    in.close();
    return data;
}

//extracts all letters as lowercase characters
string get_ASCII( string data){
    int size = data.size();
    string ascii;
    char aux;
    for (int i = 0; i < size; i++)
    {
        aux = data[i];
        if( (65 <= aux  && aux <= 90 ) || (97 <= aux  && aux <= 122 )){
          if (65 <= aux && aux <= 90) // converts upper to lowercase
          {
              aux = tolower(aux);
          }
            
          ascii += aux;
        }
    }
    return ascii;
}

//TODO: WRITE ON OUTPUT FILE WITHOUT DELETING PREVIOUS
void userInterface(){
    cout << "Interface de usuário, Código de Vigenère.." << endl;
    int keySize;
    int opt = 0; 
    char yn;
    ofstream out("out.txt", ofstream::out | ofstream::trunc);
    string filenameIn, data, enc, dec, key, dataBreak;

    while (opt != -1)
    {
        switch (opt)
        {
        case 1:
            cout << "Qual o nome do arquivo de entrada contendo apenas a mensagem a ser codificada? (Deve estar na mesma pasta que esse arquivo)" << endl;
            cin >> filenameIn;
            cout <<"Digite a chave:" << endl;
            cin >> key;
            data = read_from_in(filenameIn); 
//            data = get_ASCII(data);
            enc = vigenere("encrypt", data, key);
            cout << "Segue o  resultado, também adicionado ao arquivo out.txt" << endl;
            cout << enc << endl;
            out << enc;
            opt = 0;
            break;
        case 2:
            cout << "Qual o nome do arquivo de entrada contendo apenas a mensagem a ser descodificada?(Deve estar na mesma pasta que esse arquivo)" << endl;
            cin >> filenameIn;
            cout <<"Digite a chave:" << endl;
            cin >> key;
            data = read_from_in(filenameIn); 
            //data = get_ASCII(data);
            dec = vigenere("decrypt", enc, key);  
            cout << "Segue o  resultado, também adicionado ao arquivo out.txt" << endl;
            cout << dec << endl;
            out << dec;
            opt = 0;        
            break;
        case 3:
            cout << "Qual o nome do arquivo de entrada contendo apenas a mensagem a ser atacada?(Deve estar na mesma pasta que esse arquivo)" << endl;
            cin >> filenameIn;
            data = read_from_in(filenameIn); 
            dataBreak = get_ASCII(data);
            yn = 'y';

            while (yn == 'y')            
            {
                yn = ' ';
                while(yn != 'y' && yn != 'n')
                {
                cout << "Sabe-se o tamanho da chave? y/n" << endl;
                cin >> yn;
                }
                if(yn == 'n')
                {
                    keySize = find_key_size(dataBreak);
                }
                else
                {
                    cout << "Digite-o (de 1 para cima):" << endl;
                    cin >> keySize;
                }
                key = break_vigenere(dataBreak, keySize);
                cout << "Chave encontrada: " << key << endl;
                dec = vigenere("decrypt", data, key);
                cout << "Mensagem descriptografada: " << endl <<  dec << endl;
                cout << "Tentar novamente? A mensagem será escrita em out.txt se a resposta for 'n'  y/n" << endl;
                cin >> yn;
            }

            out << dec;
            cout << "A mensagem acima foi escrita no arquivo out.txt" << endl;
            opt = 0;
            break;
        case -1:
          return;
        
        default:
            cout << "Digite 1 para criptografar uma mensagem com uma chave" << endl;
            cout << "Digite 2 para descriptografar uma mensagem codificada com uma chave conhecida" << endl;
            cout << "Digite 3 para atacar uma mensagem codificada com a frequência de letras" << endl;
            cout << "Digite -1 para fechar o programa" << endl;
            cin >> opt;
            break;
        }
    }

    out.close();
    return;
}
int main(){
    string aux, data, asciiData, enc, key, hk, read, dec;
    ofstream out("out.txt", ofstream::out | ofstream::trunc);
    userInterface();

  return 0; 
}
