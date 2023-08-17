#include <iostream>
using namespace std;

class Node{
    Node *nextptr , *prevptr;
    int val;

public:
    friend class Binary;
};

class Binary{
    Node *start , *end;
    int num;

public:
    Binary(){
        start = nullptr;
        end = nullptr;
        num = 0;
    }

    ~Binary(){
        Node *deletenode = start;
        for(int i=0;i<num;i++){
            Node *newstart = deletenode -> nextptr;
            delete deletenode;
            deletenode = newstart;
        }
        num = 0;
    }
    
    void create(int n){
        while(n>0){
            if(num==0){
                end = new Node;
                end -> val = n%2;
                end -> nextptr = nullptr;
                end -> prevptr = nullptr;
                start = end;
            }

            else{
                Node *newstart = new Node;
                newstart -> val = n%2;
                start -> prevptr = newstart;
                newstart -> nextptr = start;
                newstart -> prevptr = nullptr;
                start = newstart;
            }

            n = n/2;
            num++;
        }

        Node *current = start;
        for(int i=0;i<num;i++){
            cout<<current -> val;
            current = current -> nextptr;
        }
        cout<<endl;
    }

    int invert(int x){
        if(x==0){
            return 1;
        }
        return 0;
    }

    void complement1s(){
        Node *current = start;
        for(int i=0;i<num;i++){
            int inverted = invert(current -> val);
            cout<<inverted;
            current = current -> nextptr;
        }
        cout<<endl;
    }

    void complement2s(){
        int complement1[num];
        Node *current = start;
        for(int i=0;i<num;i++){
            int inverted = invert(current -> val);
            complement1[i] = inverted;
            current = current -> nextptr;
        }

        int complement2[num];
        int carry = 1;
        for(int j=num-1;j>=0;j--){
            int sum = complement1[j] + carry;
            if(sum==2){
                carry = 1;
                complement2[j] = 0;
                
            }
            else{
                carry = 0;
                complement2[j] = sum;
            }
        }

        if(carry==1){
            cout<<carry;
            for(int k=0;k<num;k++){
                cout<<complement2[k];
            }
        }
        else{
            for(int k=0;k<num;k++){
                cout<<complement2[k];
            }
        }

        cout<<endl;
    }

    void add(Binary b){
        int result[32];
        int carry = 0;
        int i = 31;
        Node *bit1 = end;
        Node *bit2 = b.end;
        while(bit1!=nullptr && bit2!=nullptr && i>=0){
            int sum = bit1 -> val + bit2 -> val + carry;
            if(sum<2){
                result[i] = sum;
                carry = 0;
            }

            else if(sum==2){
                result[i] = 0;
                carry = 1;
            }

            else{
                result[i] = 1;
                carry = 1;
            }

            bit1 = bit1 -> prevptr;
            bit2 = bit2 -> prevptr;
            i--;
        }

        while(bit1!=nullptr && i>=0){
            int sum = bit1 -> val + carry;
            if(sum==2){
                result[i] = 0;
                carry = 1;
            }

            else{
                result[i] = sum;
                carry = 0;
            }

            bit1 = bit1 -> prevptr;
            i--;
        }

        while(bit2!=nullptr && i>=0){
            int sum = bit2 -> val + carry;
            if(sum==2){
                result[i] = 0;
                carry = 1;
            }

            else{
                result[i] = sum;
                carry = 0;
            }

            bit2 = bit2 -> prevptr;
            i--;
        }

        result[i] = carry;

        for(int j=i;j<32;j++){
            cout<<result[j];
        }
        cout<<endl;
    } 

};

int main(){
    Binary b,b1;
    b.create(10);
    b1.create(20);
    b.complement1s();
    b.complement2s();    
    b.add(b1);

    return  0;
}