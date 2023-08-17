#include <iostream>
using namespace std;

template <typename T> class Temp{
    T *arr;
    int capacity;
public:
    Temp(){
        cout<<"Enter size of the array: ";
        cin>>this -> capacity;
        arr = new T[capacity];
        cout<<"Enter the elements of the array"<<endl;
        for(int i=0;i<capacity;i++){
            T element;
            cout<<"Enter element: ";
            cin>>element;
            arr[i] = element;
        }        
    }

    void swap(int i1,int i2){
        T temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }

    void display(){
        for(int i=0;i<capacity;i++){
            cout<<arr[i]<<"\t";
        }
    }
    
    void selectionsort(){
        for(int i=0;i<capacity - 1;i++){
            int minindex = i;
            for(int j=i+1;j<capacity;j++){
                if(arr[j]<arr[minindex]){
                    minindex = j;
                }
            }

            this -> swap(i,minindex);
        }

        this -> display();        
    }
};

int main(){
    while(true){
        cout<<"Press 1 for sorting an integer array or 2 for float array.."<<endl;
        int choice;
        cin>>choice;

        if(choice==1){
            Temp <int> t1;
            cout<<endl;
            cout<<"Sorted array is..."<<endl;
            t1.selectionsort();
            cout<<endl;
        }

        if(choice==2){
            Temp <float> t2;
            cout<<endl;
            cout<<"Sorted array is..."<<endl;
            t2.selectionsort();
            cout<<endl;
        }

        cout<<"If you want to try again press y else press n: ";
        char c;
        cin>>c;

        if(c=='n'){
            break;
        }
    }

    return 0;
}