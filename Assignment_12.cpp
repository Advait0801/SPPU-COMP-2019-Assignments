#include <iostream>
#include <map>
using namespace std;

int main(){
    map <string,int> states;
    int n;
    cout<<"Enter no of states you want to enter: ";
    cin>>n;

    cout<<"Enter states name as single string..Dont give spaces.."<<endl;
    for(int i=0;i<n;i++){
        string s;
        int population;
        cout<<"Enter state name without space: ";
        cin>>s;
        cout<<"Enter its population: ";
        cin>>population;
        states[s] = population;  
        cout<<endl;      
    }

    try{
        string state;
        cout<<"Enter states name to cfind its popuation: ";
        
        cin>>state;
        int p = states[state];
        if(p==0){
            throw state;
        }
        else{
            cout<<"The population of "<<state<<" is "<<p<<endl;
        }
    }
    catch(string state)
    {
        cout<<"No such state exists...."<<endl;
    }      

    return 0;
}