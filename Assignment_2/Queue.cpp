#include <iostream>
using namespace std;

template <typename T>
class Queue{
    T arr[20];
    int front , rear , num;

public:
    Queue(){
        this -> front = -1;
        this -> rear = -1;
        this -> num = 0;
    }

    bool isEmpty(){
        return this -> num == 0;
    }

    void push(T item){
        if(isEmpty()){
            arr[0] = item;
            front++;
            rear++;
            num++;
        }

        else{
            rear++;
            arr[rear] = item;
            num++;
        }
    }

    void pop(){
        for(int i=front;i<rear;i++){
            arr[i] = arr[i+1];
        }

        rear--;
        num--;
    }

    T getfront(){
        return arr[front];
    }
};