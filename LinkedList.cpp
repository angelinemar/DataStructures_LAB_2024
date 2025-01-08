#include <iostream>
#include <string.h>

using namespace std;
int counterTotalNode = 0;
class Pokemon{
private :
    // store values
    int pokeDex, pokeAtk, pokeHlt, pokeAttack;
    string pokeStance;
public :
    // set initial values
    Pokemon(){
        pokeDex = 0;
        pokeAtk = 0;
        pokeHlt = 0;
        pokeAttack = 1;
        pokeStance = "";
    }

    Pokemon(int pok, int hlt, int atk, string stc, int lvl):
        pokeDex(pok), pokeAtk(atk), pokeHlt(hlt), pokeStance(stc), pokeAttack(lvl){}

    int getPokeDex(), getPokeAtk(), getPokeHlt(), getPokeLevel();
    string getPokeStance();
    void setPokeDex(int pok);
    void setPokeAttack(int atk);
    void setPokeHealth(int hlt);
    void setPokeStance(string stc);
    void setPokeLevel(int lvl);

};

int Pokemon::getPokeDex(){
    return pokeDex;
}
int Pokemon::getPokeAtk(){
    return pokeAtk;
}
int Pokemon::getPokeHlt(){
    return pokeHlt;
}
int Pokemon::getPokeLevel(){
    return pokeAttack;
}
string Pokemon::getPokeStance(){
    return pokeStance;
}
void Pokemon::setPokeLevel(int lvl){
    pokeAttack = lvl;
}
void Pokemon::setPokeDex(int pok){
    pokeDex = pok;
}
void Pokemon::setPokeAttack(int atk){
    pokeAtk = atk;
}
void Pokemon::setPokeHealth(int hlt){
    pokeHlt = hlt;
}
void Pokemon::setPokeStance(string stc){
    pokeStance = stc;
}

// node buat akses value linkedlist pokemon
class Node{
private :
    // value dari Pokemon bisa diwakilin data
    Pokemon data;
    Node *prev, *next;
public :
    Node():
    // set default pointer to NULL
    prev(NULL), next(NULL){}
    Node (Pokemon dataValue):
    data(dataValue), prev(NULL), next(NULL){}
    Pokemon getPokemon();
    Node *getNext();
    Node *getPrev();
    void setNext(Node *setnext);
    void setPrev(Node *setprev);
    void setPokemon(Pokemon datavalue);
    void setPokeAttack(int atk);
    void setPokeHealth(int hlt);
    void Print();
    void PrintDebugs();
    int getID(){
        return data.getPokeDex();
    }
    string getPokeStance(){
        return data.getPokeStance();
    }
    int getPokeHealth(){
        return data.getPokeHlt();
    }
    int getPokeLevel(){
        return data.getPokeLevel();
    }
    int getPokeAttack(){
        return data.getPokeAtk();
    }
    void setPokeLevel(int lvl){
        data.setPokeLevel(lvl);
    }
};

Node *Node::getNext(){
    return next;
}

Node *Node::getPrev(){
    return prev;
}

Pokemon Node:: getPokemon(){
    return data;
}
void Node::setPokeAttack(int attack){
    data.setPokeAttack(attack);
}
void Node::setPokeHealth(int health){
    data.setPokeHealth(health);
}
void Node::setNext(Node *setnext){
    next = setnext;
}

void Node::setPrev(Node *setprev){
    prev = setprev;
}

void Node::setPokemon(Pokemon datavalue){
    data = datavalue;
    // update node
}
void Node::PrintDebugs(){
    //cout << "check attack value: " << data.getPokeAtk() << " " << endl;
    //cout << "check stance value:" << data.getPokeStance() << " " << endl;
    //cout << "TOTAL NODES: " << counterTotalNode << " " << endl;
}

void Node::Print(){
    cout << "ID: " << data.getPokeDex() << " ";
    cout << "HP: " << data.getPokeHlt() << " ";
    cout << "LVL: " << data.getPokeLevel() << endl;
}

class LinkedList{
private:
    Node *head;

public:
    LinkedList(): head(NULL){}
    void Insert(int pok, int dmg, int hlt, string stc, int atk);
    void Delete();
    void getPrint();
    void Shuffle(int idxClock, int isClockwise);
    void Check(int inputCheck);
    void reverse(int inputReverse);
    void Evolve(int pok, int dmg, int hlt, string stc, int atk);
    void Attack(int pok, int dmg, int hlt, string stc, int atk);
};

