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

const static char FIRST_CHAR = 0; //
const static char LAST_CHAR = 255; // 
const static int F_TABLE_SIZE = 26;

// encrypts data from a key
char encrypt(char data, char key){
    char enc = data + key - FIRST_CHAR; 
    if(enc > LAST_CHAR) { // keep from trespassing alphabet boundaries
        enc += FIRST_CHAR - LAST_CHAR - 1;
    }
  return  static_cast<char>(enc);  
}

// ENC[I] =  data[i] + key[k]  - LAST_CHAR - 1 -> data[i] = - key[k]  + LAST_CHAR - enc[i] + 1
//  L + Y - Z - 1 = J -> L = J - Y + 1
// decrypts cipher from key
char decrypt(char enc, char key){
    char dec = enc - key + FIRST_CHAR;             
    if(dec < FIRST_CHAR){ // keep from trespassing alphabet boundaries
        dec =  enc - key  + LAST_CHAR + 1;      //  L + Y - Z - 1 = J -> L = J - Y + 1  
    }
  return static_cast<char>(dec); 
}

// encrypts or decrypts a string from a key 
string vigenere(string opt, string data, string key){
    int keySize, k;
    long int dataSize, i;
    char aux;
    string vig;
    dataSize = data.size(); keySize = key.size();

    for (i = 0, k = 0; i < dataSize; i++)
    {
        if(opt == "encrypt"){
            aux = encrypt(data[i], key[k]);
        }
        else if (opt == "decrypt") {
            aux = decrypt(data[i], key[k]);
        }
        
        vig[i] += static_cast<char>(aux);
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
// decrypts message by freq analysis based on GLOBAL vars (ENG, PT)
string break_vigenere(string data, int keySize, vector<pair<char,float>> table){
    int dataSize = data.size();
    vector<pair<char,float>> nFrequency;
    pair<char,float> key;
    vector<vector<pair<char,float>>> allGroupsFrequencies;
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
        key = find_shift(nFrequency, table);
        k += get<0>(key);
    }
    
    cout <<"\nKEY\n" << k << "\n\n"<< endl;
    
    dec = vigenere("decrypt", data,  k);
    return dec;
}
//reads text and ignores spaces
string read_from_in(string fileName){
    string data, read;
   fstream in;
    in.open(fileName);
    while (getline(in, read))
    {
        for (int i = 0; i < read.size(); i++)
        {
            if ( read[i] != ' '){
                data += read;
            }
            
        }
        
    }
    in.close();
    return data;
}

string get_ASCII( string data){
    string ascii;
    for (int i = 0; i < data.size(); i++)
    {
        if( 0 < data[i]  && data[i] < 127 ){
          ascii += data[i];
        }
    }
    return ascii;
}

int main(){
    string aux, data, asciiData, enc, key, hk, read;
    ofstream out("out.txt", ofstream::out | ofstream::trunc);

    data = read_from_in("in.txt");

    asciiData = get_ASCII(data);

    key = "1la";
 
    //data = " Three days of rest, three blessed days of rest, are what I had with Wolf Larsen, eating at the cabin  able and doing nothing but discuss life, literature, and the universe, the while Thomas Mugridge fumed  nd raged and did my work as well as his own. Watch out for squalls, is all I can say to you, was Louis’s warning, given during a spare half-hour on  eck while Wolf Larsen was engaged in straightening out a row among the hunters. Ye can’t tell what’ll be happenin’, Louis went on, in response to my query for more definite information. The man’s as contrary as air currents or water currents. You can never guess the ways iv  im. ’Tis just as you’re thinkin’ you know him and are makin’ a favourable slant along him, that he  hirls around, dead ahead and comes howlin’ down upon you and a-rippin’ all iv your fine-weather sails  o rags. So I was not altogether surprised when the squall foretold by Louis smote me. We had been having a  eated discussion,—upon life, of course,—and, grown over-bold, I was passing stiff strictures upon Wolf  arsen and the life of Wolf Larsen. In fact, I was vivisecting him and turning over his soul-stuff as  eenly and thoroughly as it was his custom to do it to others. It may be a weakness of mine that I have  n incisive way of speech; but I threw all restraint to the winds and cut and slashed until the whole  an of him was snarling. The dark sun-bronze of his face went black with wrath, his eyes were ablaze.  here was no clearness or sanity in them—nothing but the terrific rage of a madman. It was the wolf in  im that I saw, and a mad wolf at that. He sprang for me with a half-roar, gripping my arm. I had steeled myself to brazen it out, though I was  rembling inwardly; but the enormous strength of the man was too much for my fortitude. He had gripped  e by the biceps with his single hand, and when that grip tightened I wilted and shrieked aloud. My feet  ent out from under me. I simply could not stand upright and endure the agony. The muscles refused their  uty. The pain was too great. My biceps was being crushed to a pulp. He seemed to recover himself, for a lucid gleam came into his eyes, and he relaxed his hold with a short  augh that was more like a growl. I fell to the floor, feeling very faint, while he sat down, lighted a  igar, and watched me as a cat watches a mouse. As I writhed about I could see in his eyes that  uriosity I had so often noted, that wonder and perplexity, that questing, that everlasting query of his  s to what it was all about. I finally crawled to my feet and ascended the companion stairs. Fair weather was over, and there was  othing left but to return to the galley. My left arm was numb, as though paralysed, and days passed  efore I could use it, while weeks went by before the last stiffness and pain went out of it. And he had  one nothing but put his hand upon my arm and squeeze. There had been no wrenching or jerking. He had  ust closed his hand with a steady pressure. What he might have done I did not fully realize till next  ay, when he put his head into the galley, and, as a sign of renewed friendliness, asked me how my arm  as getting on. It might have been worse, he smiled. I was peeling potatoes. He picked one up from the pan. It was fair-sized, firm, and unpeeled. He closed  is hand upon it, squeezed, and the potato squirted out between his fingers in mushy streams. The pulpy  emnant he dropped back into the pan and turned away, and I had a sharp vision of how it might have  ared with me had the monster put his real strength upon me. But the three days’ rest was good in spite of it all, for it had given my knee the very chance it  eeded. It felt much better, the swelling had materially decreased, and the cap seemed descending into  ts proper place. Also, the three days’ rest brought the trouble I had foreseen. It was plainly Thomas  ugridge’s intention to make me pay for those three days. He treated me vilely, cursed me continually,  nd heaped his own work upon me. He even ventured to raise his fist to me, but I was becoming  nimal-like myself, and I snarled in his face so terribly that it must have frightened him back. It is  o pleasant picture I can conjure up of myself, Humphrey Van Weyden, in that noisome ship’s galley,  rouched in a corner over my task, my face raised to the face of the creature about to strike me, my  ips lifted and snarling like a dog’s, my eyes gleaming with fear and helplessness and the courage that  omes of fear and helplessness. I do not like the picture. It reminds me too strongly of a rat in a  rap. I do not care to think of it; but it was effective, for the threatened blow did not descend. Thomas Mugridge backed away, glaring as hatefully and viciously as I glared. A pair of beasts is what we  ere, penned together and showing our teeth. He was a coward, afraid to strike me because I had not  uailed sufficiently in advance; so he chose a new way to intimidate me. There was only one galley knife  hat, as a knife, amounted to anything. This, through many years of service and wear, had acquired a  ong, lean blade. It was unusually cruel-looking, and at first I had shuddered every time I used it. The  ook borrowed a stone from Johansen and proceeded to sharpen the knife. He did it with great  stentation, glancing significantly at me the while. He whetted it up and down all day long. Every odd moment he could find he had the knife and stone out and was whetting away. The steel acquired a razor edge. He tried it with the ball of his thumb or across the nail. He shaved hairs from the back of his hand, glanced along the edge with microscopic acuteness, and found, or feigned that he found, always, a  light inequality in its edge somewhere. Then he would put it on the stone again and whet, whet, whet,  ill I could have laughed aloud, it was so very ludicrous. It was also serious, for I learned that he was capable of using it, that under all his cowardice there  as a courage of cowardice, like mine, that would impel him to do the very thing his whole nature protested against doing and was afraid of doing. Cooky’s sharpening his knife for Hump, was being whispered about among the sailors, and some of them twitted him about it. This he took in good part, and  as really pleased, nodding his head with direful foreknowledge and mystery, until George Leach, the erstwhile cabin-boy, ventured some rough pleasantry on the subject. Now it happened that Leach was one of the sailors told off to douse Mugridge after his game of cards  ith the captain. Leach had evidently done his task with a thoroughness that Mugridge had not forgiven,  or words followed and evil names involving smirched ancestries. Mugridge menaced with the knife he was  harpening for me. Leach laughed and hurled more of his Telegraph Hill Billingsgate, and before either he or I knew what had happened, his right arm had been ripped open from elbow to wrist by a quick slash  f the knife. The cook backed away, a fiendish expression on his face, the knife held before him in a position of defence. But Leach took it quite calmly, though blood was spouting upon the deck as generously as water from a fountain. I’m goin’ to get you, Cooky, he said, and I’ll get you hard. And I won’t be in no hurry about it. You’ll  e without that knife when I come for you. So saying, he turned and walked quietly forward. Mugridge’s face was livid with fear at what he had done  nd at what he might expect sooner or later from the man he had stabbed. But his demeanour toward me was  ore ferocious than ever. In spite of his fear at the reckoning he must expect to pay for what he had  one, he could see that it had been an object-lesson to me, and he became more domineering and exultant.  lso there was a lust in him, akin to madness, which had come with sight of the blood he had drawn. He  as beginning to see red in whatever direction he looked. The psychology of it is sadly tangled, and yet   could read the workings of his mind as clearly as though it were a printed book. Several days went by, the Ghost still foaming down the trades, and I could swear I saw madness growing  n Thomas Mugridge’s eyes. And I confess that I became afraid, very much afraid. Whet, whet, whet, it  ent all day long. The look in his eyes as he felt the keen edge and glared at me was positively  arnivorous. I was afraid to turn my shoulder to him, and when I left the galley I went out backwards—to  he amusement of the sailors and hunters, who made a point of gathering in groups to witness my exit.  he strain was too great. I sometimes thought my mind would give way under it—a meet thing on this ship  f madmen and brutes. Every hour, every minute of my existence was in jeopardy. I was a human soul in  istress, and yet no soul, fore or aft, betrayed sufficient sympathy to come to my aid. At times I  hought of throwing myself on the mercy of Wolf Larsen, but the vision of the mocking devil in his eyes  hat questioned life and sneered at it would come strong upon me and compel me to refrain. At other  imes I seriously contemplated suicide, and the whole force of my hopeful philosophy was required to  eep me from going over the side in the darkness of night. Several times Wolf Larsen tried to inveigle me into discussion, but I gave him short answers and eluded  im. Finally, he commanded me to resume my seat at the cabin table for a time and let the cook do my  ork. Then I spoke frankly, telling him what I was enduring from Thomas Mugridge because of the three  ays of favouritism which had been shown me. Wolf Larsen regarded me with smiling eyes. So you’re afraid, eh? he sneered. Yes, I said defiantly and honestly, I am afraid. That’s the way with you fellows, he cried, half angrily, sentimentalizing about your immortal souls and  fraid to die. At sight of a sharp knife and a cowardly Cockney the clinging of life to life overcomes  ll your fond foolishness. Why, my dear fellow, you will live for ever. You are a god, and God cannot be  illed. Cooky cannot hurt you. You are sure of your resurrection. What’s there to be afraid of? You have eternal life before you. You are a millionaire in immortality, and a millionaire whose fortune  annot be lost, whose fortune is less perishable than the stars and as lasting as space or time. It is  mpossible for you to diminish your principal. Immortality is a thing without beginning or end. Eternity  s eternity, and though you die here and now you will go on living somewhere else and hereafter. And it  s all very beautiful, this shaking off of the flesh and soaring of the imprisoned spirit. Cooky cannot  urt you. He can only give you a boost on the path you eternally must tread. Or, if you do not wish to be boosted just yet, why not boost Cooky? According to your ideas, he, too,  ust be an immortal millionaire. You cannot bankrupt him. His paper will always circulate at par. You  annot diminish the length of his living by killing him, for he is without beginning or end. He’s bound  o go on living, somewhere, somehow. Then boost him. Stick a knife in him and let his spirit free. As it  s, it’s in a nasty prison, and you’ll do him only a kindness by breaking down the door. And who knows? it may be a very beautiful spirit that will go soaring up into the blue from that ugly carcass. Boost  im along, and I’ll promote you to his place, and he’s getting forty-five dollars a month. It was plain that I could look for no help or mercy from Wolf Larsen. Whatever was to be done I must do  or myself; and out of the courage of fear I evolved the plan of fighting Thomas Mugridge with his own  eapons. I borrowed a whetstone from Johansen. Louis, the boat-steerer, had already begged me for  ondensed milk and sugar. The lazarette, where such delicacies were stored, was situated beneath the cabin floor. Watching my chance, I stole five cans of the milk, and that night, when it was Louis’s watch on deck, I traded them with him for a dirk as lean and cruel-looking as Thomas Mugridge’s vegetable knife. It was rusty and dull, but I turned the grindstone while Louis gave it an edge. I slept  ore soundly than usual that night. Next morning, after breakfast, Thomas Mugridge began his whet, whet, whet. I glanced warily at him, for   was on my knees taking the ashes from the stove. When I returned from throwing them overside, he was  alking to Harrison, whose honest yokel’s face was filled with fascination and wonder. Yes, Mugridge was saying, an’ wot does ’is worship do but give me two years in Reading. But blimey if I  ared. The other mug was fixed plenty. Should ’a seen ’im. Knife just like this. I stuck it in, like  nto soft butter, an’ the w’y ’e squealed was better’n a tu-penny gaff. He shot a glance in my direction  o see if I was taking it in, and went on. ‘I didn’t mean it Tommy,’ ’e was snifflin’; ‘so ’elp me Gawd,   didn’t mean it!’ ‘I’ll fix yer bloody well right,’ I sez, an’ kept right after ’im. I cut ’im in  ibbons, that’s wot I did, an’ ’e a-squealin’ all the time. Once ’e got ’is ’and on the knife an’ tried  o ’old it. ‘Ad ’is fingers around it, but I pulled it through, cuttin’ to the bone. O, ’e was a sight,   can tell yer. A call from the mate interrupted the gory narrative, and Harrison went aft. Mugridge sat down on the  aised threshold to the galley and went on with his knife-sharpening. I put the shovel away and calmly  at down on the coal-box facing him. He favoured me with a vicious stare. Still calmly, though my heart  as going pitapat, I pulled out Louis’s dirk and began to whet it on the stone. I had looked for almost  ny sort of explosion on the Cockney’s part, but to my surprise he did not appear aware of what I was  oing. He went on whetting his knife. So did I. And for two hours we sat there, face to face, whet,  het, whet, till the news of it spread abroad and half the ship’s company was crowding the galley doors  o see the sight. Encouragement and advice were freely tendered, and Jock Horner, the quiet, self-spoken hunter who looked  s though he would not harm a mouse, advised me to leave the ribs alone and to thrust upward for the  bdomen, at the same time giving what he called the Spanish twist to the blade. Leach, his bandaged arm  rominently to the fore, begged me to leave a few remnants of the cook for him; and Wolf Larsen paused  nce or twice at the break of the poop to glance curiously at what must have been to him a stirring and  rawling of the yeasty thing he knew as life. And I make free to say that for the time being life assumed the same sordid values to me. There was  othing pretty about it, nothing divine—only two cowardly moving things that sat whetting steel upon  tone, and a group of other moving things, cowardly and otherwise, that looked on. Half of them, I am  ure, were anxious to see us shedding each other’s blood. It would have been entertainment. And I do not  hink there was one who would have interfered had we closed in a death-struggle. On the other hand, the whole thing was laughable and childish. Whet, whet, whet,—Humphrey Van Weyden  harpening his knife in a ship’s galley and trying its edge with his thumb! Of all situations this was  he most inconceivable. I know that my own kind could not have believed it possible. I had not been  alled Sissy Van Weyden all my days without reason, and that Sissy Van Weyden should be capable of doing  his thing was a revelation to Humphrey Van Weyden, who knew not whether to be exultant or ashamed. But nothing happened. At the end of two hours Thomas Mugridge put away knife and stone and held out his  and. Wot’s the good of mykin’ a ’oly show of ourselves for them mugs? he demanded. They don’t love us, an’  loody well glad they’d be a-seein’ us cuttin’ our throats. Yer not ’arf bad, ’Ump! You’ve got spunk, as  ou Yanks s’y, an’ I like yer in a w’y. So come on an’ shyke. Coward that I might be, I was less a coward than he. It was a distinct victory I had gained, and I  efused to forego any of it by shaking his detestable hand. All right, he said pridelessly, tyke it or leave it, I’ll like yer none the less for it. And to save his  ace he turned fiercely upon the onlookers. Get outa my galley-doors, you bloomin’ swabs! This command was reinforced by a steaming kettle of water, and at sight of it the sailors scrambled out  f the way. This was a sort of victory for Thomas Mugridge, and enabled him to accept more gracefully  he defeat I had given him, though, of course, he was too discreet to attempt to drive the hunters away. I see Cooky’s finish, I heard Smoke say to Horner. You bet, was the reply. Hump runs the galley from now on, and Cooky pulls in his horns. Mugridge heard and shot a swift glance at me, but I gave no sign that the conversation had reached me. I  ad not thought my victory was so far-reaching and complete, but I resolved to let go nothing I had  ained. As the days went by, Smoke’s prophecy was verified. The Cockney became more humble and slavish  o me than even to Wolf Larsen. I mistered him and sirred him no longer, washed no more greasy pots, and  eeled no more potatoes. I did my own work, and my own work only, and when and in what fashion I saw  it. Also I carried the dirk in a sheath at my hip, sailor-fashion, and maintained toward Thomas  ugridge a constant attitude which was composed of equal parts of domineering, insult, and contempt.  ";
    //data = "A Itália negociou com os Aliados sua entrada no conflito em abril de 1915.[] Os italianos renunciaram a sua aliança prévia com a Alemanha e Áustria-Hungria em 4 de maio, dando a todos um aviso adiantado de que a Itália estava se preparando para entrar em guerra contra eles. O almirante Anton Haus, Comandante da Marinha Austro-Húngara, fez preparações a fim de enviar suas principais embarcações para o Adriático e realizar um grande ataque contra a Itália assim que a guerra fosse Devido à escassez de carvão e à Barragem de Otranto, os navios foram incapazes de participarem de grandes operações ofensivas depois do ataque a Ancona, assim foram relegados a defender o litoral da Áustria-Hungria. Haus morreu a bordo do Viribus Unitis em fevereiro de 1917, tendo seu funeral sido realizado a bordo do navio com a presença do imperador Carlos I. Haus foi sucedido no comando da marinha pelo almirante Maksimilijan Njegovan, que continuou com a mesma estratégia de seu predecessor de empregar as embarcações austro-húngaras como uma frota de intimidação. O momento mais significativo para o Viribus Unitis nesse período ocorreu em junho de 1917, quando n foi tirado de seu posto em fevereiro de 1918 devido a um motim em Cátaro, O plano de Horthy era atacar a Barragem de Otranto com uma grande frota de couraçados, barcos torpedeiros, contratorpedeiros e cruzadores. O Viribus Unitis e o SMS Prinz Eugen partiram para o sul em 8 de junho, na companhia dos elementos principais de sua frota, enquanto o Tegetthoff, SMS Szent István e suas escoltas partiram logo no dia seguinte. A ideia era que os membros da Classe Tegetthoff se unissem e usassem seu poder de fogo combinado para destruir a barragem e enfrentar quaisquer embarcações aliadas que encontrassem. Em 10 de junho, enquanto o Tegetthoff e o Szent István seguiam para Islana a fim de se encontrarem com seus irmãos, eles foram avistados por duas lanchas torpedeiras italianas voltando de uma patrulha de rotina. O Szent István foi torpedeado duas vezes e naufragou. Horthy, temendo mais ataques de lanchas ou contratorpedeiros italianos, além da chegada de possíveis couraçados Aliados, achou que o eleme sendo substituído pelo contra-almirante Miklós Horthy. Este começou a reorganizar a marinha de acordo com sua visão, também tirando a frota do porto com o objetivo de realizar exercícios de manobra e artilharia regularmente. Foram as maiores operações que a marinha tinha feito desde o início da guerra. Essas ações tinham a intenção de restaurar a ordem depois de vários motins fracassados, mas também de preparar a frota para uma grande operação ofensiva. Horthy resolveu realizar uma grande ofensiva com a frota a fim de abordar a moral baixa e o tédio dos marinheiros, além de facilitar a saída de u-boots austro-húngaros e alemães do Adriático para o Mediterrâneo. Ele concluiu que a frota estava pronta depois de meses de exercícios, marcando a ofensiva para o início de junho de 191 Carlos realizou uma revista formal da frota e visitou o couraçado. Além dessas visitas, as únicas outras ações de que a base naval de Pola e o Viribus Unitis participaram desde o bombardeio de Ancona foi enfrentar mais de oitenta ataques aéreos realizados pelo recém-formado Corpo Aeronáutico Militar italiano  declarada. A dgara partiu para Brindisi a fim de encontrar-se com os alemães e escoltá-los até um porto aliado na Áustria-Hungria. Os alemães acabaram seguindo para o Império Otomano e a frota austro-húngara, em vez de acompanhá-los até o Mar Negro, voltou para sua base naval em Pola.";
    enc = vigenere("encrypt", asciiData, key);
    //cout << enc;
    //data = "tpsja kexis ttgztpb wq ssmil tfdxf vsetw ytafrttw btzf pcbroxdzo zn tqac wix, bwfd s, je ahvup sd pcbqqxff lfzed d avu ytwoxavneh sg p aznst qaghv. sfiseic f udh zgaurr dxnm rcdentv btzf nllgubsetz, wymh qfndbhqgotopl qq asmactq m prftlk huusieymi ythfdz: t tdxavict i cjs vu yts edi grzivupavnex yy pikoc wirjbko, xtw gb rvffgxa pikoc, iedp elex t gmbdr fzb sgiff bpkga; p gvgfghm t ele z xwogwko qbgmgwr adlmy bozs rtpmchv e xtme ccmo. xhmetg, hup meyqsd czgxaj o jul fsdis, eaz t tah bf iymvaxhf, mll ra roso: objqgsecl kepxqrl pgxdt sjtp emhgc v o axrfphvunh. huic zseh, ijewiet tw pjoj hzkee so kacwi pt ida dxbfp-tvict ha bsj dp tkahhf dp 1869, ge yxbya mxpm rvrclke pt qrtfffu. iwehl nre hsjspgxm t elaeks mccj, rtcse t diodiiddg, vrl lsxiszrz, isehiza nxvop rv tcxdqchfs nhrfdg v ffb eodagayaepd of cpfmftfzo ahv acnv axbkah. cezp tquvcj! vpkhmss v qfx rmd vfugx gmghrs yxq mciecthw. mrfvsnx ugt qyogbe — btbvictzm jar csnzucvr mtnhm, ifzsex i odbjtlgxq, iof czgwfpbke p mea ifzsex, ugt zvvzn yy sohupeie uwvid we gahzml asdp o znexvopzrr plxm tbxeyasep wuett ra swjcfkwa fiv pchjqgwl a mxmdp rv mtglm rcma: — “ghw, cjs f czglqrsjtpl, qqjg jeyasdtg, mod isptwj dtsid rcdirh ugt o eaenvqoo gacxgq tgkac vlagoedz t tqgrr ickibpfrvpe hq ja uod feuh pvlzl gmgottpkie fiv tpf lacfrdz t lgboeiothq. tgke lk wabpiiz, xwfpg xoetw pd qvu, ljyqaoj nfoizh sjcfkee fiv czuvqb c rzfe gabc lm nkibt tlnpkia, iiuo tlwa t o uoc vvgp s da bni xws iot t rmiiiekt ee bozs tgxuboj eymvmcvrs; enha xgjo p nq ejpcixx pajjfr lh rahgf iwnwfgs wiytha.” qcd e qbix pazgz! gea, cof mp tvdtdvnoh hmh jznex ebdzzcpl ugt zye oxmjtw. v fzb eehwd qfx gttulet t gxpijuwt hah avud wmmh; tfi llwub ele xx izrodiyaiu eoia z nrpxgtogxvqs qfuymvk ss yaxeif, hsd ad âgwupg eex tw pjjzdll ha bcto akmzrwge, xtw bpijaoh i fgcgerh gabc hupf wq gskict xmgrv dz xwbthrcfes. fpfue p tfagfvctws. hxfrmxx md jars yhzq di uek iiehcrs, pgxdt scad mvqh gvnshvmh, aznst mdbo jambrm, rojaot gab c toekmy, p tzlst, — yy awiiz ws hpzv, — e... exrtpa ganbizrwr! dljyu p dfunh pttg uicxm cjsd ect e ftftetke etbyoct. gachvnexq-et rv sluid fiv edle mcceixt, eucrr qfx rmd drrpgxm, eouenxy ypwj dz jyq pg gacxrfpg. v vpkhmss, gaoxgqj arid. gea swxo bni et qrrabwet, bro obka fiv sp wiumojsp ksxpf gewh gtpc, toyoyxho. eex h qqj csieh idp qfidt exiodeymi pgodaebgm... ja jowmiugof qfx ijewia lhw etgjeyme q firtch ezdg, eaz iedtqv qfx vqjbr ex lm fdrfs zl ixtavnehw pt ida ekestrza. p wepd ele dbq, a fiv mpgse rcevtglm p sjsl tracwda pke meoieyme-xd. rv pp, t gmqstetke pp qrml, vsy dg flshw qhhlptwse, p pfcl xrfgsrbpkxm, p hiidmi etbyoct qma dfdtt gdtf ea xbrtp sottggmd.";
    hk = break_vigenere(enc, key.size(), ENG);

    out << hk;
    out.close();

  return 0;
}
