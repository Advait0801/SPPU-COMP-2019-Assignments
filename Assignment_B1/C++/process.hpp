#ifndef PROCESS_H
#define PROCESS_H

#include<iostream>
using namespace std;

class Process{
public:
    string processName;
    int priority = 0;    
    long burstTime = 0;
    long arrivalTime = 0;
    long turnAroundTime = 0;
    long waitTime = 0;
    long completionTime = 0;
    long responseTime = 0;

    Process(){
        this -> processName = "";
    }

    Process(string name){
        this -> processName = name;
    }

    void displayProcess(){
        cout<<"Process "<<this -> processName<<" ----> Priority: "<<this -> priority<<", AT: "<<this -> arrivalTime<<", BT: "<<this -> burstTime<<", CT: " <<this -> completionTime<<", TAT: "<<this -> turnAroundTime<<", WT: "<<this -> waitTime<<", RT: "<<this -> responseTime<<endl;
    }
};

#endif