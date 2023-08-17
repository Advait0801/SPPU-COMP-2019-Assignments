#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class StudentRecord
{
    string name;
    int rollno , marks;

public:
    
    StudentRecord()
    {
        this -> name = "";
        this -> rollno = 0;
        this -> marks = 0;
    }   

    StudentRecord(string n,int r,int m)
    {
        this -> name = n;
        this -> rollno = r;
        this -> marks = m;
    } 

    void create()
    {
        string n;
        int r,m;
        cout<<"Enter name, rollno and marks : ";
        cin>>n>>r>>m;       
        this -> name = n;
        this -> rollno = r;
        this -> marks = m;
    }

    void display()
    {
        cout<<"Name: "<<this -> name<<"\tRollNo: "<<this -> rollno<<"\tMarks: "<<this -> marks<<endl;
    }

    int getmarks()
    {
        return this -> marks;
    }

    friend bool operator==(const StudentRecord &s1 , const StudentRecord &s2)
    {
        return s1.name == s2.name;
    } 

};

bool comparemarks(StudentRecord &s1,StudentRecord &s2)
{
    int m1 = s1.getmarks();
    int m2 = s2.getmarks();
    return m1 < m2;
} 

int search(vector<StudentRecord> &record , string n)
{
    std::vector<StudentRecord>::iterator it;
    it = std::find(record.begin() , record.end() , StudentRecord(n , 0 , 0));
    if(it != record.end())
    {
        return int(it - record.begin());        
    }
    else{
        return -1;
    }
} 

int main()
{
    vector<StudentRecord> vec;
    cout<<"Enter 3 student details......"<<endl;
    for(int i=0;i<3;i++)
    {
        StudentRecord s;
        s.create();
        vec.push_back(s);       
    }
    
    cout<<endl;
    cout<<"Here's the student details...."<<endl;
    for(int i=0;i<3;i++)
    {
        vec[i].display();
    }

    cout<<endl;
    cout<<"Press 1 for sorting the data according to marks or press 2 for searching a particular data by name: ";
    int option;
    cin>>option;
    if(option==1)
    {
        sort(vec.begin() , vec.end() , comparemarks);
        cout<<"Sorted list.........."<<endl;
        for(int i=0;i<3;i++)
        {
            vec[i].display();
        }        
    }

    if(option==2)
    {
        cout<<"Enter name to search: ";
        string n;
        cin>>n;
        int index = search(vec , n);
        if(index==-1)
        {
            cout<<"Student not present in the list."<<endl;
        }
        else{
            cout<<"Student is present in the list.Here are its details..."<<endl;
            vec[index].display();
        }
    }


    return 0;
}
