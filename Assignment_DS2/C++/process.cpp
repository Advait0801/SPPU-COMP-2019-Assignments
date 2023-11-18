#include<bits/stdc++.h>
using namespace std;

class Process{
public:
    const string MESSAGE_ELECTION = "ELECTION";
    static float ACTIVE_PROB;
    int identifier;
    bool coordinate;

    Process(){}

    Process(int identifier, bool coordinate = false){
        this -> identifier = identifier;
        this -> coordinate = coordinate;
    }

    static bool isActive(){
        srand(time(0));
        return ((double)rand()) / RAND_MAX <= ACTIVE_PROB;
    }

    string processMessage(){
        if(Process::isActive()){
            return "OK";
        }
        return "NOT_OK";
    }

    Process operator=(const Process &p){
        Process newProcess;
        newProcess.coordinate = p.coordinate;
        newProcess.identifier = p.identifier;
        return newProcess;
    }
};