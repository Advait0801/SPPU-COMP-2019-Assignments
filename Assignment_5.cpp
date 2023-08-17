/*
Implement all the functions of a dictionary (ADT) using open hashing technique: separate chaining using
linked list Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, and Keys
must be unique. Standard Operations: Insert(key, value), Find(key), Delete(key)

Name : Advait Naik
Roll no : 21354
*/
#include <iostream>
using namespace std;

class Node{
    Node *ptr;
    string word;
    string meaning;

public:
    Node(string key,string value){
        this -> word = key;
        this -> meaning = value;
        this -> ptr = nullptr;
    }

    friend class Dictionary;
};

class Dictionary{
    int dictionarysize;
    Node **headnode;

    int hash(string item){
        int ascii = 0;

        for(int i=0; i<item.length() ;i++){
            ascii = ascii + int(item[i]);
        }
        return ascii % dictionarysize;
    }

    void insertNode(Node *head, Node *newentry){
        Node *current = head;
        while(current -> ptr != nullptr){
            current = current -> ptr;
        }
        current -> ptr = newentry;
    }

    void print(Node *head){
        Node *current = head;
        while(current != nullptr){
            cout.width(5);
            cout<<current -> word<<" - "<<current -> meaning<<",";
            current = current -> ptr;
        }
    }

public:
    Dictionary( int size ) {
        this -> dictionarysize = size ;
        headnode = new Node*[ size ] ;
        for( int i = 0 ; i < size ; i++ ) {
            headnode[ i ] = nullptr ;
        }
    }

    void insert(string key,string value){
        int index = hash(key);
        
        if(headnode[index] == nullptr){
            headnode[index] = new Node(key,value);
        }
        else{
            Node *newnode = new Node(key,value);
            insertNode(headnode[index] , newnode);
        }
    }

    void display(){
        for(int i=0;i<dictionarysize;i++){
            cout.width(5);
            cout<<i<<" ";
            print(headnode[i]);
            cout<<"\0"<<endl;
        }
    }

    void search(string key){
        int index = hash(key);
        int count = 1;

        Node *current = headnode[index];
        while(current != nullptr){
            if(current -> word == key){
                cout<<"Word found.."<<endl;
                cout<<current -> word<<" - "<<current -> meaning<<endl;
                cout<<"No. of comparisons: "<<count<<endl;
                break;
            }
            current = current -> ptr;
            count++;
        }
        if(current == nullptr){
            cout<<"Word not found.."<<endl;
            cout<<"No. of comparisons: "<<count<<endl;
        }
    }

    void deleteWord(string key){
        int index = hash(key);

        if(headnode[index] -> word == key){
            Node *newhead = headnode[index] -> ptr;
            delete headnode[index];
            headnode[index] = newhead;
        }
        else{
            Node *current = headnode[index];
            Node *previous = nullptr;
            while(current != nullptr){
                if(current -> word == key){
                    break;
                }
                previous = current;
                current = current -> ptr;
            }
            previous -> ptr = current -> ptr;
            delete current;
        }
    }
};

int main(){
    Dictionary d(10);
    d.insert("abc" , "godd");
    d.insert("bac" , "dsbjv");
    d.insert("gggg" , "ashv");
    d.display();
    d.deleteWord("abc");
    d.display();
    d.search("bac");
    d.search("cab");

    return 0;
}