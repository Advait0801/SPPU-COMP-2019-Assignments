#include <iostream>
using namespace std;

class Deque{
    int num , capacity;
    int *arr;
    int front , rear;

public:
    Deque(){
        cout<<"Enter the capacity of the array: ";
        cin>>this -> capacity;
        this -> arr = new int[capacity];
        this -> num = 0;
        this -> front = -1;
        this -> rear = -1;
    }

    ~Deque(){
        delete arr;
        num = 0;
    }

    bool isEmpty(){
        return this -> num == 0;
    }

    bool isFull(){
        return this -> num == this -> capacity;
    }

    void display(){
        for(int i=front;i<=rear;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }

    void insert_at_front(int item){
        if(!isFull()){
            if(isEmpty()){
                front = 0;
                rear = 0;
                arr[0] = item;
                num++;
            }

            else{
                for(int i=rear+1;i>front;i--){
                    arr[i] = arr[i-1];
                }
                arr[front] = item;
                rear++;
                num++;
            }

            cout<<"Now array is..."<<endl;
            this -> display();
        } 

        else{
            cout<<"Deque is full......"<<endl;
        }       
    }

    void insert_at_rear(int item){
        if(!isFull()){
            if(isEmpty()){
                front = 0;
                rear = 0;
                arr[0] = item;
                num++;
            }

            else{
                rear++;
                arr[rear] = item;
                num++;
            }

            cout<<"Now array is..."<<endl;
            this -> display();
        }

        else{
            cout<<"Deque is full......"<<endl;
        }       
    }

    void delete_at_front(){
        if(!isEmpty()){
            cout<<"Element deleted : "<<arr[front]<<endl;
            for(int i=front;i<rear;i++){
                arr[i] = arr[i+1];
            }
            rear--;
            num--;

            cout<<"Now array is..."<<endl;
            this -> display();
        }

        else{
            cout<<"Deque is empty...."<<endl;
        }
    }

    void delete_at_rear(){
        if(!isEmpty()){
            cout<<"Element deleted : "<<arr[rear]<<endl;
            rear--;
            num--;

            cout<<"Now array is..."<<endl;
            this -> display();
        }

        else{
            cout<<"Deque is empty...."<<endl;
        }
        
    }
};

int main(){
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

        else{
            cout<<"Invalid option...Try again..."<<endl;
        }

        cout<<"Press y to continue and n to exit: ";
        char c;
        cin>>c;
        if(c=='n'){
            break;
        }
    }
}