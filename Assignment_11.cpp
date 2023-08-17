#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class PersonInfo{
    string name , dob , mobileno;

public:
    PersonInfo(){
        this -> name = "";
        this -> dob = "";
        this -> mobileno = "";
    }

    PersonInfo(string n,string d,string m){
        this -> name = n;
        this -> dob = d;
        this -> mobileno = m;
    }

    void create(){
        cout<<"Enter person's details.."<<endl;
        cout<<"Name of the person: ";
        cin>>this -> name;
        cout<<"DOB of the person: ";
        cin>>this -> dob;
        cout<<"MobileNo of the person: ";
        cin>>this -> mobileno;
        cout<<endl;
    }

    friend bool operator==(const PersonInfo &p1,const PersonInfo &p2){
        return p1.name == p2.name;
    }

    void display(){
        cout<<"Name: "<<this -> name<<"\tDOB: "<<this -> dob<<"\tMobileNo: "<<this -> mobileno<<endl;
    }

    string getname(){
        return this -> name;
    }
};

bool comparenames(PersonInfo &p1,PersonInfo &p2){
    return p1.getname() < p2.getname();
}

int search(vector <PersonInfo> &data,string n){
    std::vector <PersonInfo>::iterator i;
    i = std::find(data.begin(),data.end(),PersonInfo(n,"",""));
    if(i != data.end()){
        return int(i - data.begin());
    }
    return -1;
}

int main(){
    vector <PersonInfo> records;
    cout<<"Enter 3 people's details..."<<endl;
    for(int i=0;i<3;i++){
        PersonInfo p;
        p.create();
        records.push_back(p);
    }

    cout<<"Here are entered details..."<<endl;
    for(int i=0;i<3;i++){
        records[i].display();
    }
    cout<<endl;

    cout<<"Press 1 for sorting the list alphabetically or 2 for searching a person's details by name.."<<endl;
    int choice;
    cin>>choice;

    if(choice==1){
        cout<<"Here's the sorted list.."<<endl;
        sort(records.begin(),records.end(),comparenames);
        for(int i=0;i<3;i++){
            records[i].display();
        }
    }

    if(choice==2){
        cout<<"Enter person's name to be found: ";
        string n;
        cin>>n;
        int index = search(records,n);
        if(index==-1){
            cout<<"Person not found in the list..."<<endl;
        }
        else{
            cout<<"Here are the person's details.."<<endl;
            records[index].display();
        }
    }

    return 0;
}