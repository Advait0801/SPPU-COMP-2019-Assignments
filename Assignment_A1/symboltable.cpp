#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class SymbolTable {
    vector<pair<string,int>> symbols ; 
    vector<string> symbolValues;

public:
    bool find( string &symbolName ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbolName ) {
                return true;
            }
        }
        return false;
    }

    int getSymbolIndex( string &symbolName ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbolName ) {
                return i+1;
            }
        }
        return -1 ; 
    }

    int getSymbolAddress( string &symbolName ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbolName ) {
                return symbols[i].second;
            }
        }
        return -1 ; 
    }

    void setSymbol( string &symbolName , int address ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbolName ) {
                symbols[i].second = address ; 
                return;
            }
        }
        symbols.push_back( { symbolName , address } ) ; 
    }

    void setSymbolValue( string &symbolName , string value ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbolName ) {
                //symbols[i].second = address ; 
                break;
            }
        }
    }

    void print() {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            std::cout << (i+1) << " => " << symbols[i].first << " => " << symbols[i].second << "\n" ; 
        }
    }
}; 