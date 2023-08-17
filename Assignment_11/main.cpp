/*
Department maintains a student information. The file contains roll
number, name, division and address. Allow user to add, delete
information of student. Display information of particular student. If
record of student does not exist an appropriate message is displayed. If
it is, then the system displays the student details. Use Sequential File
to maintain the data.

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

class Record{
    int rollNo , div;
    string name , address;

public:
    Record(string title,string path,int roll,int division){
        this -> name = title;
        this -> address = path;
        this -> rollNo = roll;
        this -> div = division;
    }

    friend class File;
};

class File{
    string fileName;
    fstream input;
    fstream output;

public:
    File(string title){
        this -> fileName = title;
    }

    void writeRecord(Record *r,int num){
        output.open(fileName , ios::out);
        for(int i=0;i<num;i++){
            output<<r[i].rollNo<<","<<r[i].name<<",SE-"<<r[i].div<<","<<r[i].address<<endl;
        }
        output.close();
    }

    void printRecord(){
        input.open(fileName , ios::in);
        while(!input.eof()){
            string record;
            input>>record;
            cout<<record<<endl;
        }
        input.close();
    }

    void searchRecord(int r){
        input.open(fileName , ios::in);
        bool isFound = false;
        while(!input.eof()){
            string record;
            input>>record;
            if(int(record[0] - 48) == r){
                cout<<"Record found"<<endl;
                cout<<record<<endl;
                cout<<endl;
                isFound = true;
                break;
            }
        }
        input.close();
        if(!isFound){
            cout<<"Record not found...."<<endl;
        }
    }

    void deleteRecord(int r){
        input.open(fileName , ios::in);
        vector <string> lines;

        while(!input.eof()){
            string record;
            input>>record;
            if((int(record[0]) -48) != r){
                lines.push_back(record);
            }
        }
        input.close();

        output.open(fileName,ios::out);
        for(int i=0;i<lines.size();i++){
            output<<lines[i]<<endl;
        }
        output.close();
    }
};

int main(){
    File f("sample.txt");
    Record record[3] = {
        Record("Advait" , "Kothrud" , 4 , 3),
        Record("Shubham" , "Thane" , 5 , 3),
        Record("Kaustubh" , "Jalgaon" , 6 , 3)
    };

    f.writeRecord(record , 3);
    f.printRecord();
    f.searchRecord(5);
    f.deleteRecord(5);
    f.printRecord();

    return 0;
}