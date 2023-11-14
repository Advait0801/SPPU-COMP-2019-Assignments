#include<iostream>
#include"process.hpp"
#include<vector>
using namespace std;

class Priority{
    vector<Process> processes;

public:
    Priority(vector<Process> process){
        this -> processes = process;
    }

    void schedule(){
        vector<Process> ans;
        vector<Process> readyQueue;
        long time = 0;
        bool isExecuting = false;
        Process currentProcess = processes[0];
        int n = 0;
        while(n < processes.size()){
            for(Process p : processes){
                if(p.arrivalTime == time){
                    readyQueue.push_back(p);
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
                int maxPriority = 999;
                int processIndex = 0;
                for(int i=0;i<readyQueue.size();i++){
                    if(readyQueue[i].priority < maxPriority){
                        maxPriority = readyQueue[i].priority;
                        currentProcess = readyQueue[i];
                        processIndex = i;
                    }
                }
                currentProcess.responseTime = time;
                readyQueue.erase(readyQueue.begin() + processIndex);
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