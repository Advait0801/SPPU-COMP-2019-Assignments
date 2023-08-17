#include<iostream>
#include <vector>
#include <sstream>
#include "mnemonics.cpp"
using namespace std;

class Tokenizer {
    MnemonicTable mnemonicTable;

public:
    vector<string> getTokens( string instruction ) {
        stringstream stream( instruction ) ; 
        string token;
        vector<string> tokens;
        while( stream >> token ) {
            tokens.push_back( token ) ; 
        }

        string label, mnemonic, operand1, operand2;
        if( mnemonicTable.isMnemonic( tokens[0] ) ) {
            mnemonic = tokens[0] ; 
            if( tokens.size() == 2 ) {
                operand1 = tokens[1] ; 
            }
            else if( tokens.size() == 3 ) {
                operand1 = tokens[1] ; 
                operand2 = tokens[2] ; 
            }
        }
        else if( mnemonicTable.isMnemonic( tokens[1] ) ) {
            label = tokens[0] ; 
            mnemonic = tokens[1] ; 
            if( tokens.size() == 3 ) {
                operand1 = tokens[2] ; 
            }
            else if( tokens.size() == 4 ) {
                operand1 = tokens[2] ; 
                operand2 = tokens[3] ; 
            }
        }

        return { label , mnemonic , operand1 , operand2 };
    }
} ;