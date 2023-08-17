#include <iostream>
using namespace std;

class Node{
    int data;
    Node *nextptr , *prevptr;

public:
    friend class Deque;
};

class Deque{
    int num;
    Node *front , *rear;

public:
    Deque(){
        this -> num = 0;
        this -> front = nullptr;
        this -> rear = front;
    }

    ~Deque(){
        Node *deletenode = front;
        for(int i=0;i<num;i++){
            Node *current = deletenode -> nextptr;
            delete deletenode;
            deletenode = current;
        }
        num=0;
    }

    bool isEmpty(){
        return num==0;
    }

    void insert_at_rear(int item){
        if(isEmpty()){
            front = new Node;
            front -> data = item;
            rear = front;
            num++;
        }

        else{
            Node *newnode = new Node;
            newnode -> data = item;
            rear -> nextptr = newnode;
            newnode -> prevptr = rear;
            rear = newnode;
            num++;
        }
    }

    void insert_at_front(int item){
        if(isEmpty()){
            front = new Node;
            front -> data = item;
            rear = front;
            num++;
        }

        else{
            Node *newnode = new Node;
            newnode -> data = item;
            newnode -> nextptr = front;
            front -> prevptr = newnode;
            front = newnode;
            num++;
        }
    }

    void delete_at_front(){
        if(isEmpty()){
            cout<<"Deque is empty..."<<endl;
        }

        else{
            cout<<"Deleted element: "<<front -> data<<endl;
            Node *current = front -> nextptr;
            delete front;
            front = current;
            num--;
        }        
    }

    void delete_at_rear(){
        if(isEmpty()){
            cout<<"Deque is empty..."<<endl;
        }

        else{
            cout<<"Deleted element: "<<rear -> data<<endl;
            Node *current = rear -> prevptr;
            delete rear;
            rear = current;
            num--;
        }        
    }

    void display(){
        if(isEmpty()){
            cout<<"Deque is empty..."<<endl;
        }

        else{
            Node *self = front;
            for(int i=0;i<num;i++){
                cout<<self -> data<<"\t";
                self = self -> nextptr;
            }
        }        
    }
};

int main(){
    cout<<"This is progra depecting deque..i.e.double ended queue...."<<endl;
    cout<<"So you can insert or delete element at both ends......"<<endl;
    Deque d;
    while(true){
        int option;
        cout<<"Press 1 for inserting at front,2 for inserting at rear,"<<endl;
        cout<<"3 for deleting from front,4 for deleting at end and 5 for displaying the deque...."<<endl;
        cin>>option;
        if(option==1){
            int item;
            cout<<"Enter element: ";
            cin>>item;
            d.insert_at_front(item);
        }

        else if(option==2){
            int item;
            cout<<"Enter element: ";
            cin>>item;
            d.insert_at_rear(item);
        }

        else if(option==3){
            d.delete_at_front();
        }

        else if(option==4){
            d.delete_at_rear();
        }

        else if(option==5){
            d.display();
            break;
        }

        else{
            cout<<"Invalid option...Try again..."<<endl;
        }
    }
}
