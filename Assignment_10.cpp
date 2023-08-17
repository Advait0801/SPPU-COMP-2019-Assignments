/*
Implement the Heap sort algorithm using heap data structure with
modularity of programming language.

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <queue>
using namespace std;

class Node{
    int data;
    Node *left, *right;

public:
    Node(){
        this -> data = 0;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    Node(int i){
        this -> data = i;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    friend class BT;
};

class BT{
    Node *root = nullptr;
    queue <Node *> q;
    int numNodes = 0;

    Node *maxHeapTree(Node *node){
        if(node == nullptr){
            return nullptr;
        }

        node -> left = maxHeapTree(node -> left);
        node -> right = maxHeapTree(node -> right);

        if(node -> left != nullptr && node -> left -> data > node -> data){
            int temp = node -> data;
            node -> data = node -> left -> data;
            node -> left -> data = temp;
        }
        if(node -> right != nullptr && node -> right -> data > node -> data){
            int temp = node -> data;
            node -> data = node -> right -> data;
            node -> right -> data = temp;
        }

        return node;
    }

    Node *lastNode(){
        queue <Node *> q;
        q.push(this -> root);
        Node *current = nullptr;

        while(!q.empty()){
            current = q.front();
            q.pop();

            if(current -> left != nullptr){
                q.push(current -> left);
            }
            if(current -> right != nullptr){
                q.push(current -> right);
            }
        }

        return current;
    }

    Node *deleteNode(Node *node,int key){
        if(node == nullptr){
            return nullptr;
        }

        if(node -> data == key){
            delete node;
            return nullptr;
        }

        node -> left = deleteNode(node -> left,key);
        node -> right = deleteNode(node -> right,key);
        return node;
    }

public:
    void insert(int value){
        if(this -> root == nullptr){
            this -> root = new Node(value);
            q.push(this -> root);
        }

        else{
            Node *newNode = new Node(value);
            Node *current = q.front();

            while(true){
                if(current -> left != nullptr && current -> right != nullptr){
                    q.push(current -> left);
                    q.push(current -> right);
                    q.pop();
                    current = q.front();
                }

                else if(current -> left == nullptr){
                    current -> left = newNode;
                    break;
                }

                else{
                    current -> right = newNode;
                    break;
                }
            }
        }
        numNodes++;
    }

    void BFStraversal(){
        queue <Node *> q;
        q.push(this -> root);
        Node *current = nullptr;

        while(!q.empty()){
            current = q.front();
            cout<<current -> data<<" ";
            q.pop();

            if(current -> left != nullptr){
                q.push(current -> left);
            }
            if(current -> right != nullptr){
                q.push(current -> right);
            }
        }
        cout<<endl;
    }

    void heapSort(){
        for(int i=0;i<numNodes;i++){
            maxHeapTree(this -> root);

            Node *last = lastNode();

            int temp = this -> root -> data;
            this -> root -> data = last -> data;
            last -> data = temp;

            cout<<last -> data<<" ";
            deleteNode(this -> root,last -> data);
        }
    }    
};

int main(){
    BT b;
    b.insert(87);
    b.insert(12);
    b.insert(75);
    b.insert(91);
    b.insert(44);
    b.insert(57);
    b.insert(68);
    
    b.BFStraversal();
    b.heapSort();
    return 0;
}