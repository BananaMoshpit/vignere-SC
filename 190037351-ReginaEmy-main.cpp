//por: Regina Kamada, 190037351. UnB 2022/1.

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


const static char FIRST_CHAR = 97; // a
const static char LAST_CHAR = 122; // z
const static int F_TABLE_SIZE = 25;

// encrypts data from a key
char encrypt(const char data, const char key){
    int enc = static_cast<int>(data) + static_cast<int>(key) - static_cast<int>(FIRST_CHAR); 
    if(enc > static_cast<int>(LAST_CHAR)) {// keep from trespassing alphabet boundaries
        enc = static_cast<int>(data) + static_cast<int>(key) - static_cast<int>(LAST_CHAR) - 1;          //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return  static_cast<char>(enc);  
}

// decrypts cipher from key
char decrypt(const char enc, const char key){
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


vector<pair<char,float>> empty_table(){
   vector<pair<char,float>> aux;
   aux = ENG;
   for (int i = 0; i < F_TABLE_SIZE; i++)
   {
       get<1>(aux[i]) = 0;
   }
   
   return aux;
}

//!TODO: consider mean freq?
// PS: NOT N-SORTED: RECEIVES N-SORTED GROUPS
vector<pair<char,float>> get_frequency (string nGroup){
    vector<pair<char,float>> frequencies, auxTable ;
    float nGroupSize, count, freq;
    char aux;
    int j = 0;
    nGroupSize = nGroup.size(); count = 0;

    sort(nGroup.begin(), nGroup.end());
    for (int i = 0; i < nGroupSize; i++)
    {
        aux = static_cast<char>(nGroup[i]);
        count = nGroup.find_last_of(aux) - nGroup.find_first_of(aux) + 1;
        freq = count/nGroupSize;
        aux = static_cast<char>(nGroup[i]);
        count = nGroup.find_last_of(aux) - nGroup.find_first_of(aux) + 1;
        freq = count/nGroupSize;
        auxTable.push_back(make_pair(aux, freq));
        i += count - 1;

        sort(auxTable.begin(), auxTable.end()); //sorts a->z
        frequencies = empty_table();
        
        for(int j = 0; j < F_TABLE_SIZE ; j++){
            for(int i = 0; i < auxTable.size() ; i++){
                if(get<0>(frequencies[j]) == get<0>(auxTable[i])){
                    get<1>(frequencies[j] )= get<1>(auxTable[i]);
                }
            }
        }
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
    if(row < table.size())
     return (get<1>(table[row]) * 100.00);
    else{
     cout << "Erro de acesso de memória não alocada em get_char_frequency";
     return -1;
    }
}

//prints 3 frequency tables besides each other: ENG, PT & argument
//ENG max freq = 13, PT max freq = 15
void print_freq_graph(vector<pair<char,float>> data){
    float j, charFreq, engMax, ptMax;
    char aux, line, lineEnd;
    int afarNum = 2;
    engMax = 13;
    ptMax = 15;
    cout << "ENG                 " << "PT                 " << "DATA" << "             " << "ENG            " << "PT            " << "DATA" << endl;
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

        cout << "    ";
        cout << get<0>(ENG[row]) << " " << get_char_frequency(ENG, row) << "         " <<  get<0>(ENG[row]) << " "<< get_char_frequency(PT, row) <<  "         " << row << ": " << get_char_frequency(data, row) << endl ;
         std::cout << endl;
    
    }
}


void print_tuple_vector_freqs(vector<pair<char,float>> data){
    float charFreq;
    cout << std::fixed;
    cout << std::setprecision(2);
    cout << "ENG            " << "DATA            " << "PT" <<  endl;
        for (int row = 0; row < F_TABLE_SIZE; row++)
    {
        cout << get<0>(ENG[row]) << " " << get_char_frequency(ENG, row) << "         " <<  row << ": "<< get_char_frequency(data, row) <<  "         " << get<0>(ENG[row]) << " " << get_char_frequency(PT, row) << endl ;

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


int find_key_size(const string data){
    int opt = 0;
    int keySizeGuess = 4;
    vector<pair<char,float>> nFrequency;
    std::cout << ">> mostrando gráficos de frequências para diferentes tamanhos de chave " << endl;
    while (keySizeGuess >= 0){
        nFrequency = get_nGroup_freq(data, keySizeGuess);
        print_freq_graph(nFrequency);
        cout << "tamanho da chave no gráfico acima: " << keySizeGuess << endl;
        cout << "digite outro tamanho de chave (> 0) para teste ou -1 para escolher este tamanho: " << endl;
        cin >> opt ;
        if(opt >= 0){
            keySizeGuess = opt;
        }
        else
        {
            return keySizeGuess;
        }
        
    }
    return -1;
}

// decrypts message by freq analysis based on GLOBAL vars (ENG, PT)
string break_vigenere(string data, int keySize){
    int dataSize = data.size();
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    string nGroup, dec, k;
    int language, shift, opt, i;
    i = 0;
         
    cout << ">> encontrando a senha com ataque de frequência assumindo o tamanho de chave " << keySize << endl;

    while(keySize > 0) {
        for (int keyN = 1; keyN <= keySize; keyN++)
        {
            nGroup.clear();
            for(i = keyN - 1; i < dataSize; i += keySize)
            {
                nGroup += data[i];
            }
            nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
            sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
            cout << "Seguem os gráficos de frequência de letras. Compare-os para descobrir a linguagem da mensagem original e digite " << endl;
            //cout << "Dica: Em inglês, as colunas de t-e são: t(alta), u-z(muito baixas), a(2a maior), e(maior). Em PT, a > e, t ~= u " << endl;
            //cout << "Dica: em inglês, há 1 coluna maior(t) sucedida por 6 baixíssimas(u-z), que antecedem uma das maiores(a), sucedida por 3 menores(b-d) e pela maior(e)." << endl;
            print_freq_graph(nFrequency);       
            cout << "Digite o número linha que representa 'a' no gráfico de DATA (0-25) ou (-1) para tentar outro tamanho de chave: " ;
            cin >> shift;
            if(shift < 0){
                keySize = find_key_size(data);
                i = 0;
                keyN = 1;
                break;
            }
            //k += decrypt('a', get<0>(nFrequency[shift]));
            else
            {           
                cout << "caesar:" << find_key('a', get<0>(nFrequency[shift])) << endl;
                k += find_key('a', get<0>(nFrequency[shift])); 
            }
            
        }

        if(i >= dataSize)
        {
            break;
        }
    }
    
    cout <<"\nchave encontrada: " << k << endl;
    
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

void userInterface(){
    cout << "Interface de usuário, Código de Vigenère.." << endl;
    int keySize;
    int opt = 0; 
    char yn;
    ofstream out("out.txt", std::ios_base::app);
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
            out << endl;
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
            out << endl;
            opt = 0;        
            break;
        case 3:
            cout << "Qual o nome do arquivo de entrada contendo apenas a mensagem a ser atacada?(Deve estar na mesma pasta que esse arquivo)" << endl;
            cin >> filenameIn;
            data = read_from_in(filenameIn); 
            dataBreak = get_ASCII(data);
            //dataBreak = data;
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
            out << endl;
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
