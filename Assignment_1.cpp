#include <iostream>
using namespace std;

class Complex{
    int real , imaginary;

public:
    Complex(){
        real = 0;
        imaginary = 0;
    }

    Complex(int r,int i){
        real = r;
        imaginary = i;
    }

    Complex operator +(Complex &p){
        Complex c;
        c.real = this -> real + p.real;
        c.imaginary = this -> imaginary + p.imaginary;
        return c;
    }

    Complex operator -(Complex &p){
        Complex c;
        c.real = this -> real - p.real;
        c.imaginary = this -> imaginary - p.imaginary;
        return c;
    }

    Complex operator *(Complex &p){
        Complex c;
        c.real = this -> real * p.real - this -> imaginary * p.imaginary;
        c.imaginary = this -> real * p.imaginary + this -> imaginary * p.real;
        return c;
    }

    friend ostream &operator<<(ostream &output,Complex &c){
        if(c.imaginary<0){
            output<<c.real<<" - "<<abs(c.imaginary)<<"i"<<endl;
        }
        else{
            output<<c.real<<" + "<<c.imaginary<<"i"<<endl;
        }
        
        return output;
    }

    friend istream &operator>>(istream &input,Complex &c){
        cout<<"Enter real and imaginary part of the complex no with a space.."<<endl;
        input>>c.real>>c.imaginary;
        return input;
    }
};

int main(){
    Complex c1,c2(3,4);
    cin>>c1;
    cout<<endl;
    cout<<"The 1st complex no is.."<<endl;
    cout<<c1<<endl;
    cout<<"The 2nd complex no is.."<<endl;
    cout<<c2<<endl;
    
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = c1 * c2;

    cout<<"The addition of these 2 complex nos is.."<<endl;
    cout<<c3<<endl;

    cout<<"The subtraction of these 2 complex nos is.."<<endl;
    cout<<c4<<endl;

    cout<<"The multiplication of these 2 complex nos is.."<<endl;
    cout<<c5<<endl;

    return 0;
}