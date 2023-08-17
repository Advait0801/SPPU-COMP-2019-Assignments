#include <iostream>
using namespace std;

template <typename T>
class Stack{
    T arr[20];
    int top , num;

public:
    Stack(){
        this -> top = -1;
        this -> num = 0;
    }

    bool isEmpty(){
        return this -> num == 0;
    }

    void push(T item){
        if(isEmpty()){
            arr[0] = item;
            top++;
            num++;
        }

        else{
            top++;
            arr[top] = item;
            num++;
        }
    }

    void pop(){
        arr[top] = NULL;
        top--;
        num--;
    }

    T gettop(){
        return this -> arr[top];
    }
};