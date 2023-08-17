#include <iostream>
using namespace std;

void swap(int *arr,int i1,int i2){
    //this function swaps the elements in the array at i1 and i2 indices
    int temp = *(arr + i2);    //*(arr + i2) == arr[i2]
    *(arr + i2) = *(arr + i1); 
    *(arr + i1) = temp;
}

void display(int *arr,int n){
    //this function displays the entire array
    for(int i=0;i<n;i++){
        cout<<*(arr + i)<<" ";
    }
    cout<<endl;
}

int linear_search(int *arr,int n,int key){
    /*this function performs linear search to find the index position of the element 
    if not present returns -1
    key is the element to be found*/

    int i = 0;  //i is the current index 
    while(i<n){
        if(arr[i] == key){
            return i;
        }
        i++;
    }
    return -1;

    //Time Complexity = O(n)
}

int sentinel_search(int *arr,int n,int key){
    /*this function performs linear search to find the index position of the element 
    if not present returns -1
    key is the element to be found*/

    if(arr[n-1] == key){
        return n-1;
    }

    else{
        arr[n-1] = key;
        int index = linear_search(arr,n-1,key);
        return index;
    }

    //Time Complexity = O(n)
}

int binary_search_recursive(int *arr,int key,int low,int high){
    /*this function performs recursive binary search to find the index position of the element 
    if not present returns -1
    key is the element to be found*/

    if(low<=high){
        int mid = (low + high)/2;
        if(arr[mid] > key){   //key is smaller than element at mid
            return binary_search_recursive(arr,key,mid + 1,high);
        }

        else if(arr[mid] < key){    //key is greater than element at mid
            return binary_search_recursive(arr,key,low,mid - 1);
        }

        else{      //key is same as that at mid
            return mid;
        }
    }

    return -1;

    //Time Complexity = O(log2(n))
}

int binary_search_iterative(int *arr,int n,int key){
    /*this function performs iterative binary search to find the index position of the element 
    if not present returns -1
    key is the element to be found*/

    int low = 0;
    int high = n-1;
    
    while(low<=high){
        int mid = (low + high)/2;
        if(arr[mid] == key){    //key is same as that at mid
            return mid;
        }

        else if(arr[mid] < key){      //key is greater than element at mid
            high = mid - 1;
        }

        else{    //key is smaller than element at mid
            low = mid + 1;
        }
    }

    return -1;

    //Time Complexity = O(log2(n))
}

int fibonacci_search(int *arr,int n,int key){
    /*this function performs fibonacci search to find the index position of the element 
    if not present returns -1
    key is the element to be found*/

    int f0 = 0;
    int f1 = 1;
    int f2 = 1;

    //generating fibonacci sequence till a number greater than equal to n
    while(f2 < key){
        f0 = f1;
        f1 = f2;
        f2 = f0 + f1;
    }

    int offset = -1;   //marking eliminated range from front
    
    while(f2 > 1){
        int index = std::min(offset + f0 , n - 1); //deciding the index position to start comparisons

        if(arr[index] < key){    //move down the fibonacci sequence by 1 step and reset the offset
            f2 = f1;
            f1 = f0;
            f0 = f2 - f1;
            offset = index;
        }

        else if(arr[index] > key){    //move down the fibonacci sequence by 2 steps and don't reset the offset
            f2 = f0;
            f1 = f1 - f0;
            f0 = f2 - f1;
        }

        else{
            return index;    //element found
        }
    }

    /*Since there might be a single element remaining for comparison, check if f1 is 1. 
    If Yes, compare key with that remaining element. If match, return index.*/
    if(f1 && arr[offset + 1] == key){
        return offset + 1;
    }

    return -1;
    
    //Time Complexity = O(log n)
}

void insertion_sort(int *arr,int n){
    //this function performs insertion sort to sort the array and displays it

    for(int i=0;i<n;i++){
        for(int j=i;j>0;j--){
            if(arr[j] < arr[j-1]){
                swap(arr,j,j-1);
            }
        }
    }

    display(arr,n);

    //Time Complexity = O(n2)
}

void shell_sort(int *arr,int n){
    //this function performs shell sort to sort the array and displays it

    int step = n/2;  //deciding the gap for comparison

    while(step>0){
        for(int i=step;i<n;i++){
            for(int j = i;j > step - 1; j -= step){
                if(arr[j] < arr[j-step]){
                    swap(arr,j,j-step);
                }
            }
        }

        step = step/2;
    }   

    display(arr,n);

    //Time Complexity = O(n2) 
}

