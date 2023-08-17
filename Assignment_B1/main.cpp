#include<iostream>
#include"firstcomefirstserve.cpp"
#include"priority.cpp"
#include"smallestjobfirst.cpp"
#include"roundrobin.cpp"
#include<vector>
using namespace std;

int main(){
    long burstTimes[5] = { 3 , 6 , 1 , 2 , 4 } ; 
    long arrivalTimes[5] = { 0 , 1 , 3 , 2 , 4 } ; 
    long priorities[5] = {3,1,4,5,2};
    vector<Process> processes;
    for(int i=0;i<5;i++){
        Process p = Process("P" + to_string(i+1));
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        p.priority = priorities[i];
        processes.push_back(p);
    }

    cout<<"FCFS"<<endl;
    FirstComeFirstServe scheduler1(processes);
    scheduler1.schedule();
    cout<<endl;

    cout<<"Priority"<<endl;
    Priority scheduler2(processes);
    scheduler2.schedule();
    cout<<endl;

    cout<<"SJF"<<endl;
    SmallestJobFirst scheduler3(processes);
    scheduler3.schedule();
    cout<<endl;     

    cout<<"RoundRobin"<<endl;
    RoundRobin scheduler4(processes);
    scheduler4.schedule(2L);
    cout<<endl;
    
    return 0;
}