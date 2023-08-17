#include <iostream>
using namespace std;

class Publication{
public:
    string name;
    float price;

    Publication(){
        name = "";
        price = 0;
    }

    void init(){
        cout<<"Enter the publication's details.."<<endl;
        cout<<"Name of the publication: ";
        cin>>this -> name;
        cout<<"Price of the publication: ";
        cin>>this -> price;
        cout<<endl;
    }

    void displaybook(Publication &p){
        cout<<"Name of the book: "<<p.name<<endl;
        cout<<"Price of the book: "<<p.price<<endl;
    }

    void displaytape(Publication &p){
        cout<<"Name of the tape: "<<p.name<<endl;
        cout<<"Price of the tape: "<<p.price<<endl;
    }
};

class Book:public Publication{
    int pages;

public:
    Book(Publication &pub){
        try{
            cout<<"Enter no of pages present in the book: ";
            int p;
            cin>>p;
            if(p<=0){
                throw p;
            }
            else{
                this -> pages = p;
            }
        }
        catch(int p){
            cout<<"Pages in the book can't be negative or zero"<<endl;
            this -> pages = 0;
            pub.name = "";
            pub.price = 0.0f;
        }
    }

    void display(Publication &p){
        cout<<"Here are the book's details..."<<endl;
        this -> displaybook(p);
        cout<<"No of pages in the book: "<<pages<<endl;
    }
};

class Tape:public Publication{
    float time;

public:
    Tape(Publication &pub){
        try
        {
            float t;
            cout<<"Enter the time length of the tape: ";
            cin>>t;
            if(t<=0){
                throw t;
            }
            else{
                this -> time = t;
            }
        }
        catch(float t)
        {
            cout<<"Time length of the tape can't be negative or null"<<endl;
            pub.name = "";
            pub.price = 0.0f;
            this -> time = 0.0f;
        }
        
    }

    void display(Publication &p){
        cout<<"Here are the tape's details..."<<endl;
        this -> displaytape(p);
        cout<<"Time length of the tape: "<<time<<endl;
    }
};

int main(){
    while(true){
        Publication p;
        p.init();
        cout<<"Enter whether the publication is a book or a tape.."<<endl;
        cout<<"Press b for book and t for tape: ";
        char c;
        cin>>c;        

        if(c=='b'){
            Book b(p);
			cout<<endl;
            b.display(p);
        }

        if(c=='t'){
            Tape t(p);
			cout<<endl;
            t.display(p);
        }

        cout<<"If you want to try again press 1 else press 0: ";
        int choice;
        cin>>choice;
        cout<<endl;

        if(choice==0){
            break;
        }
    }
}