void selection_sort(int *arr,int n){
    //this function performs selection sort to sort the array and displays it

    for(int i=0;i<n-1;i++){
        int min_index = i;         //initializing the min index to i i.e element at ith index is smallest
        for(int j=i+1;j<n;j++){
            if(arr[j] < arr[min_index]){
                min_index = j;    //if the current element is smaller than the min index then chanje the min index
            }
        }

        if(min_index != i){   //if min index position is changed the swap it with first comparison element
            swap(arr,i,min_index);
        }
    }

    display(arr,n);

    //Time Complexity = O(n2)
}

void bubble_sort(int *arr,int n){
    //this function performs bubble sort to sort the array and displays it

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr,j,j+1);
            }
        }
    }

    display(arr,n);

    //Time Complexity = O(n2)
}

int partition_as_first(int *arr,int low,int high){
    /*This function takes first element as pivot, the function
    places the pivot element(first element) on its sorted position and all the element lesser than pivot will placed
    left to it, and all the element greater than pivot placed right to it.*/
 
    int pivot = arr[low];  //pivot element is first element

    //Index of smaller element and indicates the right position of pivot found so far
    int i = high + 1;

    for(int j=high;j>low;j--){
        if(arr[j] >= pivot){
            i--;
            swap(arr,j,i);
        }
    }

    swap(arr,low,i-1);

    return i-1;    
}

int partition_as_middle(int *arr,int low,int high){
    /*This function takes middle element as pivot, the function
    places the pivot element(middle element) on its sorted position and all the element lesser than pivot will placed
    left to it, and all the element greater than pivot placed right to it.*/

    int pivot = arr[(low + high) / 2];  //pivot as middle element

    int i = low - 1;  //smaller elements than pivot
    int j = high + 1;    //greater elements than pivot

    while(true){
        i++;
        j--;

        while(arr[i] < pivot){
            i++;
        }

        while(arr[j] > pivot){
            j--;
        }

        if(i>=j){
            return j;
        }

        swap(arr,i,j);
    }
}

int partition_as_last(int *arr,int low,int high){
    /* This function takes last element as pivot,
    places the pivot element at its correct position in sorted array, 
    and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */

    int pivot = arr[high];  //pivot as last element

    int i = low - 1;

    for(int j=low;j<high;j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr,i,j);
        }
    }

    swap(arr,high,i+1);

    return i+1;
}

void quick_sort1(int *arr,int low,int high){
    if(low<high){
        int p1 = partition_as_first(arr,low,high);  //pivot index
        quick_sort1(arr,low,p1-1);         //recursion call
        quick_sort1(arr,p1+1,high);        //recursion call
    }
}

void quick_sort2(int *arr,int low,int high){
    if(low<high && low>=0 && high>=0){
        int p2 = partition_as_middle(arr,low,high);   //pivot index
        quick_sort2(arr,low,p2);     //recursion call
        quick_sort2(arr,p2+1,high);     //recursion call
    }
}

void quick_sort3(int *arr,int low,int high){
    if(low<high){
        int p3 = partition_as_last(arr,low,high);  //pivot index
        quick_sort3(arr,p3+1,high);      //recursion call
        quick_sort3(arr,low,p3-1);       //recursion call
    }
}

void merge(int *arr,int low,int mid,int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];      //copy of left array
    int right[n2];     //copy of right array

    for(int i=0;i<n1;i++){
        left[i] = arr[low + i];    //initializing left array
    }
    for(int j=0;j<n2;j++){
        right[j] = arr[mid + 1 + j];    //initializing right array 
    }

    int i,j,k;
    i = 0;
    j = 0;
    k = low;

    while(i<n1 && j<n2){
        if(left[i] < right[j]){     //if left array element is smaller than right array element
            arr[k] = left[i];
            i++;
            k++;
        }

        else if(left[i] > right[j]){       //if left array element is greater than right array element
            arr[k] = right[j];
            j++;
            k++;
        }

        else{                  //if both are equal
            arr[k] = left[i];
            i++;
            j++;
            k++;
        }
    }

    while(i<n1){       //if any left array elements remain.  right array exhausted
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j<n2){      //if any right array elements remain.   left arry exhausted
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergesort(int *arr,int low,int high){
    if(low < high){
        int mid = low + (high - low)/2;
        mergesort(arr,low,mid);          //recursion call for left part
        mergesort(arr,mid + 1,high);     //recursion call fro right part 
        merge(arr,low,mid,high);        //merge both parts
    }
}

int main(){
    int arr[5] = {34,23,0,-1,100};
    mergesort(arr,0,4);
    display(arr,5);
    return 0;
}

