/*
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client’s telephone number.
Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers
(Note: Use linear probing with replacement and without replacement)

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <string.h>
using namespace std;

class Record{
    string clientname;
    int phone;

public:
    Record(){
        this  -> clientname = "--------";
        this -> phone = 0;
    }

    Record(string name,int num){
        this -> clientname = name;
        this -> phone = num;
    }

    void print(){
        cout<<"Name: "<<clientname<<"   Phone No: "<<phone<<endl;
    }  

    bool isEmpty(){
        return this -> phone == 0;
    }  

    friend class HashingTable;
};

class HashingTable{
    int tablesize;
    Record *record;

    int hash(string clientname){
        int ascii = 0;

        for(int i=0; i<clientname.length() ;i++){
            ascii = ascii + int(clientname[i]);
        }
        return ascii % tablesize;
    }

public:
    HashingTable(int i){
        this -> tablesize = i;
        this -> record = new Record[tablesize];
    }

    void display(){
        for(int i=0;i<tablesize;i++){
            record[i].print();
        }
    }

    void insert_without_replacement(Record r){
        int index = hash(r.clientname); 

        if(record[index].isEmpty()){
            record[index] = r;
        }

        else{
            int currentIndex = index ;
			while( !record[ currentIndex ].isEmpty() ) {
				currentIndex = ( currentIndex + 1 ) % tablesize ;
			}
			record[ currentIndex ] = r ;
        }
    }

    void insert_with_replacement(Record r){
        int index = hash(r.clientname);

        if(record[index].isEmpty()){
            record[index] = r;
        }

        else{
            Record existing = record[index];
            int actual_index = hash(existing.clientname);

            if(actual_index == index){
                int currentIndex = index ;
			    while( !record[ currentIndex ].isEmpty() ) {
			    	currentIndex = ( currentIndex + 1 ) % tablesize ;
			    }
			    record[ currentIndex ] = r ;
            }

            else{
                record[index] = r;
                int currentIndex = index ;
			    while( !record[ currentIndex ].isEmpty() ) {
			    	currentIndex = ( currentIndex + 1 ) % tablesize ;
			    }
			    record[ currentIndex ] = existing;
            }
        }
    }

    void search(string name){
        int index = hash(name);
        int comparisons = 0;

        if(record[index].clientname == name){
            record[index].print();
        }
        
        else{
            int currentindex = index;
            int passes = 0;

            while( record[ currentindex ].clientname != name && passes != tablesize) {
			    currentindex = ( currentindex + 1 ) % tablesize ;
                passes++;
                comparisons++;
			}

            if(passes != tablesize){
                record[currentindex].print();
            }
            else{
                cout<<"No record exists with clientname: "<<name<<endl;
            }            
        }

        cout<<"No of comparisons: "<<comparisons<<endl;
    }

    
};

int main(){
    HashingTable ht(10); 
    ht.insert_without_replacement(Record("abcd",78));
    ht.insert_without_replacement(Record("bcda",758));
    ht.insert_without_replacement(Record("dabc",56));
    ht.insert_without_replacement(Record("cdab",3));
    ht.insert_without_replacement(Record("cbda",23));
    ht.display();

    ht.search("cdab");
    ht.search("ggg");

    return 0;
}