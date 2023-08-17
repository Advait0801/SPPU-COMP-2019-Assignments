#include<iostream>
#include "assembler.cpp"
using namespace std;

int main() {
    Assembler assembler( "testcase2.txt" ) ;
    assembler.performPass1() ; 
    return 0;
}