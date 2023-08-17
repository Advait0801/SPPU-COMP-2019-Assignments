#include <iostream>
using namespace std;

class Student{
    string name;
    int rollno , div;
    static int studentcount;

public:
    Student(){
        this -> name = "";
        this -> rollno = 0;
        this -> div = 0;
        studentcount++;
    }

    Student(Student &s){
        this -> name = s.name;
        this -> rollno = s.rollno;
        this -> div = s.div;
        studentcount++;
    }

    ~Student(){
        cout<<"Destructor called"<<endl;
        studentcount--;
    }

    static int showcount(){
        return studentcount;
    }

    void init(){
        cout<<"Enter student's details.."<<endl;
        string n;
        int r , d;
        cout<<"Student's name: ";
        cin>>n;

        try
        {
            cout<<"Student's rollno: ";
            cin>>r;
            if(r<=0){
                throw r;
            }
        }
        catch(int r)
        {
            cout<<"Roll no cant be negative"<<endl;
            this -> rollno = 0;
        }
        
        cout<<"Student's division: ";
        cin>>d;
        cout<<endl;

        this -> name = n;
        this -> rollno = r;
        this -> div = d;
    }

    friend class Display;
};

class Display{
public:
    void display(Student &s){
        cout<<"Following are student's details.."<<endl;
        cout<<"Student's name: "<<s.name<<endl;
        cout<<"Student's rollno: "<<s.rollno<<endl;
        cout<<"Student's division: "<<s.div<<endl;
    }
};

int Student::studentcount = 0;

int main(){
    Student s1;
    Display d;
    s1.init();
    d.display(s1);
    cout<<endl;
    Student s2 = s1;
    d.display(s2);
    cout<<endl;

    cout<<"Student's count = "<<Student::showcount()<<endl;

    Student *s3 = new Student;
    s3 -> init();
    d.display(*s3);
    cout<<endl;
    delete s3;   

    return 0;
}