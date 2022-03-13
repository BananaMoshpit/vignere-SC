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

float shifted_freq( vector<pair<char,float>> data, int shift,vector<pair<char,float>> table) {
    int turnAround, sizeData, i;
    float diffSum, diff;
    sort(data.begin(), data.end()); // by letter
    diffSum = 0; i = 0; turnAround = 0; sizeData = data.size();
    
     while (i < F_TABLE_SIZE && turnAround < sizeData) 
    {
        if(shift + i < sizeData){
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
pair<char,float> find_shift(vector<pair<char,float>> nFrequency, vector<pair<char,float>> table){
    int shift,freqSize ;
    float aux, fitness;
    char key, cipherA;
    freqSize = nFrequency.size();
    fitness = 999;
    shift = FIRST_CHAR;
 
        for (int i = 0; i < freqSize; i++)
        {
            aux = shifted_freq(nFrequency,i,ENG);
            if(aux < fitness){
                shift = i;
                fitness = aux;
            }
        }
    
    cipherA = get<0>(nFrequency[0 + shift - 1]); 
    key = find_key(get<0>(table[0]), cipherA);
    return make_pair(key, fitness);
    
}

void print_freq_graph(vector<pair<char,float>> vfrq){
    float j;
    for (int i = 0; i < vfrq.size(); i++)
    {
        for (j = 0; j < get<1>(vfrq[i]) * 1000.00; j++)
        {
            std::cout << '-';
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

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < dataSize; i += keySize)
        {
            nGroup += data[i];
        }
        nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
        print_freq_graph(nFrequency);
        key = find_shift(nFrequency, table);
        k += get<0>(key);
    }
    
    cout <<"\nKEY\n" << k << "\n\n"<< endl;
    
   // dec = vigenere("decrypt", data,  k);
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
        if( 65 <= aux  && aux < 122 ){
          if (65 <= aux && aux <= 90) // converts upper to lowercase
          {
              aux = tolower(aux);
          }
            
          ascii += aux;
        }
    }
    return ascii;
}

int main(){
    string aux, data, asciiData, enc, key, hk, read, dec;
    ofstream out("out.txt", ofstream::out | ofstream::trunc);


//   data = read_from_in("in.txt"); 
//    asciiData = get_ASCII(data);
    //asciiData = get_ASCII(data);
    print_freq_graph(PT);

   key = "a";
    data = "Á";
    enc = vigenere("encrypt", data, key);
    dec =  vigenere("decrypt", enc, key);
   cout <<  data << endl;
   cout << enc << endl;
   cout << dec << endl;


   //data = "Three days of rest, three blessed days of rest, are what I had with Wolf Larsen, eating at the cabin  able and doing nothing but discuss life, literature, and the universe, the while Thomas  fumed  and raged and did my work as well as his own. Watch out for squalls, is all I can say to you, was Louis’s warning, given during a spare half-hour on   while Wolf Larsen was engaged in straightening out a row among the hunters. Ye cant tell whatll be happenin, Louis went on, in response to my query for more definite information. The mans as contrary as air currents or water currents. You can never guess the ways Tis just as youre thinkin you know him and are makin a favourable slant along him, that he  hirls around, dead ahead and comes howlin down upon you and arippin";
//   data = "A Itália negociou com os Aliados sua entrada no conflito em abril de 1915.[] Os italianos renunciaram a sua aliança prévia com a Alemanha e Áustria-Hungria em 4 de maio, dando a todos um aviso adiantado de que a Itália estava se preparando para entrar em guerra contra eles. O almirante Anton Haus, Comandante da Marinha Austro-Húngara, fez preparações a fim de enviar suas principais embarcações para o Adriático e realizar um grande ataque contra a Itália assim que a guerra fosse Devido à escassez de carvão e à Barragem de Otranto, os navios foram incapazes de participarem de grandes operações ofensivas depois do ataque a Ancona, assim foram relegados a defender o litoral da Áustria-Hungria. Haus morreu a bordo do Viribus Unitis em fevereiro de 1917, tendo seu funeral sido realizado a bordo do navio com a presença do imperador Carlos I. Haus foi sucedido no comando da marinha pelo almirante Maksimilijan Njegovan, que continuou com a mesma estratégia de seu predecessor de empregar as embarcações austro-húngaras como uma frota de intimidação. O momento mais significativo para o Viribus Unitis nesse período ocorreu em junho de 1917, quando n foi tirado de seu posto em fevereiro de 1918 devido a um motim em Cátaro, O plano de Horthy era atacar a Barragem de Otranto com uma grande frota de couraçados, barcos torpedeiros, contratorpedeiros e cruzadores. O Viribus Unitis e o SMS Prinz Eugen partiram para o sul em 8 de junho, na companhia dos elementos principais de sua frota, enquanto o Tegetthoff, SMS Szent István e suas escoltas partiram logo no dia seguinte. A ideia era que os membros da Classe Tegetthoff se unissem e usassem seu poder de fogo combinado para destruir a barragem e enfrentar quaisquer embarcações aliadas que encontrassem. Em 10 de junho, enquanto o Tegetthoff e o Szent István seguiam para Islana a fim de se encontrarem com seus irmãos, eles foram avistados por duas lanchas torpedeiras italianas voltando de uma patrulha de rotina. O Szent István foi torpedeado duas vezes e naufragou. Horthy, temendo mais ataques de lanchas ou contratorpedeiros italianos, além da chegada de possíveis couraçados Aliados, achou que o eleme sendo substituído pelo contra-almirante Miklós Horthy. Este começou a reorganizar a marinha de acordo com sua visão, também tirando a frota do porto com o objetivo de realizar exercícios de manobra e artilharia regularmente. Foram as maiores operações que a marinha tinha feito desde o início da guerra. Essas ações tinham a intenção de restaurar a ordem depois de vários motins fracassados, mas também de preparar a frota para uma grande operação ofensiva. Horthy resolveu realizar uma grande ofensiva com a frota a fim de abordar a moral baixa e o tédio dos marinheiros, além de facilitar a saída de u-boots austro-húngaros e alemães do Adriático para o Mediterrâneo. Ele concluiu que a frota estava pronta depois de meses de exercícios, marcando a ofensiva para o início de junho de 191 Carlos realizou uma revista formal da frota e visitou o couraçado. Além dessas visitas, as únicas outras ações de que a base naval de Pola e o Viribus Unitis participaram desde o bombardeio de Ancona foi enfrentar mais de oitenta ataques aéreos realizados pelo recém-formado Corpo Aeronáutico Militar italiano  declarada. A dgara partiu para Brindisi a fim de encontrar-se com os alemães e escoltá-los até um porto aliado na Áustria-Hungria. Os alemães acabaram seguindo para o Império Otomano e a frota austro-húngara, em vez de acompanhá-los até o Mar Negro, voltou para sua base naval em Pola.";
//   enc = vigenere("encrypt", data, key);
//   dec = vigenere("decrypt", enc, key);
//   out << break_vigenere("ABCDEFG", key.size(), ENG );
   //cout << enc;
    //data = "tpsja kexis ttgztpb wq ssmil tfdxf vsetw ytafrttw btzf pcbroxdzo zn tqac wix, bwfd s, je ahvup sd pcbqqxff lfzed d avu ytwoxavneh sg p aznst qaghv. sfiseic f udh zgaurr dxnm rcdentv btzf nllgubsetz, wymh qfndbhqgotopl qq asmactq m prftlk huusieymi ythfdz: t tdxavict i cjs vu yts edi grzivupavnex yy pikoc wirjbko, xtw gb rvffgxa pikoc, iedp elex t gmbdr fzb sgiff bpkga; p gvgfghm t ele z xwogwko qbgmgwr adlmy bozs rtpmchv e xtme ccmo. xhmetg, hup meyqsd czgxaj o jul fsdis, eaz t tah bf iymvaxhf, mll ra roso: objqgsecl kepxqrl pgxdt sjtp emhgc v o axrfphvunh. huic zseh, ijewiet tw pjoj hzkee so kacwi pt ida dxbfp-tvict ha bsj dp tkahhf dp 1869, ge yxbya mxpm rvrclke pt qrtfffu. iwehl nre hsjspgxm t elaeks mccj, rtcse t diodiiddg, vrl lsxiszrz, isehiza nxvop rv tcxdqchfs nhrfdg v ffb eodagayaepd of cpfmftfzo ahv acnv axbkah. cezp tquvcj! vpkhmss v qfx rmd vfugx gmghrs yxq mciecthw. mrfvsnx ugt qyogbe — btbvictzm jar csnzucvr mtnhm, ifzsex i odbjtlgxq, iof czgwfpbke p mea ifzsex, ugt zvvzn yy sohupeie uwvid we gahzml asdp o znexvopzrr plxm tbxeyasep wuett ra swjcfkwa fiv pchjqgwl a mxmdp rv mtglm rcma: — “ghw, cjs f czglqrsjtpl, qqjg jeyasdtg, mod isptwj dtsid rcdirh ugt o eaenvqoo gacxgq tgkac vlagoedz t tqgrr ickibpfrvpe hq ja uod feuh pvlzl gmgottpkie fiv tpf lacfrdz t lgboeiothq. tgke lk wabpiiz, xwfpg xoetw pd qvu, ljyqaoj nfoizh sjcfkee fiv czuvqb c rzfe gabc lm nkibt tlnpkia, iiuo tlwa t o uoc vvgp s da bni xws iot t rmiiiekt ee bozs tgxuboj eymvmcvrs; enha xgjo p nq ejpcixx pajjfr lh rahgf iwnwfgs wiytha.” qcd e qbix pazgz! gea, cof mp tvdtdvnoh hmh jznex ebdzzcpl ugt zye oxmjtw. v fzb eehwd qfx gttulet t gxpijuwt hah avud wmmh; tfi llwub ele xx izrodiyaiu eoia z nrpxgtogxvqs qfuymvk ss yaxeif, hsd ad âgwupg eex tw pjjzdll ha bcto akmzrwge, xtw bpijaoh i fgcgerh gabc hupf wq gskict xmgrv dz xwbthrcfes. fpfue p tfagfvctws. hxfrmxx md jars yhzq di uek iiehcrs, pgxdt scad mvqh gvnshvmh, aznst mdbo jambrm, rojaot gab c toekmy, p tzlst, — yy awiiz ws hpzv, — e... exrtpa ganbizrwr! dljyu p dfunh pttg uicxm cjsd ect e ftftetke etbyoct. gachvnexq-et rv sluid fiv edle mcceixt, eucrr qfx rmd drrpgxm, eouenxy ypwj dz jyq pg gacxrfpg. v vpkhmss, gaoxgqj arid. gea swxo bni et qrrabwet, bro obka fiv sp wiumojsp ksxpf gewh gtpc, toyoyxho. eex h qqj csieh idp qfidt exiodeymi pgodaebgm... ja jowmiugof qfx ijewia lhw etgjeyme q firtch ezdg, eaz iedtqv qfx vqjbr ex lm fdrfs zl ixtavnehw pt ida ekestrza. p wepd ele dbq, a fiv mpgse rcevtglm p sjsl tracwda pke meoieyme-xd. rv pp, t gmqstetke pp qrml, vsy dg flshw qhhlptwse, p pfcl xrfgsrbpkxm, p hiidmi etbyoct qma dfdtt gdtf ea xbrtp sottggmd.";
  //  hk = break_vigenere(enc, key.size(), ENG);
 /*    cout << hk << endl;
    cout << key << endl; */
//out << enc << endl;
/* cout << data.compare(dec) << endl;
out << asciiData << endl;
out << dec << endl;
out << break_vigenere(enc, key.size(), ENG ) << endl;
out << break_vigenere(asciiData, key.size(), ENG ) << endl; */
//out << data;
//  //   out << hk;
//   out << dec;
//    out.close(); 

  return 0;
}
