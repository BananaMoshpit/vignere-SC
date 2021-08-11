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

int first_char(vector<pair<char,float>> data, char c){
    auto it = std::find_if(data.begin(), data.end(), [&c](const pair<char, float>& e) {return get<0>(e) == c; } );
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
   // nasw = make_pair(key, fitness);
    return make_pair(key, fitness);
    
}
// only frequency of all letters(lower +upper) without any special characters
vector<pair<char,float>> alpha_frequency(vector<pair<char,float>> nFrequency){
    int idxAlpha, size, i;
    char alpha;
    size = nFrequency.size();
    sort(nFrequency.begin(), nFrequency.end()); // sorting pairs by ascii char 

    idxAlpha = first_alpha(nFrequency);
    nFrequency.erase(nFrequency.begin(), nFrequency.begin() + idxAlpha);
    alpha = get<0>(nFrequency[idxAlpha]);

   // idxAlphaSizeData = data.size() -  idxAlpha; // TEST ON DATA[0] = 'A' // amount of different letters in data
    if ('A' <= alpha && alpha <= 'Z'  )
    {
        while(alpha <= 'Z' && idxAlpha < size){ // putting uppercase freq in lower case letter

        }
    }
    

    
    while (i <= 122)
    {
        /* code */
    }
    
    
    return nFrequency;
}
string break_vigenere(int opt, string data, int keySize){
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    float bestMatch;
    vector<vector<pair<char,float>>> allGroupsFrequencies;
    string nGroup;
    string dec;
    string k;

    for (int keyN = 1; keyN <= keySize; keyN++)
    {
        nGroup.clear();
        for(int i = keyN - 1; i < data.size(); i += keySize)
        {
            nGroup += data[i];
        }
        std::cout << nGroup << " "; // n-split string , ie 11 from a1a1 w keySize 2
        nFrequency = get_frequency(nGroup);// freq analysis from nGroup characters
        sort(nFrequency.begin(), nFrequency.end()); // sorting by letter a->z
        
        key = find_shift(nFrequency, ENG);
        std::cout << "KEY FOUND " << get<0>(key) << get<1>(key) << endl;
        //shifted_freq(nFrequency,0,ENG);
    k += get<0>(key);
    }
    
    std::cout <<"\nKEY\n" << k << "\n\n"<< endl;
    
    dec = vigenere("decrypt", data,  k);
    return dec;
}