void LinkedList::reverse(int inputReverse){
    //cout << "reverse: " << endl;
    //if(head == NULL) cout << "HEAD IS NULL" << head->getNext()->getID() << endl;;
    //cout <<"HEAD ID NOW: "<<  head -> getID() << endl;
    //if(head != NULL) return;
    Node *dummyHead = head;
    Node *counter = head;
    int idxCounter = 0;
    int idxTurn = inputReverse;
    //cout << "idxTurn: " << idxTurn << endl;
    //cout << "counter: " << counterTotalNode << endl;
    int newIdxTurn = idxTurn;
    // if hasil modulus = 0
    //if(newIdxTurn == 0) cout << "newIdxTurn modulusnya hasilnya 0" << endl;
    //if(newIdxTurn > counterTotalNode) cout << "newIdxTurn nya lebih besar dari jumlah node yg ada" << endl;
    if(newIdxTurn == 0 || newIdxTurn > counterTotalNode) newIdxTurn = counterTotalNode;
    
    //if(head->getNext() != head){
        //cout << "masuk" << endl;
        do{
            idxCounter++;
            counter = counter -> getNext();
        } while(counter != head);
        //cout << "counter ada: " << idxCounter << endl;

        Pokemon temp[idxCounter + 10];
        Node *checkpoint;
        while(idxCounter > 0){
            for(int i = 0; i < newIdxTurn; i++){
                temp[i] = dummyHead -> getPokemon();
                dummyHead = dummyHead -> getNext();
            }

        /*
        for(int i = 0; i < idxTurn; i++){
            cout << "pokedex stored: " << temp[i].getPokeDex() << endl;
        }
        */ 
        checkpoint = dummyHead;
        for(int i = 0; i< newIdxTurn; i++){
            dummyHead = dummyHead -> getPrev();
            //cout << "masuk" << endl;
            dummyHead -> setPokemon(temp[i]);
        }
        idxCounter -= inputReverse;
        if(idxCounter < inputReverse) newIdxTurn = idxCounter;

        // UPDATE BACK DUMMY HEAD KE POSISI TERAKHIR
            dummyHead = checkpoint;
        }
    //}
    //TO-DO:
    // JANGAN LUPA GANTI HEADDDDDDDDDDDDDDDDDDDDDDDDDN !!
    //cout << "head is now : " << head->getID() << endl;
}

void LinkedList::Check(int inputCheck){
    if(head == NULL) return;
    Node *currHead = head;
    Node *tail = head;
    int storageOfPokeDex[100] = {0};
    int nominalStorageofPokeDex[100] = {0};
    int idxLoop = inputCheck ;
    int idxStorageofPokeDex = 0;
    if(idxLoop > counterTotalNode) idxLoop = counterTotalNode;
    for(int i = 0; i < idxLoop; i++){
        bool isSame = false;
        for(int j = 0;j < idxLoop && isSame == false ; j++){
            if(storageOfPokeDex[j] == currHead->getID()){
                isSame = true;
                nominalStorageofPokeDex[j]++; // add numbers of found elements (> 1 means there are duplicates)
            }
        }
        // if there are no duplicates
        if(isSame == false){
            // just keep storing the current found element into the array
            storageOfPokeDex[idxStorageofPokeDex] = currHead -> getID();
            //cout << "storage item ke " << idxStorageofPokeDex << " adalah " <<  storageOfPokeDex[idxStorageofPokeDex] << endl;
            nominalStorageofPokeDex[idxStorageofPokeDex] = 1; // add number elements
            idxStorageofPokeDex++;
        }
        // update indexs
        currHead = currHead->getNext();
        tail = currHead;
    }

    Node *headForDeletion = head;
    int loopCounter = 0;
    bool toErase = true;
    while (loopCounter < idxLoop){
        toErase = false;
        for(int i = 0; i< idxStorageofPokeDex && toErase == false; i++){
            if(storageOfPokeDex[i] == headForDeletion->getID()){
                //cout << "storage ke " << storageOfPokeDex[i] << " sama dengan " << headForDeletion->getID() << " " <<idxStorageofPokeDex<<endl;
                if(nominalStorageofPokeDex[i] > 1) {
                        toErase = true;
                        //cout<<"hapus"<<endl;
                }
            }
        }

        if(toErase == true){
            if(headForDeletion == head){
                //printf("masuk if\n");
                // 2
                Node *temp = head;
                // 3
                Node *prevHead = head -> getPrev();
                // 4
                Node *nextHead = head -> getNext();

                prevHead -> setNext(nextHead);
                nextHead -> setPrev(head -> getPrev());

                // change currentTarget to new head
                head = nextHead;
                //cout << "masuk current head: " << head->getID() << endl;
                counterTotalNode--;
                headForDeletion = prevHead;
            }
            else{
                //printf("masuk else\n");
                Node *temp = headForDeletion;
                Node *prevHead = headForDeletion -> getPrev();
                Node *nextHead = headForDeletion -> getNext();
                prevHead -> setNext(nextHead);
                nextHead -> setPrev(headForDeletion -> getPrev());
                headForDeletion = prevHead;
                delete temp;
                counterTotalNode--;

                //cout << "head for deletion is now: " << headForDeletion->getID() << endl;
            }
        }
        //cout<<"--kali--"<<endl;
        headForDeletion = headForDeletion -> getNext();
        //cout << "updated head for deletion: " << headForDeletion->getID() << endl;
        loopCounter++;
        //cout<<loopCounter << " - " <<idxLoop<<endl;
    }
}

