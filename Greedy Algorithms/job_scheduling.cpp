#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Job{
public:
    int id = 0;
    int profit = 0;
    int deadline = 0;

    Job(int i, int p, int d){
        this -> id = i;
        this -> profit = p;
        this -> deadline = d;
    }

    void print(){
        cout<<"Job ---->  id = "<<id<<", deadline = "<<deadline<<", profit = "<<profit<<endl;
    }
};


int jobScheduling(vector<Job> &jobs){
    int n = jobs.size();

    for(int i=0;i<n;i++){
        int j = i;

        while(jobs[j].profit > jobs[j-1].profit && j > 0){
            Job temp = jobs[j];
            jobs[j] = jobs[j-1];
            jobs[j-1] = temp;
            j--;
        }

        vector<int> deadlines(n, 0);
        for(j=0;j<n;j++){
            deadlines[j] = jobs[j].deadline;
        }
        int maxDeadline = *max_element(deadlines.begin(), deadlines.end());

        vector<bool> slotStatus(maxDeadline, true);
        vector<Job> maxProfitSeq;

        for(j=0;j<n;j++){
            Job job = jobs[j];

            for(int k=job.deadline;k>=0;k--){
                if(slotStatus[k] == true){
                    slotStatus[k] = false;
                    maxProfitSeq.push_back(job);
                    break;
                }
            }
        }

        int m = maxProfitSeq.size();
        int maxProfit = 0;
        for(j=0;j<m;j++){
            maxProfitSeq[j].print();
            maxProfit += maxProfitSeq[j].profit;
        }

        return maxProfit;      
        
    }
}