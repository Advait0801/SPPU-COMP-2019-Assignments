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
    }

    int maxDeadline = INT_MIN;
    for(int i=0;i<n;i++){
        maxDeadline = max(maxDeadline, jobs[i].deadline);
    }

    vector<bool> slotStatus(maxDeadline, true);
    vector<Job> maxProfitSequence;

    for(int i=0;i<n;i++){
        Job job = jobs[i];

        for(int j=job.deadline-1;j>=0;j--){
            if(slotStatus[j] == true){
                slotStatus[j] = false;
                maxProfitSequence.push_back(job);
                break;
            }
        }
    }

    int maxProfit = 0;
    int m = maxProfitSequence.size();
    for(int i=0;i<m;i++){
        maxProfitSequence[i].print();
        maxProfit += maxProfitSequence[i].profit;
    }

    return maxProfit;
}


int main(){
    vector<Job> jobs = {
        Job(1, 20, 2),
        Job(2, 15, 2),
        Job(3, 10, 1),
        Job(4, 5, 3),
        Job(5, 1, 3),
    };

    int ans = jobScheduling(jobs);
    cout<<"Max Profit = "<<ans<<endl;

    return 0;
}