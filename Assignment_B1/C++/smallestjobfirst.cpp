#include<iostream>
#include"process.hpp"
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class SmallestJobFirst{
    vector<Process> processes;

public:
    SmallestJobFirst(vector<Process> process){
        this -> processes = process;
    }

    void schedule(){
        unordered_map<string,long> burstTimes;
        for(Process p : processes){
            burstTimes[p.processName] = p.burstTime;
        }

        long time = 0;
        bool isExecuting = false;
        Process currentProcess = processes[0];
        int n = 0;
        long currentRemainingBurstTime = 1000L;

        vector<Process> readyQueue;
        vector<Process> ans;

        while(n < processes.size()){
            for(Process p : processes){
                if(p.arrivalTime == time){
                    readyQueue.push_back(p);
                }
            }

            if(currentRemainingBurstTime == 0){
                currentProcess.responseTime = currentProcess.responseTime - currentProcess.arrivalTime;
                currentProcess.burstTime = burstTimes[currentProcess.processName];
                currentProcess.completionTime = time;
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                ans.push_back(currentProcess);
                n++;
                isExecuting = false;

                if(!readyQueue.empty()){
                    sort(readyQueue.begin(), readyQueue.end(), [](const Process &p1,const Process &p2){
                        return p1.burstTime < p2.burstTime;
                    });
                    if(readyQueue[0].responseTime == 0L) readyQueue[0].responseTime = time;
                    currentRemainingBurstTime = readyQueue[0].burstTime;
                    currentProcess = readyQueue[0];
                    readyQueue.erase(readyQueue.begin());
                    isExecuting = true;
                }
            }
            else{
                if(!readyQueue.empty()){
                    sort(readyQueue.begin(), readyQueue.end(), [](const Process &p1,const Process &p2){
                        return p1.burstTime < p2.burstTime;
                    });

                    if(isExecuting){
                        if(readyQueue[0].burstTime < currentRemainingBurstTime){
                            currentProcess.burstTime = currentRemainingBurstTime;
                            readyQueue.push_back(currentProcess);
                            currentProcess = readyQueue[0];
                            readyQueue.erase(readyQueue.begin());
                            currentRemainingBurstTime = currentProcess.burstTime;
                            isExecuting = true;
                        }
                    }
                    else{
                        currentProcess = readyQueue[0];
                        readyQueue.erase(readyQueue.begin());
                        currentRemainingBurstTime = currentProcess.burstTime;
                        isExecuting = true;                        
                    }
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