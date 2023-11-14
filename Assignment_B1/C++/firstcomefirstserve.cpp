#include<iostream>
#include"process.hpp"
#include<vector>
#include<queue>
using namespace std;

class FirstComeFirstServe{
    vector<Process> processes;

public:
    FirstComeFirstServe(vector<Process> process){
        this -> processes = process;        
    }

    void schedule(){
        queue<Process> readyQueue;
        vector<Process> ans;
        bool isExecuting = false;
        long time = 0;
        Process currentProcess = processes[0];
        int n = 0;
        while(n < processes.size()){
            for(Process p : processes){
                if(p.arrivalTime == time){
                    readyQueue.push(p); 
                }
            }

            if(isExecuting && time == currentProcess.responseTime + currentProcess.burstTime){
                isExecuting = false;
                currentProcess.completionTime = time;
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                ans.push_back(currentProcess);
                n++;
            }

            if(!readyQueue.empty() && !isExecuting){
                currentProcess = readyQueue.front();
                readyQueue.pop();
                currentProcess.responseTime = time;
                isExecuting = true;
            }
            time++;
        }

        long totalWaitTime = 0;
        long totalTurnAroundTime = 0;
        for(Process p : ans){
            totalWaitTime = totalWaitTime + p.waitTime;
            totalTurnAroundTime = totalTurnAroundTime + p.turnAroundTime;
            p.displayProcess();
        }

        float avgWaitTime = (float)totalWaitTime / ans.size();
        float avgTurnAroundTime = (float)totalTurnAroundTime / ans.size();

        cout<<"Average Wait Time = "<<avgWaitTime<<"seconds"<<endl;
        cout<<"Average TurnAroundTime = "<<avgTurnAroundTime<<"seconds"<<endl;
    }
};