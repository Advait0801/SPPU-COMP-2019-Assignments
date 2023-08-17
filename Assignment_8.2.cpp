#include <iostream>
using namespace std;

class Node
{
    Node *ptrnext;
    int value;

public:
    friend class List;
};

class List
{
    Node *start, *end;

public:
    List()
    {
        start = nullptr;
        end = nullptr;
    }

    ~List()
    {
        Node *current = start;
        while(current!=nullptr)
        {
            Node *deletenode = current -> ptrnext;
            delete current;
            current = deletenode;
        }
    }

    void append(int roll)
    {
        if(start == NULL)
        {
            start = new Node;
            start -> value = roll;
            end = start;
        }

        else
        {
            Node *self = end;
            Node *newnode = new Node;
            newnode -> value = roll;
            self -> ptrnext = newnode;
            end = newnode;
        }
    }

    int length()
    {
        Node *self = start;
        int i = 1;
        while(self<=end)
        {
            self = self -> ptrnext;
            i++;
        }

        return i;
    }

    void display()
    {
        Node *self = start;
        if(self == NULL)
        {
            cout<<"List is empty"<<endl;
        }
        else
        {
            while(self<=end)
        {
            cout<<self -> value<<"\t";
            self = self -> ptrnext;
        }
        }

        cout<<endl;
    }    
};


int main()
{
    cout<<"This is an icecream parlour record...Vanilla and Butterscotch are only 2 available flavours....So enter data accordingly"<<endl;
    List van,butter,van_and_butter,nothing;
    int rollno, choice = 1;
    while(choice==1)
    {
        int option;
        cout<<"Enter rollno of the student: ";
        cin>>rollno;
        cout<<"If you like only vanilla press 1 or if you like only butterscotch press 2.."<<endl;
        cout<<"If u like both press 3 and if you dont like anything press 0: ";
        cin>>option;

        if(option==1)
        {
            van.append(rollno);
        }

        if(option==2)
        {
          butter.append(rollno);
        }

        if(option==3)
        {
            van_and_butter.append(rollno);
        }

        if(option==0)
        {
            nothing.append(rollno);
        }
        
        cout<<"If you want to add any other rollno press 1 or to display the info press 2: ";
        cin>>choice;
    }

    cout<<"Heres the information of students and thier interest in icecream..."<<endl;
    cout<<endl;
    cout<<"Following is the list of students who like both vanilla and icecream....."<<endl;
    van_and_butter.display();

    cout<<"Following is the list of students who either like vanilla or butter or not both....."<<endl;
    van.display();
    butter.display();
    nothing.display();

    cout<<"Number of students who like neither vanilla nor butterscotch are "<<nothing.length()<<endl;        
    
}