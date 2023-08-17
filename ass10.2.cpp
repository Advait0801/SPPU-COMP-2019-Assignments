#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Node{
    Node *nextptr , *prevptr;
    char val;

public:
    friend class Stack;
};

class Stack{
    Node *top;
    int num;

public:
    Stack(){
        num = 0;
        top = nullptr;
    }

    ~Stack(){
        Node *deletenode = top;
        for(int i=0;i<num;i++){
            Node *newtop = deletenode -> prevptr;
            delete deletenode;
            deletenode = newtop;
        }
        num = 0;
    }

    bool isEmpty(){
        return num==0;
    }

    char pop(){
        if(!isEmpty()){
            Node *newtop = top -> prevptr;
            char topchar = top -> val;
            delete top;
            num--;
            top = newtop;
            return topchar;
        }
        else{
            return -1;
        }
    }

    void push(char c){
        if(isEmpty()){
            top = new Node;
            top -> val = c;
            top -> nextptr = nullptr;
            top -> prevptr = nullptr;
        }

        else{
            Node *newnode = new Node;
            newnode -> val = c;
            newnode -> prevptr = top;
            newnode -> nextptr = nullptr;
            top = newnode;
        }

        num++;
    }

    char topelement(){
        if(!isEmpty()){
            return top -> val;
        }

        return -1;
    }  
};

int precedence(char c){
    if(c=='(' || c==')'){
        return 3;
    }

    else if(c=='*' || c=='/'){
        return 2;
    }

    else if(c=='+' || c=='-'){
        return 1;
    }

    else{
        return 0;
    }
}

int chartoint(char c){
    return int(c) - 48;
}

char inttochar(int i){
    return char(i+48);
}

int operation(char op,int x,int y){
    if(op=='+'){
        return x+y;
    }

    else if(op=='-'){
        return x-y;
    }

    else if(op=='*'){
        return x*y;
    }

    else if(op=='/'){
        return x/y;
    }

    else{
        return -999999999;
    }
}

int main(){
    string infix;
    cout<<"Enter a valid infix expression using only round brackets if needed...Please don't give spaces..."<<endl;
    cin>>infix;

    //Infix to Postfix
    vector <char> operands;
    string postfix = "";
    Stack s;
    for(char i : infix){
        if(precedence(i)==0){
            postfix += i;
            operands.push_back(i);
        }

        else if(i=='(' || precedence(s.topelement()) < precedence(i) || s.topelement()=='('){
            s.push(i);
        }

        else if(i==')'){
            while(s.topelement()!='('){
                postfix += s.pop();
            }
            s.pop();
        }

        else{
            while(!s.isEmpty() && precedence(s.topelement()) >= precedence(i)){
                postfix += s.topelement();
                s.pop();
            }
            s.push(i);
        }
    }
    
    while(!s.isEmpty()){
        postfix += s.pop();
    }
    cout<<"The required postfix expression is....."<<endl;
    cout<<postfix<<endl;


    //Evaluation
    map <char,int> values;
    int value;
    for(int i=0;i<operands.size();i++){
        cout<<"Enter value of "<<operands[i]<<": ";
        cin>>value;
        values[operands[i]] = value;
    }

    Stack result;
    for(char c : postfix){
        if(precedence(c)==0){
            result.push(c);
        }

        else{
            int a , b;
            if(values.find(result.topelement()) == values.end()){
                b = chartoint(result.pop());
            }

            else{
                b = values[result.pop()];
            }

            if(values.find(result.topelement()) == values.end()){
                a = chartoint(result.pop());
            }

            else{
                a = values[result.pop()];
            }

            int r = operation(c , a , b);
            result.push(inttochar(r));
        }
    }

    cout<<"The result after evaluation is: "<<chartoint(result.pop())<<endl;
}



