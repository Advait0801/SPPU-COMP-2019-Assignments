#include<iostream>
#include "assembler.cpp"
using namespace std;

int main() {
    std::cout << "----------- Test case 1 ------------------ \n\n\n" ; 
    Assembler assembler1( "testcase1.txt" ) ;
    assembler1.performPass1() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 2 ------------------ \n\n\n" ; 
    Assembler assembler2( "testcase2.txt" ) ;
    assembler2.performPass1() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 3 ------------------ \n\n\n" ; 
    Assembler assembler3( "testcase3.txt" ) ;
    assembler3.performPass1() ; 
    std::cout << "\n\n\n" ;
    return 0;
}