void LinkedList::Shuffle(int idxClock, int isClockwise){
    if(head == NULL) return;
    // if it is a anticlockwise
    LinkedList callLinkedlist;
    if(head -> getNext() != head && isClockwise == 1){
        Node *getTarget = head;
        for(int i = 0; i < idxClock; i++){
            getTarget = getTarget -> getNext();
        }
        //cout << "currentTarget is: " << getTarget -> getID() << endl;

        // 5
        Node *prevCT = getTarget -> getPrev();
        //cout << "prevCT is 5: " << prevCT -> getID() << endl;
        // 7
        Node *nextCT = getTarget -> getNext();
        //cout << "nextCT is 7: " << nextCT -> getID() << endl;

        prevCT -> setNext(head);
        nextCT -> setPrev(head);
        // 5
        Node *prevHead = head -> getPrev();
        // 3
        Node *nextHead = head -> getNext();

        prevHead -> setNext(getTarget);
        nextHead -> setPrev(getTarget);

        head -> setPrev(prevCT);
        head -> setNext(nextCT);
        getTarget -> setPrev(prevHead);
        //cout << "5 : " << getTarget -> getPrev() -> getID() << endl;
        getTarget -> setNext(nextHead);
        //cout << "3 : " << getTarget -> getNext() -> getID() << endl;
        
    }
    else if(isClockwise == 0){
        if(head -> getNext() != head) {
        Node *getTarget = head;
        //cout << getTarget -> getID() << endl;
        for(int i = 0; i < idxClock; i++) {
            getTarget = getTarget -> getPrev();
        }        

        // getTarget sekarang 3
        Node *prevGT = getTarget -> getPrev(); // 3
        Node *nextGT = getTarget -> getNext(); // 4
        Node *prevHead = head -> getPrev(); // 5
        Node *nextHead = head -> getNext(); // 3
        nextGT -> setPrev(head);
        prevGT -> setNext(head);
        head -> setPrev(prevGT);
        head-> setNext(nextGT);

        prevHead -> setNext(getTarget);
        nextHead -> setPrev(getTarget);
        getTarget -> setPrev(prevHead);
        getTarget -> setNext(nextHead);

        //cout << "Head skrg 2: " << head -> getID() << endl;
        }
    }
}

void LinkedList::Delete(){
    if(head == NULL) return;
    if(counterTotalNode >= 1){
        if(head != NULL){
            // A
            Node *temp = head;
            // B
            Node *nextNode = temp -> getNext();
            // E
            Node *prevNode = temp -> getPrev();
            counterTotalNode--;
            // head now is B
            head = nextNode;
            // B prevNode is now E
            nextNode -> setPrev(prevNode);
            // E nextNode is now B
            prevNode -> setNext(head);
            //cout<<"Posisi head setelah delete : "<<head->getID()<<endl;
            //cout<<"Kirinya head adalah "<<head->getPrev()->getID()<<endl;
            delete temp;
        } 
    }
}

void LinkedList::getPrint() {
    // print final pok and hlt
    //cout<<" === Maju : \n";
    if(counterTotalNode == 0){
        cout << "no Poke Poke ;-;" << endl;
    }
    else{
        Node *temp = head;
        do{
            temp -> Print();
            temp -> PrintDebugs();
            temp = temp -> getNext();
        } while(temp != head);
    }
    // debug dari blkg
    //cout<<" === Mundur : \n";
    //Node *temp = head->getPrev();
    //do{
        //temp -> Print();
        //temp -> PrintDebugs();
        //temp = temp -> getPrev();
    //} while(temp != head->getPrev());
    //cout<<"Posisi Head : \n";head->Print();
}

