#include <bits/stdc++.h>

using namespace std;

char FIRST_CHAR = 32; // space
char LAST_CHAR = 122; // 'z'
ofstream out("output.txt");

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
        i += count ;
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

bool tuple_sort_sec(const tuple<char , float>& a,
               const tuple<char , float>& b)
{
    return (get<1>(a) > get<1>(b));
}

string break_vigenere(int opt, string data, int keySize, string reKey){
    vector<tuple<char,float>> nFrequency;
    vector<vector<tuple<char,float>>> allGroupsFrequencies;
    char hlp;
    string nGroup, key;
    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < data.size(); i += keySize)
        {
            nGroup += static_cast<int>(data[i]);
        }
        out << nGroup << " ";
        nFrequency = get_frequency(nGroup);
        switch (keyN)
        {
        case 1:
        hlp = vigenere("decrypt", static_cast<string>(get<0>(nFrequency[0])),"k")[0];
            key += find_key(hlp ,'get<0>(nFrequency[0]));
            break;
                case 2:
                hlp = vigenere("decrypt", get<0>(nFrequency[0],"e"))[0];
            key += find_key(hlp ,'get<0>(nFrequency[0]));
            break;
                case 3:
                hlp = vigenere("decrypt", get<0>(nFrequency[0],"y"))[0];
            key += find_key(hlp ,'get<0>(nFrequency[0]));
            break;
        
        default:
        key += "!!";
            break;
        }
/*         sort(nFrequency.begin(), nFrequency.end(), tuple_sort_sec);
        key += find_key('e', get<0>(nFrequency[0])); */
    }
    
    cout << "\n\n !!! KEYKEY >> "<< key << "\n\n " << endl;
    return reKey;
}

void find_shift(vector<tuple<char,float>> data){
    
}

int main(){
    string aux, key;

    

    aux = "radarZmonkeyZsomeoneZissueZcoachZbrainZrareZcautionZcertainZwhaleZmatterZtoolZvisitZgirlZstateZflockZmerryZmushroomZtattooZauditZjunkZsirenZvirusZevidenceZjoinZbenefitZlabZgasZmethodZpenaltyZdebateZfanZcauseZpeaceZstoryZneitherZvolcanoZtrafficZbringZmuchZsectionZfenceZarmedZfeeZvesselZdwarfZearthZtwelveZbirthZfingerZmaterialZomitZacousticZmonsterZvolcanoZsilentZinnocentZdollZforumZloanZswallowZreviewZchurnZgymZoceanZfameZarmorZoldZquizZpumpkinZcountryZtellZfacultyZdemandZweatherZwaterZunfairZrewardZsituateZtorchZbraveZgunZshipZorangeZfatigueZdropZbubbleZbreadZvoiceZmedalZexplainZvillageZnobleZhugeZarrowZcardarrowZtorchZvendorZweirdZquizZneitherZsituateZsuchZsystemZravenZdieselZtextZtrayZdifferZamongZsuspectZaskZbargainZbundleZsilentZriskZjustZbeautyZembarkZpulseZpoleZincreaseZtowardZfuelZkiteZjeansZcheapZeffortZevolveZchampionZmailZspellZcardZcarryZclusterZhalfZunknownZtackleZclumpZimmuneZwishZwolfZbelow";
    aux = "not very enticingly authoritative";
    aux = vigenere("encrypt", aux, "hello");
    key = break_vigenere(0, aux, 5, "hello");
    cout << vigenere("decrypt", aux, key) << endl;
    cout << "\n"<< vigenere("decrypt", aux, "hello") << endl;

   /*  cout << find_key( 'B',encrypt('B', 215)) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    aux = vigenere( "encrypt", "HELLOSDKFJHG", "SDBNO");
    cout << aux << endl; //zhmyckglsxzj 
    aux = vigenere( "decrypt", aux, "SDBNO");

    cout << encrypt('B', 'C') << endl; //zhmyckglsxzj 

    get_frequency("w1rrr3aaaa4");
    break_vigenere(0, "azbycx", 2);
    break_vigenere(0, "abcdefabcdefabcdefabcdeff1", 6); */
    out.close();
  return 0;
}

/* BUG REPORT : FIXED, :: INPUT CHARA OVERFLOW-- MUST PASS A\SCII VAL IE 215 INSTREAD OF ×
char LAST_CHAR = 221+;
    cout << find_key( 'B',encrypt('B', 'C')) << endl;
    cout << find_key( '!',encrypt('!', '@')) << endl;
    cout << find_key( 'z',encrypt('z', '-')) << endl;

    !!WRONG KEYS FOUND
    
 */