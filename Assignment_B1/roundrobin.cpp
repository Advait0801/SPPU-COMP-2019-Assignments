#include<iostream>
#include"process.hpp"
#include<unordered_map>
#include<vector>
using namespace std;

class RoundRobin{
    vector<Process> processes;

public:
    RoundRobin(vector<Process> process){
        this -> processes = process;
    }

    void schedule(long quantumTime){
        vector<Process> readyQueue;
        vector<Process> ans;

        unordered_map<string,long> burstTimes;
        for(Process p : processes){
            burstTimes[p.processName] = p.burstTime;
        }

        long time = 0;
        bool isExecuting = false;
        Process currentProcess = processes[0];
        int n = 0, step = 0;
        long currentRemainingBurstTime = 1000L;

        while(n < processes.size()){
            for(Process p : processes){
                if(p.arrivalTime == time){
                    readyQueue.push_back(p);
                }
            }

            if(currentRemainingBurstTime == 0L){
                currentProcess.responseTime = currentProcess.responseTime - currentProcess.arrivalTime;
                currentProcess.burstTime = burstTimes[currentProcess.processName];
                currentProcess.completionTime = time;
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                ans.push_back(currentProcess);
                isExecuting = false;
                n++;

                if(!readyQueue.empty()){
                    currentProcess = readyQueue[0];
                    if(currentProcess.responseTime == 0L) currentProcess.responseTime = time;
                    currentRemainingBurstTime = currentProcess.burstTime;
                    step = time + quantumTime;
                    isExecuting = true;
                    readyQueue.erase(readyQueue.begin());
                }
            }

            if(isExecuting){
                if(time == step){
                    currentProcess.burstTime = currentRemainingBurstTime;
                    readyQueue.push_back(currentProcess);

                    if(!readyQueue.empty()){
                        currentProcess = readyQueue[0];
                        if(currentProcess.responseTime == 0L) currentProcess.responseTime = time;
                        currentRemainingBurstTime = currentProcess.burstTime;
                        step = time + quantumTime;
                        isExecuting = true;
                        readyQueue.erase(readyQueue.begin());
                    }      
                }                          
            }
            else{
                if(!readyQueue.empty()){
                    currentProcess = readyQueue[0];
                    currentRemainingBurstTime = currentProcess.burstTime;
                    step = time + quantumTime;
                    isExecuting = true;
                    readyQueue.erase(readyQueue.begin());
                }                
            }

            if(isExecuting){
                currentRemainingBurstTime--;
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
        cout<<"Average TurnAround Time = "<<avgTurnAroundTime<<"seconds"<<endl;
    }
};