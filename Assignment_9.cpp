#include <cstring>
#include <iostream>
#include <cmath>
using namespace std ;

template <class E>
class Stack {

private:
    int HEAD_INDEX;
    E *elements;
    int numElements;
    int capacity;

public:

    Stack(int capacity){
        this -> numElements = 0;
        this -> capacity = capacity;
        elements = new E[capacity];
    }

    void push(E element){
        if (numElements == 0){
            HEAD_INDEX = 0;
        }
        else{
            HEAD_INDEX++;
        }
        *(elements + HEAD_INDEX) = element;
        numElements += 1;
    }

    E pop() {
        if (numElements > 0) {
            E poppedElement = *( elements + HEAD_INDEX ) ; 
            HEAD_INDEX -= 1;
            numElements -= 1;
            return poppedElement;
        }
        else {
            return '0' ;
        }
    }

    int getNumElements() {
        return numElements ; 
    }

};

bool matching( char c1 , char c2 ) {
    return abs(int(c1) - int(c2)) <= 2 ;
}

class Solution {
public:
    bool isValid(string s) {
        Stack<char> stack( s.length() ); 
        for( char c : s ) {
            if( c == '(' || c == '[' || c == '{' ) {
                stack.push( c ) ; 
            }
            else {
                char popChar = stack.pop() ;
                if( !matching( popChar , c ) ) {
                    return false ; 
                }
            }
        }
        return stack.getNumElements() == 0 ;
    }
};

int main(){
    Solution s;
    bool b = s.isValid("()");
    cout<<b;

    return 0;
}