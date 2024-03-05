#include<iostream>
#include<vector>
using namespace std;

void selectionSort(vector<int> &nums){
    int n = nums.size();

    for(int i=0;i<n;i++){
        int mini = nums[i];
        int index = i;

        for(int j=i+1;j<n;j++){
            if(nums[j] < mini){
                mini = nums[j];
                index = j;
            }
        }

        int temp = nums[i];
        nums[i] = nums[index];
        nums[index] = temp;
    }

    for(int i=0;i<n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}


int main(){
    vector<int> v = {1, 0, -99, 99, 5};
    selectionSort(v);

    return 0;
}