int main(){
    string aux, data, enc, key, hk;


/*     ifstream nameFileout;
    string line;
    nameFileout.open("in.txt");
    while (getline(nameFileout, line))
    {
        cout << data;
    }
    nameFileout.close();
 */
     key = "amha";
    data = "ohtheblazingtropicnightwhenthewakesaweltoflightthatholdsthehotskytameandthesteadyforefootsnoresthroughtheplanet-powderedfloorswherethescaredwhaleflukesinflame.herplatesarescarredbythesundearlassandherropesaretautwiththedewforwereboomingdownontheoldtrailourowntrailtheouttrailweresaggingsouthonthelongtrailthetrailthatisalwaysnewsometimesithinkwolflarsenmadorhalfmadatleastwhatofhisstrangemoodsandvagariesatothertimesitakehimforagreatmanageniuswhohasneverarrivedandfinallyiamconvincedthatheistheperfecttypeoftheprimitivemanbornathousandyearsorgenerationstoolateandananachronisminthisculminatingcenturyofcivilizationheiscertainlyanindividualistofthemostpronouncedtypenotonlythatbutheisverylonelythereisnocongenialitybetweenhimandtherestofthemenaboardshiphistremendousvirilityandmentalstrengthwallhimaparttheyaremorelikechildrentohimeventhehuntersandaschildrenhetreatsthemdescendingperforcetotheirlevelandplayingwiththemasamanplayswithpuppiesorelseheprobesthemwiththecruelhandofavivisectionistgropingaboutintheirmentalprocessesandexaminingtheirsoulsasthoughtoseeofwhatsoulstuffismade"; 
    data = "I have seen him a score of times, at table, insulting this hunter or that, with cool and level eyes and, withal, a certain air of interest, pondering their actions or replies or petty rages with a curiosity almost laughable to me who stood onlooker and who understood. Concerning his own rages, I am convinced that they are not real, that they are sometimes experiments, but that in the main they are the habits of a pose or attitude he has seen fit to take toward his fellow-men. I know, with the possible exception of the incident of the dead mate, that I have not seen him really angry; nor do I wish ever to see him in a genuine rage, when all the force of him is called into play.While on the question of vagaries, I shall tell what befell Thomas Mugridge in the cabin, and at the same time complete an incident upon which I have already touched once or twice. The twelve o’clock dinner was over, one day, and I had just finished putting the cabin in order, when Wolf Larsen and Thomas Mugridge descended the companion stairs. Though the cook had a cubby-hole of a state-room opening off from the cabin, in the cabin itself he had never dared to linger or to be seen, and he flitted to and fro, once or twice a day, a timid spectre.“So you know how to play ‘Nap,’” Wolf Larsen was saying in a pleased sort of voice. “I might have guessed an Englishman would know. I learned it myself in English ships.”Thomas Mugridge was beside himself, a blithering imbecile, so pleased was he at chumming thus with the captain. The little airs he put on and the painful striving to assume the easy carriage of a man born to a dignified place in life would have been sickening had they not been ludicrous. He quite ignored my presence, though I credited him with being simply unable to see me. His pale, wishy-washy eyes were swimming like lazy summer seas, though what blissful visions they beheld were beyond my imagination.“Get the cards, Hump,” Wolf Larsen ordered, as they took seats at the table. “And bring out the cigars and the whisky you’ll find in my berth.”I returned with the articles in time to hear the Cockney hinting broadly that there was a mystery about him, that he might be a gentleman’s son gone wrong or something or other; also, that he was a remittance man and was paid to keep away from England—“p’yed ’ansomely, sir,” was the way he put it; “p’yed ’ansomely to sling my ’ook an’ keep slingin’ it.”I had brought the customary liquor glasses, but Wolf Larsen frowned, shook his head, and signalled with his hands for me to bring the tumblers. These he filled two-thirds full with undiluted whisky—“a gentleman’s drink?” quoth Thomas Mugridge,—and they clinked their glasses to the glorious game of “Nap,” lighted cigars, and fell to shuffling and dealing the cards.They played for money. They increased the amounts of the bets. They drank whisky, they drank it neat, and I fetched more. I do not know whether Wolf Larsen cheated or not,—a thing he was thoroughly capable of doing,—but he won steadily. The cook made repeated journeys to his bunk for money. Each time he performed the journey with greater swagger, but he never brought more than a few dollars at a time. He grew maudlin, familiar, could hardly see the cards or sit upright. As a preliminary to another journey to his bunk, he hooked Wolf Larsen’s buttonhole with a greasy forefinger and vacuously proclaimed and reiterated, “I got money, I got money, I tell yer, an’ I’m a gentleman’s son.”Wolf Larsen was unaffected by the drink, yet he drank glass for glass, and if anything his glasses were fuller. There was no change in him. He did not appear even amused at the other’s antics.In the end, with loud protestations that he could lose like a gentleman, the cook’s last money was staked on the game—and lost. Whereupon he leaned his head on his hands and wept. Wolf Larsen looked curiously at him, as though about to probe and vivisect him, then changed his mind, as from the foregone conclusion that there was nothing there to probe.“Hump,” he said to me, elaborately polite, “kindly take Mr. Mugridge’s arm and help him up on deck. He is not feeling very well.”“And tell Johnson to douse him with a few buckets of salt water,” he added, in a lower tone for my ear alone.I left Mr. Mugridge on deck, in the hands of a couple of grinning sailors who had been told off for the purpose. Mr. Mugridge was sleepily spluttering that he was a gentleman’s son. But as I descended the companion stairs to clear the table I heard him shriek as the first bucket of water struck him.Wolf Larsen was counting his winnings.“One hundred and eighty-five dollars even,” he said aloud. “Just as I thought. The beggar came aboard without a cent.”“And what you have won is mine, sir,” I said boldly.He favoured me with a quizzical smile. “Hump, I have studied some grammar in my time, and I think your tenses are tangled. ‘Was mine,’ you should have said, not ’is mine.’”“It is a question, not of grammar, but of ethics,” I answered.It was possibly a minute before he spoke.“D’ye know, Hump,” he said, with a slow seriousness which had in it an indefinable strain of sadness, “that this is the first time I have heard the word ‘ethics’ in the mouth of a man. You and I are the only men on this ship who know its meaning.”“At one time in my life,” he continued, after another pause, “I dreamed that I might some day talk with men who used such language, that I might lift myself out of the place in life in which I had been born, and hold conversation and mingle with men who talked about just such things as ethics. And this is the first time I have ever heard the word pronounced. Which is all by the way, for you are wrong. It is a question neither of grammar nor ethics, but of fact.”“I understand,” I said. “The fact is that you have the money.”His face brightened. He seemed pleased at my perspicacity. “But it is avoiding the real question,” I continued, “which is one of right.”“Ah,” he remarked, with a wry pucker of his mouth, “I see you still believe in such things as right and wrong.”“But don’t you?—at all?” I demanded.“Not the least bit. Might is right, and that is all there is to it. Weakness is wrong. Which is a very poor way of saying that it is good for oneself to be strong, and evil for oneself to be weak—or better yet, it is pleasurable to be strong, because of the profits; painful to be weak, because of the penalties. Just now the possession of this money is a pleasurable thing. It is good for one to possess it. Being able to possess it, I wrong myself and the life that is in me if I give it to you and forego the pleasure of possessing it.”“But you wrong me by withholding it,” I objected.“Not at all. One man cannot wrong another man. He can only wrong himself. As I see it, I do wrong always when I consider the interests of others. Don’t you see? How can two particles of the yeast wrong each other by striving to devour each other? It is their inborn heritage to strive to devour, and to strive not to be devoured. When they depart from this they sin.”“Then you don’t believe in altruism?” I asked.He received the word as if it had a familiar ring, though he pondered it thoughtfully. “Let me see, it means something about coöperation, doesn’t it?”“Well, in a way there has come to be a sort of connection,” I answered unsurprised by this time at such gaps in his vocabulary, which, like his knowledge, was the acquirement of a self-read, self-educated man, whom no one had directed in his studies, and who had thought much and talked little or not at all. “An altruistic act is an act performed for the welfare of others. It is unselfish, as opposed to an act performed for self, which is selfish.”He nodded his head. “Oh, yes, I remember it now. I ran across it in Spencer.”“Spencer!” I cried. “Have you read him?”“Not very much,” was his confession. “I understood quite a good deal of First Principles, but his Biology took the wind out of my sails, and his Psychology left me butting around in the doldrums for many a day. I honestly could not understand what he was driving at. I put it down to mental deficiency on my part, but since then I have decided that it was for want of preparation. I had no proper basis. Only Spencer and myself know how hard I hammered. But I did get something out of his Data of Ethics. There’s where I ran across ‘altruism,’ and I remember now how it was used.”I wondered what this man could have got from such a work. Spencer I remembered enough to know that altruism was imperative to his ideal of highest conduct. Wolf Larsen, evidently, had sifted the great philosopher’s teachings, rejecting and selecting according to his needs and desires.“What else did you run across?” I asked.His brows drew in slightly with the mental effort of suitably phrasing thoughts which he had never before put into speech. I felt an elation of spirit. I was groping into his soul-stuff as he made a practice of groping in the soul-stuff of others. I was exploring virgin territory. A strange, a terribly strange, region was unrolling itself before my eyes.“In as few words as possible,” he began, “Spencer puts it something like this: First, a man must act for his own benefit—to do this is to be moral and good. Next, he must act for the benefit of his children. And third, he must act for the benefit of his race.”“And the highest, finest, right conduct,” I interjected, “is that act which benefits at the same time the man, his children, and his race.”“I wouldn’t stand for that,” he replied. “Couldn’t see the necessity for it, nor the common sense. I cut out the race and the children. I would sacrifice nothing for them. It’s just so much slush and sentiment, and you must see it yourself, at least for one who does not believe in eternal life. With immortality before me, altruism would be a paying business proposition. I might elevate my soul to all kinds of altitudes. But with nothing eternal before me but death, given for a brief spell this yeasty crawling and squirming which is called life, why, it would be immoral for me to perform any act that was a sacrifice. Any sacrifice that makes me lose one crawl or squirm is foolish,—and not only foolish, for it is a wrong against myself and a wicked thing. I must not lose one crawl or squirm if I am to get the most out of the ferment. Nor will the eternal movelessness that is coming to me be made easier or harder by the sacrifices or selfishnesses of the time when I was yeasty and acrawl.”“Then you are an individualist, a materialist, and, logically, a hedonist.”“Big words,” he smiled. “But what is a hedonist?”He nodded agreement when I had given the definition. “And you are also,” I continued, “a man one could not trust in the least thing where it was possible for a selfish interest to intervene?”“Now you’re beginning to understand,” he said, brightening.“You are a man utterly without what the world calls morals?”“That’s it.”“A man of whom to be always afraid—”“That’s the way to put it.”“As one is afraid of a snake, or a tiger, or a shark?”“Now you know me,” he said. “And you know me as I am generally known. Other men call me ‘Wolf.’”“You are a sort of monster,” I added audaciously, “a Caliban who has pondered Setebos, and who acts as you act, in idle moments, by whim and fancy.”His brow clouded at the allusion. He did not understand, and I quickly learned that he did not know the poem.“I’m just reading Browning,” he confessed, “and it’s pretty tough. I haven’t got very far along, and as it is I’ve about lost my bearings.”Not to be tiresome, I shall say that I fetched the book from his state-room and read “Caliban” aloud. He was delighted. It was a primitive mode of reasoning and of looking at things that he understood thoroughly. He interrupted again and again with comment and criticism. When I finished, he had me read it over a second time, and a third. We fell into discussion—philosophy, science, evolution, religion. He betrayed the inaccuracies of the self-read man, and, it must be granted, the sureness and directness of the primitive mind. The very simplicity of his reasoning was its strength, and his materialism was far more compelling than the subtly complex materialism of Charley Furuseth. Not that I—a confirmed and, as Furuseth phrased it, a temperamental idealist—was to be compelled; but that Wolf Larsen stormed the last strongholds of my faith with a vigour that received respect, while not accorded conviction.Time passed. Supper was at hand and the table not laid. I became restless and anxious, and when Thomas Mugridge glared down the companion-way, sick and angry of countenance, I prepared to go about my duties. But Wolf Larsen cried out to him:“Cooky, you’ve got to hustle to-night. I’m busy with Hump, and you’ll do the best you can without him.”And again the unprecedented was established. That night I sat at table with the captain and the hunters, while Thomas Mugridge waited on us and washed the dishes afterward—a whim, a Caliban-mood of Wolf Larsen’s, and one I foresaw would bring me trouble. In the meantime we talked and talked, much to the disgust of the hunters, who could not understand a word.";
    
    enc = vigenere("encrypt", data, key);
    hk = break_vigenere(0, enc, key.size());
   // cout << "data   " << data << endl;
   // cout << "enc    " << enc << endl;
   // cout << "hk     " << hk << endl;
 
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
        {'1', 	12.702 / 100},
        {'9', 	12.702 / 100},
        {'#', 	12.702 / 100},
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
    alpha_frequency(testENG);
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