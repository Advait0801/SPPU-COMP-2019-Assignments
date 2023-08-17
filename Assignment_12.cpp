#include <iostream>
using namespace std;

class Node{
    int data , priority;
    Node *nextptr;

public:
    friend class PriorityQueue;

};

class PriorityQueue{
    Node *front ;
    int num;

public:
    PriorityQueue(){
        this -> front = nullptr;
        this -> num  = 0;        
    }

    ~PriorityQueue(){
        Node *deletenode = this -> front;
        for(int i=0;i<num;i++){
            Node *self = deletenode -> nextptr;
            delete deletenode;
            deletenode = self;            
        }
        num = 0;
    }

    bool isEmpty(){
        return num==0;
    }

    void enqueue(int item,int p){
        if(isEmpty()){
            front = new Node;
            front -> data = item;
            front -> priority = p;
            num++;
        }
        else if(p < front -> priority){
            Node *newnode = new Node;
            newnode -> data = item;
            newnode -> priority = p;
            newnode -> nextptr = front;
            front = newnode;
            num++;
        }        
        else{
            Node *current = this -> front;
            while(current -> nextptr!=nullptr && current -> nextptr -> priority <= p){
                current = current -> nextptr;
            }
            Node *newnode = new Node;
            newnode -> data = item;
            newnode -> priority = p;
            newnode -> nextptr = current -> nextptr;
            current -> nextptr = newnode;
            num++;
        }

        
    }

    void dequeue(){
        if(isEmpty()){
            cout<<"Queue is empty......"<<endl;
        }

        else{
            cout<<"Deleted element and its priority: "<<front -> data<<"\t"<<front -> priority;
            Node *current = this -> front;
            front = front -> nextptr;
            delete current;
            num--;
        }
    }

    void display(){
        if(isEmpty()){
            cout<<"Queue is empty..."<<endl;
        }
        
        else{
            Node *self = this -> front;
            for(int i=0;i<num;i++){
                cout<<self -> data<<"\t"<<self -> priority;
                cout<<endl;
                self = self -> nextptr;
            }
        }
        
    }
};

int main(){
    cout<<"This is a priority queue.....So enter data with priority..."<<endl;
    PriorityQueue P;
    while(true){
        cout<<"Press 1 for enter element and its priority,2 for deleting the front and 0 for display:"<<endl;
        int option;
        cin>>option;
        if(option==1){
            cout<<"Enter data and its priority with a blankspace in btw: ";
            int d,p;
            cin>>d>>p;
            P.enqueue(d,p);
        }

        else if(option==2){
            P.dequeue();
        }

        else if(option==0){
            P.display();
            break;
        }

        else{
            cout<<"Invalid option..Try again.."<<endl;
        }
    }

    return 0;
}
