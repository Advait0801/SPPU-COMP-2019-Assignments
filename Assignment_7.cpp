#include <iostream>
#include <ios>
#include <fstream>
using namespace std;

void insert( string text ) {
	fstream outputStream ;
	outputStream.open( "data.txt" , ios::out ) ;
	outputStream.write( (char*)&text[0] , text.length() ) ;
	outputStream.close() ;
}

void modify( string text , int position ) {
	fstream outputStream ;
	outputStream.open( "data.txt" , ios::in | ios::out ) ;
	outputStream.seekp( position , ios::beg ) ;
	outputStream.write( (char*)&text[0] , text.length() ) ;
	outputStream.close() ;
}

string read( int numBytes ) {
	fstream inputStream ;
	inputStream.open( "data.txt" , ios::in ) ;
	char data[ numBytes ] ;
	inputStream.read( &data[0] , numBytes ) ;
	inputStream.close() ;
	return string( data ) ;
}

int main() {
	insert( "Hello World" ) ;
	cout << read( 11 ) << "\n" ;
	modify( "Python" , 6 ) ;
	cout << read( 16 ) << "\n" ;
	return 0;
}