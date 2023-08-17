#include <iostream>
using namespace std;

class Queue{
    int front , rear , num , capacity;
    int *elements;

public:
    Queue(int size){
        this -> capacity = size;
        this -> front = -1;
        this -> rear = this -> front;
        elements = new int[capacity];
        this -> num = 0;
    }

    ~Queue(){
        delete elements;
        num=0;
    }

    bool isEmpty(){
        if(num==0){
            return true;
        }
        else{
            return false;
        }
    }

    bool isFull(){
        if(this -> num==this -> capacity){
            return true;
        }
        else{
            return false;
        }
    }

    void enqueue(int item){
        if(!isFull()){
            if(isEmpty()){
                front = 0;
                rear++;
                elements[rear] = item;
            }

            else{
                rear++;
                elements[rear] = item;
            }
            num++;
        }

        else{
            cout<<"Queue is full.Can't add more elements....."<<endl;
        }
    }

    void dequeue(){
        if(!isEmpty()){
            cout<<"Element deleted: "<<elements[front];
            cout<<endl;
            front++;
            num--;
        }

        else{
            cout<<"Queue is empty...."<<endl;
        }
    }

    void display(){
        if(!isEmpty()){
            for(int i=front;i<=rear;i++){
                cout<<this -> elements[i]<<"\t";
            }
        }

        else{
            cout<<"Queue is empty......"<<endl;
        }
    }
};

int main(){
    cout<<"this is program to add or delete elements in queue......"<<endl;
    cout<<"Enter size of queue: ";
    int size;
    cin>>size;
    Queue q(size);
    while(true){
        int option;
        cout<<"Press 1 for inserting element,2 for deleting an element and 0 for displaying the queue...."<<endl;
        cin>>option;
        if(option==1){
            int item;
            cout<<"Enter element to insert: ";
            cin>>item;
            q.enqueue(item);
        }

        else if(option==2){
            q.dequeue();
        }

        else if(option==0){
            cout<<"Following is the queue.."<<endl;
            q.display();
            break;
        }

        else{
            cout<<"Invalid option..Try again..."<<endl;
        }
    }

    return 0;
}
