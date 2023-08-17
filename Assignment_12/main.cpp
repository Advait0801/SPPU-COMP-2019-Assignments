/*
Implementation of a direct access file -Insertion and deletion of a
record from a Direct Access File.

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class Record{
	int id,salary,experience;
	string name;

public:
	Record(string title,int i1,int i2,int i3){
		this -> name = title;
		this -> id = i1;
		this -> salary = i2;
		this -> experience = i3;
	}

	string toString(){
	    string output ;
	    return output + to_string( id ) + "-" + name + "-" + to_string( experience ) + "-" + to_string( salary );
	}

	friend class File;
};

class File{
	int tableSize;
	string fileName;
	int *table;

	int hash(int id){
		return id % this -> tableSize;
	}

public:
	File(string name,int size){
		this -> fileName = name;
		this -> tableSize = size;
		this -> table = new int[tableSize];
		for(int i=0;i<tableSize;i++){
			table[i] = -1;
		}
	}

	void insert(Record r){
		ofstream output;
		output.open(this -> fileName , ios::app);
		int index = hash(r.id);
		int address = output.tellp();
		table[index] = address;
		output.write( r.toString().c_str() , r.toString().length() );
		output.write( "\n" , 1 ) ;
		output.close() ;
	}

	void deleleRecord(int id){
		int index = hash(id);
		this -> table[index] = -1;
		ifstream input;
		input.open(this -> fileName , ios::in);
		vector <string> lines;

		while(!input.eof()){
			string record;
			input>>record;
			if((int(record[0]) -48) != id){
				lines.push_back(record);
			}
		}
		input.close();

		ofstream output;
		output.open(this -> fileName , ios::out);
		for(int i=0;i<lines.size();i++){
			int location = output.tellp();
			string line = lines[i];
			output.write(line.c_str() , line.length());
			output.write("\n" , 1);
			int index = hash(int(line[0]) - 48);
			this -> table[index] = location;
		}
		output.close();
	}

	void displayRecords(){
		ifstream input;
		input.open(this -> fileName , ios::in);
		input.seekg(ios::beg);
		while(!input.eof()){
			string line;
			input>>line;
			cout<<line;
			cout<<endl;
		}
		input.close();
	}

	void displayTable(){
		for(int i=0;i<this -> tableSize;i++){
			cout<<table[i]<<endl;
		}
	}

};

int main(){
	File f("data.txt",5);
	f.insert(Record("Advait",1,34,5));
	f.insert(Record("Shubham",2,12,2));
	f.insert(Record("Kaustubh",3,26,4));
	f.insert(Record("Krishna",4,10,1));
	f.displayTable();
	cout<<endl;
	f.displayRecords();
	f.deleleRecord(2);
	f.displayTable();
	cout<<endl;
	f.displayRecords();

	return 0;
}