void LinkedList::Attack(int pok, int atk, int hlt, string stc, int lvl) {
    if(head == NULL) return;
    Pokemon pointer(pok, atk, hlt, stc, lvl);
    Node *newNode = new Node(pointer);
    Node *currHead = head;
    Node *prevHead = head -> getPrev();
    Node *kelinciPercobaan = head;
    if(head->getNext() != head){
        /*
        cout << "masuk" << endl;
        cout << "CURRHEAD POKE HEALTH: " << currHead->getPokeHealth()<< endl;
        cout << "currHead poke attack: " << currHead->getPokeAttack() << endl;
        */
        if(currHead->getPokeHealth() - newNode->getPokeAttack() <= 0){
            //cout << "aman" << endl;
            Node *tempHeadNext = head -> getNext();
            head = tempHeadNext;
            head -> setPrev(prevHead);   
            counterTotalNode--;
        }
        // if the head will be killed
        else if(currHead->getPokeHealth() - newNode->getPokeAttack() > 0){
            // remove head, set new head, insert newNode
            /*
            cout << "bye" << endl;
            cout << "currHead health: " << currHead->getPokemon().getPokeHlt() << endl;
            cout << "newNode attack: " << newNode->getPokemon().getPokeAtk() << endl;
            cout << "updateHealth: " << updateHealth << endl;
            cout << "health baru: " << updateHealth << endl;
            */
            int updateHealth = currHead->getPokemon().getPokeHlt() - newNode->getPokeAttack() ;
            currHead->setPokeHealth(updateHealth);
        }

        // if prevHead will be killed
        if(prevHead->getPokeHealth() - newNode->getPokeAttack() <= 0){
            Node *tempPrevPrev = prevHead->getPrev();
            head->setPrev(tempPrevPrev);
            tempPrevPrev->setNext(head);
            counterTotalNode--;
        }
        else if(prevHead->getPokeHealth() - newNode->getPokeAttack() > 0){
            /*
            cout << "HALOOOOOOOOOOO" << endl;
            cout << "currHead health: " << prevHead->getPokemon().getPokeHlt() << endl;
            cout << "newNode attack: " << newNode->getPokemon().getPokeAtk() << endl;
            cout << "updateHealth: " << updateHealth << endl;
            cout << "health baru: " << updateHealth << endl;
            */
           int updateHealth = prevHead->getPokemon().getPokeHlt() - newNode->getPokeAttack();
            prevHead->setPokeHealth(updateHealth);
        }
        // insert newNode
        Insert(pok, atk, hlt, stc, lvl);
    }
    else if(head->getNext() == head){
        //cout << "MASUKK SENDIRI" << endl;
        if(newNode->getPokeAttack() <= 0){
            int updateHealth = currHead->getPokemon().getPokeAtk() - newNode->getPokeAttack();
            currHead->setPokeHealth(updateHealth);
        }
        else if(currHead->getPokeHealth() - newNode->getPokeAttack() == 0){
            Node *tempHead = head;
            Insert(pok, atk, hlt, stc, lvl);
            head = newNode;
            counterTotalNode--;
        }
    }
}

