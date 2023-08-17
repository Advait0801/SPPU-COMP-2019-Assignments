#include <iostream>
using namespace std;

class Node
{
    Node *next;
    int value;

public:
    friend class List;
};

class List
{
private:
    Node *start , *head;
    int num;
    
public:
    List()
    {
        start = nullptr;
        head = nullptr;
        num = 0;
    }

    ~List()
    {
        Node *ptr = start;
        for(int i=1;i<=num;i++)
        {
            Node *node = ptr -> next;
            delete ptr;
            ptr = node;
        }    
    }

    void insert_at_front()
    {
        int item;
        cout<<"Enter the value to be inserted at beginning: ";
        cin>>item;
        if(num==0)
        {
            
            start = new Node;
            start -> value = item;
            head = start;
        }
        else
        {
            Node *self = start;
            Node *newnode = new Node;
            newnode -> value = item;
            newnode -> next = self;
            start = newnode;
        }

        num++;
    }

     void insert_at_index()
    {
        int object,index;
        cout<<"Enter after what index you would like to insert the value: ";
        cin>>index;
        cout<<"Enter value to be inserted: ";
        cin>>object;
                
        int i = 0;
        Node *self = start;
        while (i<index)
        {
            self = self -> next;
            i++;
        }

        Node *newnode = new Node;
        newnode -> value = object;
        newnode -> next = self -> next;
        self -> next = newnode;
        num++;
    }

    void insert_at_back()
    {
        int element;
        cout<<"Enter element to be inserted at end of the list: ";
        cin>>element;
        if(num==0)
        {
            start = new Node;
            start -> value = element;
            head = start;
        }

        else
        {
            Node *self = head;
            Node *newnode = new Node;
            newnode -> value = element;
            self -> next = newnode;
            head = newnode;
        }

        num++;
    }   

    void display()
    {
        Node *a = start;
        for(int i=1 ; i<=num ; i++)
        {
            cout<<a->value<<"\t";
            a = a->next;
        }
    }  

};    
    

int main()
{  
    List l;
    while( true )
    {
        int choice;
        cout<<"Press 1 for insertion at beginning, 2 for at an index and 3 for inseting at end......Press 0 for displaying the list: ";
        cin>>choice;
        if(choice==1)
            l.insert_at_front();
        if(choice==2)
            l.insert_at_index();
        if(choice==3)
            l.insert_at_back();
        if(choice==0)
        {
            l.display();  
            break;  
        }
                
    }

      
}