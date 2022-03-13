//FIXME: STRINGS LIKE "Á" IS READ AS SIZE() == 2 AND WRECKS ENCRYPT/DECRYPT SHIFT OPERATIONS' LOGIC
//TODO: IMPLEMENT INPUT_KEY AND FIND_SHIFT TO BREAK VIGNERE
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

const static char FIRST_CHAR = 01; //
const static char LAST_CHAR = 254; // 
const static int F_TABLE_SIZE = 26;

// encrypts data from a key
char encrypt(char data, char key){
    int enc = static_cast<int>(data) + static_cast<int>(key) - static_cast<int>(FIRST_CHAR); 
    if(enc > static_cast<int>(LAST_CHAR)) {// keep from trespassing alphabet boundaries
        enc += static_cast<int>(FIRST_CHAR) - static_cast<int>(LAST_CHAR) - 1;          //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
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

// get key given original data and cipher
char find_key(char data, char enc){
    char key = enc - data + FIRST_CHAR;             
    if(key < static_cast<int>(FIRST_CHAR)){ // keep from trespassing alphabet boundaries
        key =  enc - data  + LAST_CHAR + 1;  //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(key); 
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
        if(opt == "encrypt"){
            aux = encrypt(data[i], key[k]);
        }
        else if (opt == "decrypt") {
            aux = decrypt(data[i], key[k]);
        }
        
        vig[i] = aux;
        k++;
        if(k >= keySize){
            k = 0; 
        }
    }

    return vig;
    
}

// PS: NOT N-SELECTED: RECEIVES N-SELECTED GROUPS
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
        frequencies.push_back(make_pair(aux, count/nGroupSize)); //WHY SHOULD IT BE BY TOTAL OF LETTERS IN TEXT OR BY TOTAL LETTERS IN ALPHABET???
        i += count - 1;
    }
    
    return frequencies;
}

void print_freq_graph(vector<pair<char,float>> vfrq){
    float j;
    char aux;
    for (int i = 0; i < vfrq.size(); i++)
    {
        for (j = 0; j < get<1>(vfrq[i]) * 1000.00; j++)
        {
            if(i&1)
                aux = '~';
            else
                aux = '-';
            std::cout << aux;
        }
        std::cout << '|'<< endl;
    }
}

// decrypts message by freq analysis based on GLOBAL vars (ENG, PT)
string break_vigenere(string data, int keySize, vector<pair<char,float>> table){
    int dataSize = data.size();
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    string nGroup, dec, k;
int shift;

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < dataSize; i += keySize) //right?? Tested, yeah
        {
            nGroup += data[i];
        }
        nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
        
// GETTING frequency& asking user to fund the shift
cout << "given the graph above,  in what shift is the graph below?" << endl;
print_freq_graph(nFrequency);
          k += shift + 97; //WHY submittable to change      
    }
    
    cout <<"\nKEY\n" << k << "\n\n"<< endl;
    
    return k;
}

int main(){
    string aux, data, asciiData, enc, key, hk, read, dec;

     key = "akk";
   data = "Three days of rest, three blessed days of rest, are what I had with Wolf Larsen, eating at the cabin  able and doing nothing but discuss life, literature, and the universe, the while Thomas  fumed  and raged and did my work as well as his own. Watch out for squalls, is all I can say to you, was Louis’s warning, given during a spare half-hour on   while Wolf Larsen was engaged in straightening out a row among the hunters. Ye cant tell whatll be happenin, Louis went on, in response to my query for more definite information. The mans as contrary as air currents or water currents. You can never guess the ways Tis just as youre thinkin you know him and are makin a favourable slant along him, that he  hirls around, dead ahead and comes howlin down upon you and arippin";
//   data = "A Itália negociou com os Aliados sua entrada no conflito em abril de 1915.[] Os italianos renunciaram a sua aliança prévia com a Alemanha e Áustria-Hungria em 4 de maio, dando a todos um aviso adiantado de que a Itália estava se preparando para entrar em guerra contra eles. O almirante Anton Haus, Comandante da Marinha Austro-Húngara, fez preparações a fim de enviar suas principais embarcações para o Adriático e realizar um grande ataque contra a Itália assim que a guerra fosse Devido à escassez de carvão e à Barragem de Otranto, os navios foram incapazes de participarem de grandes operações ofensivas depois do ataque a Ancona, assim foram relegados a defender o litoral da Áustria-Hungria. Haus morreu a bordo do Viribus Unitis em fevereiro de 1917, tendo seu funeral sido realizado a bordo do navio com a presença do imperador Carlos I. Haus foi sucedido no comando da marinha pelo almirante Maksimilijan Njegovan, que continuou com a mesma estratégia de seu predecessor de empregar as embarcações austro-húngaras como uma frota de intimidação. O momento mais significativo para o Viribus Unitis nesse período ocorreu em junho de 1917, quando n foi tirado de seu posto em fevereiro de 1918 devido a um motim em Cátaro, O plano de Horthy era atacar a Barragem de Otranto com uma grande frota de couraçados, barcos torpedeiros, contratorpedeiros e cruzadores. O Viribus Unitis e o SMS Prinz Eugen partiram para o sul em 8 de junho, na companhia dos elementos principais de sua frota, enquanto o Tegetthoff, SMS Szent István e suas escoltas partiram logo no dia seguinte. A ideia era que os membros da Classe Tegetthoff se unissem e usassem seu poder de fogo combinado para destruir a barragem e enfrentar quaisquer embarcações aliadas que encontrassem. Em 10 de junho, enquanto o Tegetthoff e o Szent István seguiam para Islana a fim de se encontrarem com seus irmãos, eles foram avistados por duas lanchas torpedeiras italianas voltando de uma patrulha de rotina. O Szent István foi torpedeado duas vezes e naufragou. Horthy, temendo mais ataques de lanchas ou contratorpedeiros italianos, além da chegada de possíveis couraçados Aliados, achou que o eleme sendo substituído pelo contra-almirante Miklós Horthy. Este começou a reorganizar a marinha de acordo com sua visão, também tirando a frota do porto com o objetivo de realizar exercícios de manobra e artilharia regularmente. Foram as maiores operações que a marinha tinha feito desde o início da guerra. Essas ações tinham a intenção de restaurar a ordem depois de vários motins fracassados, mas também de preparar a frota para uma grande operação ofensiva. Horthy resolveu realizar uma grande ofensiva com a frota a fim de abordar a moral baixa e o tédio dos marinheiros, além de facilitar a saída de u-boots austro-húngaros e alemães do Adriático para o Mediterrâneo. Ele concluiu que a frota estava pronta depois de meses de exercícios, marcando a ofensiva para o início de junho de 191 Carlos realizou uma revista formal da frota e visitou o couraçado. Além dessas visitas, as únicas outras ações de que a base naval de Pola e o Viribus Unitis participaram desde o bombardeio de Ancona foi enfrentar mais de oitenta ataques aéreos realizados pelo recém-formado Corpo Aeronáutico Militar italiano  declarada. A dgara partiu para Brindisi a fim de encontrar-se com os alemães e escoltá-los até um porto aliado na Áustria-Hungria. Os alemães acabaram seguindo para o Império Otomano e a frota austro-húngara, em vez de acompanhá-los até o Mar Negro, voltou para sua base naval em Pola.";

    enc = vigenere("encrypt", data, key);
    dec =  vigenere("decrypt", enc, key);

 cout << dec << endl << endl;
 cout << enc << endl << endl;
 cout << data << endl << endl;
 break_vigenere(data,key.size(),ENG);

  return 0;
}