void LinkedList::Evolve(int pok, int atk, int hlt, string stc, int lvl){
    if(head == NULL) return;
    //cout << "masukkk" << endl;
    Pokemon pointer(pok, atk, hlt, stc, lvl);
    Node *newNode = new Node(pointer);
    //cout << "newNode is: " << newNode->getID() << endl;
    Node *currHead = head;
    Node *prevHead = head -> getPrev();

    Node *kelinciPercobaan = head;
    int highestValueHealth = 0;
    int highestValueAttack = 0;
    int highestValueLevel = 0;

   //if(head -> getNext() != head){
        // if we dont have 3 of the same ID, insert biasa aja tapi stance diganti jadi Neutral
        //cout << "head pokedex: " << currHead -> getID() << endl;
        //cout << "prev head pokedex: " << prevHead -> getID() << endl;
        //cout << "newNode pokeDex: " << newNode -> getID() << endl;
        //cout << "currHead is: " << currHead->getID() << endl;
        //cout << "prevHead is: " << prevHead->getID() << endl;
        if(newNode ->getID() != currHead -> getID() || newNode -> getID() !=  prevHead -> getID()){
            //cout << "== GA SAMA ==" << endl; 
            stc = "Neutral";
            // insert newNode just like normal
            Insert(pok, atk, hlt, stc, lvl);
            return;
        }
        // check value head and prev head
        else if(newNode -> getID() == currHead -> getID() && newNode ->getID() == prevHead -> getID()){
            //cout << "== SAMA ==" << endl;
            for(int i = 0; i < 2; i++){
                // if ternyata curr Level udah 3
                if(newNode -> getPokeLevel() >= 3 || currHead -> getPokeLevel() >= 3 || prevHead -> getPokeLevel() >= 3){
                    // insert biasa 
                    // set the newNode stance into Neutral
                    //cout << "== LVL UDH 3 ==" << endl;
                    stc = "Neutral";
                    Insert(pok, atk, hlt, stc, lvl);
                    return;
                }
                else if(newNode -> getPokeLevel() <= 3 && currHead -> getPokeLevel() <= 3 && prevHead -> getPokeLevel() <= 3){
                    //cout << "== SAMA == " << endl;
                    if(highestValueHealth < kelinciPercobaan -> getPokeHealth()){
                        highestValueHealth = kelinciPercobaan -> getPokeHealth();
                    }
                    if(highestValueAttack < kelinciPercobaan -> getPokeAttack()){
                        highestValueAttack = kelinciPercobaan -> getPokeAttack();
                    }
                    if(highestValueLevel < kelinciPercobaan -> getPokeLevel()){
                        highestValueLevel = kelinciPercobaan -> getPokeLevel();
                    }
                    kelinciPercobaan = kelinciPercobaan -> getPrev();
                }
            }
            // bandingin terakhir sama calon inserted node
            
            //cout << " == SAMA 2 == " << endl;
            if(highestValueHealth < newNode -> getPokeHealth()){
                highestValueHealth = newNode -> getPokeHealth();
            }
            if(highestValueAttack < newNode -> getPokeAttack()){
                highestValueAttack = newNode -> getPokeAttack();
            }
            if(highestValueLevel < newNode -> getPokeLevel()){
                highestValueLevel = newNode -> getPokeLevel();
            }
        }
        //cout << "==highest value level: " << highestValueLevel << endl;   
     
        Node *prevHeadPrevTemp = prevHead -> getPrev();
        head -> setPrev(prevHeadPrevTemp);
        prevHeadPrevTemp -> setNext(head);
        head -> setPokeAttack(highestValueAttack);
        head -> setPokeHealth(highestValueHealth);
        head -> setPokeLevel(++highestValueLevel);                   
        // DEBUG
        //cout << "current value attack of head: " << head->getPokeAttack() << endl;
        //cout << "==highest value attack: "<< highestValueAttack <<endl;
        //cout << "curent head health: " << head->getPokemon().getPokeHlt()<< endl;
        //cout << "==highest value health: " <<highestValueHealth << endl;
        //cout << "current level value: " << head->getPokemon().getPokeLevel() << endl;
        counterTotalNode--;
        //getPrint();
        
        
        // INSERT THE RESULT MERGED LINKEDLIST
    //}
}

void LinkedList::Insert(int pok, int atk, int hlt, string stc, int lvl){
    Pokemon pointer(pok, atk, hlt, stc, lvl);
    // newNode itu kotak baru kosong
    Node *newNode = new Node(pointer);
    // if head is empty
    if(head == NULL){
        // head nya nunjuk A
        head = newNode;
        // next nya A juga A
        head -> setNext(head);
        // prev nya A juga A
        head -> setPrev(head);
        counterTotalNode++;
    } // kalo ini end, berarti kotak A udah kebentuk
    // kalau nodenya masih point ke diri sendiri (tunggal)
    // pake getNext karena cm mau baca next aja
    else if(head -> getNext() == head){
        // newNode sekarang adalah B
        // newNode sekarang adalah B
        head -> setNext(newNode);
        // B prevnya nunjuk A
        newNode -> setPrev(head);
        // B nextnya juga A
        newNode -> setNext(head);
        // set A punya prev jadi B
        head -> setPrev(newNode);
        counterTotalNode++;
    }
    // buat kali kedua >=
    // update prev head, addLeft next, newNode prev and next
    else {
        /*
        #1 Iteration:
            prev A -> A
            next A -> B
            prev B -> A
            next B -> A
        #2 Iteration:

        */
        // new node buat selipin
        // addLeft itu misal skrg cuma A & B
        // mau selipin C jadi B nya kita pake addLeft buat ganti node nya
        // node B tdnya pointing ke A, ganti ke pointing ke newNode which is C
        Node *addLeft = head -> getPrev();
        //cout<<"Posisi addleft : "<<addLeft->getID()<<endl;
        addLeft -> setNext(newNode);
        //cout<<"next dari left adalah : "<<addLeft->getID()<<endl;
        newNode -> setPrev(addLeft);
        //cout<<"left dari new Node adalah : "<<newNode->getPrev()->getID()<<endl;
        newNode -> setNext(head);
        //cout<<"next dari new Node adalah : "<<newNode->getNext()->getID()<<endl;
        head -> setPrev(newNode);
        counterTotalNode++;
        // getPrint();
    }
};

int main (){
    Pokemon callPokemon;
    Node callNode;
    LinkedList callLinkedlist;
    int testCase = 0;
    int pokedexValue = 0, pokeHealthValue = 0, pokeAttackValue = 0;
    string input;
    string stance;
    char inputShuffle;
    int idxClockwise = 0;
    int inputCheck;
    int inputReverse;
    int levelValue = 1;
    
    cin >> testCase;
    for(int i = 0; i < testCase; i++) {

        cin >> input;

        if(input == "Insert"){
            cin >> pokedexValue >> pokeAttackValue >> pokeHealthValue;
            cin >> stance;
            callPokemon.setPokeDex(pokedexValue);
            callPokemon.setPokeAttack(pokeHealthValue);
            callPokemon.setPokeHealth(pokeAttackValue);
            callPokemon.setPokeLevel(levelValue);
            if(stance == "Neutral"){
                callLinkedlist.Insert(pokedexValue, pokeHealthValue, pokeAttackValue, stance, levelValue);
                //callLinkedlist.getPrint();
            }
            else if(stance == "Evolve"){
                callLinkedlist.Evolve(pokedexValue, pokeHealthValue, pokeAttackValue, stance, levelValue);
            }
            else if(stance == "Attack"){
                callLinkedlist.Attack(pokedexValue, pokeHealthValue, pokeAttackValue, stance, levelValue);
            }
        }
        else if(input == "Delete"){
            callLinkedlist.Delete();
            //callLinkedlist.getPrint();
        }
        else if(input == "Shuffle"){
            cin >> inputShuffle;
            int modIdxShuffle = 0;
            if(inputShuffle == 'c'){
                cin >> idxClockwise;
                modIdxShuffle = idxClockwise % counterTotalNode;
                callLinkedlist.Shuffle(modIdxShuffle, 1);
            }
            else if(inputShuffle == 'a'){
                cin >> idxClockwise;
                modIdxShuffle = idxClockwise % counterTotalNode;
                callLinkedlist.Shuffle(modIdxShuffle, 0);
            }
        }
        else if(input == "Check"){
            cin >> inputCheck;
            callLinkedlist.Check(inputCheck); 
        }
        else if(input == "Reverse"){
            cin >> inputReverse;
            callLinkedlist.reverse(inputReverse);
        }
        //cout <<"ID: " << pokedexValue << "HP: " << healthValue << endl;
    }
    callLinkedlist.getPrint();
    return 0;
}

/*
testcase insert
4
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 3 1 1 Neutral

6
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Insert 5 1 1 Neutral
===========================
testcase delete
5
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Delete

6
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Delete
Insert 5 1 1 Neutral
===========================
testcase shuffle
9
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Delete
Insert 5 1 1 Neutral
Insert 6 1 1 Neutral
Insert 7 1 1 Neutral
Shuffle c 4

shuffle tc for anticlockwise
9
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Delete
Insert 5 1 1 Neutral
Insert 6 1 1 Neutral
Insert 7 1 1 Neutral
Shuffle a 4

original tc shuffle 
10
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 3 1 1 Neutral
Delete
Insert 4 1 1 Neutral
Insert 5 1 1 Neutral
Insert 7 1 1 Neutral
Insert 8 1 1 Neutral
Shuffle c 4
===========================
original tc check
13
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 3 1 1 Neutral
Delete
Insert 4 1 1 Neutral
Insert 5 1 1 Neutral
Insert 5 1 1 Neutral
Shuffle c 4
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Shuffle a 5
Check 4

7
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 1 1 1 Neutral
Insert 1 1 1 Neutral
Insert 1 2 2 Evolve
Check 4
Insert 3 3 3 Evolve

8
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 1 1 1 Neutral
Insert 1 1 1 Neutral
Insert 1 2 2 Evolve
Check 4
Insert 3 3 3 Evolve
Reverse 3
*/
