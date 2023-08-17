/*
Beginning with an empty binary tree, Construct binary tree by inserting the 
values in the order given. After constructing a binary tree perform following 
operations on it-
 Perform inorder, preorder and post order traversal
 Change a tree so that the roles of the left and right pointers are swapped at 
every node 
 Find the height of tree
 Copy this tree to another [operator=] 
 Count number of leaves, number of internal nodes. 
 Erase all nodes in a binary tree. 

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include "Queue.cpp"
#include "Stack.cpp"
using namespace std;

class Node{
    int data;
    Node *left , *right;

public:
    Node(int i){
        this -> data = i;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    friend class BT;
};

class BT{
    Node *root;
    Queue <Node*> q;

public:
    BT(){
        this -> root = nullptr;
    }

    ~BT(){
        this -> deletenodes();
    }

    Node *getroot(){
        return this -> root;
    }

    void insert(int item){
        if(root == nullptr){
            root = new Node(item);
            q.push(root);
        }

        else{
            Node *newnode = new Node(item);
            Node *current = q.getfront();

            while(true){
                if(current -> left!=nullptr && current -> right!=nullptr){
                    q.push(current -> left);
                    q.push(current -> right);
                    q.pop();
                    current = q.getfront();
                }

                else if(current -> left == nullptr){
                    current -> left = newnode;
                    break;
                }

                else{
                    current -> right = newnode;
                    break;
                }
            }
        }
    }    

    void displayInorder(){
        Stack <Node *> s;
        Node *current = this -> root;

        while(!s.isEmpty() || current!=nullptr){
            //Reach the left most node of the current node
            //Push each left node into the stack
            while(current!=nullptr){
                s.push(current);
                current = current -> left;
            }

            //current is null so pop the stack and print the data
            current = s.gettop();
            s.pop();

            cout<<current -> data<<" ";

            //now check the right part
            current = current -> right;
        }
        cout<<endl;
    }

    void displayPreorder(){
        Stack <Node *> s;
        s.push(this -> root);
        Node *current = nullptr;

        while(!s.isEmpty()){
            current = s.gettop();
            cout<<current -> data<<" ";
            s.pop();

            //now push right child first and then left so that pop time, left comes first 
            if(current -> right != nullptr){
                s.push(current -> right);
            }
            if(current -> left != nullptr){
                s.push(current -> left);
            }
        }
        cout<<endl;
    }

    void displayPostorder(){
        Stack <Node *> s1,s2;
        s1.push(this -> root);
        Node *current = nullptr;

        while(!s1.isEmpty()){
            //pop the top element of first stack and push it into the second stack
            current = s1.gettop();
            s2.push(current);
            s1.pop();

            //now push left child first into s1 and then right so while pop it will go in postorder
            if(current -> left != nullptr){
                s1.push(current -> left);
            }
            if(current -> right != nullptr){
                s1.push(current -> right);
            }
        }

        //now all the nodes of the tree are traversed
        //now the stack s2 is in postorder reversed
        //so pop and display each element
        
        while(!s2.isEmpty()){
            current = s2.gettop();
            cout<<current -> data<<" ";
            s2.pop();
        }
        cout<<endl;
    }

    int height(Node* node){
        if(node == nullptr){
            return -1;
        }
        int left = height(node->left);
        int right = height(node->right);
        int count;

        if(left>=right){
            count = left + 1;
        }
        else{
            count = right + 1;
        }
        return count;
    }

    void swapNodes(Node *node){
        Node *current = node;
        Node *temp;

        if(current!=nullptr){
            if(current -> left || current -> right){
            temp = current -> left;
            current -> left = current -> right;
            current -> right = temp;
            }

            swapNodes(current -> left);
            swapNodes(current -> right);
        }

        else{
            return;
        }        
    }

    void nodesCount(){
        Stack <Node *> s;
        s.push(this -> root);
        Node *current = nullptr;
        int leafnode = 0;
        int internalnode = 0;

        while(!s.isEmpty()){
            current = s.gettop();            
            s.pop();

            if(current -> left == nullptr && current -> right == nullptr){
                leafnode++;
            }
            else{
                internalnode++;
            }

             
            if(current -> right != nullptr){
                s.push(current -> right);
            }
            if(current -> left != nullptr){
                s.push(current -> left);
            }
        }

        cout<<"No of leafnodes: "<<leafnode<<endl;
        cout<<"No of internal nodes: "<<internalnode<<endl;
    }

    BT operator=(BT &tree){
        BT b;
        Queue <Node *> q;
        q.push(tree.root);
        Node *current = nullptr;

        while(!q.isEmpty()){
            current = q.getfront();
            b.insert(current -> data);
            q.pop();

            if(current -> left != nullptr){
                q.push(current -> left);
            }
            if(current -> right != nullptr){
                q.push(current -> right);
            }
        }

        return b;
    }

    void deletenodes(){
        Stack <Node *> s1,s2;
        s1.push(this -> root);
        Node *current = nullptr;

        while(!s1.isEmpty()){
            current = s1.gettop();
            s2.push(current);
            s1.pop();

            if(current -> left != nullptr){
                s1.push(current -> left);
            }
            if(current -> right != nullptr){
                s1.push(current -> right);
            }
        }

        while(!s2.isEmpty()){
            delete s2.gettop();
            s2.pop();            
        }
    }
};

int main(){
    BT b;
    cout<<"Enter no of elements to insert in binary tree: ";
    int n , value;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter element: ";
        cin>>value;
        b.insert(value);
    }

    while(true){
        int choice;
        cout<<"Press 1 for displaying the binary tree, 2 for getting the height of the tree, 3 for mirroring the tree and displaying it, 4 for copying the tree into another tree and displaying it and 5 for counting the leaf and internal nodes of the tree...."<<endl;
        cin>>choice;

        if(choice == 1){
            cout<<"Here's the inorder display of the binary tree..."<<endl;
            b.displayInorder();
            cout<<"Here's the preorder display of the binary tree..."<<endl;
            b.displayPreorder();
            cout<<"Here's the postorder display of the binary tree..."<<endl;
            b.displayPostorder();
        }
        else if(choice == 2){
            Node *root = b.getroot();
            int h = b.height(root);
            cout<<"Height of the binary tree is "<<h<<endl;
        }
        else if(choice == 3){
            Node *root = b.getroot();
            b.swapNodes(root);
            cout<<"Here's the preorder display of the mirrored binary tree..."<<endl;
            b.displayPreorder();
        }
        else if(choice == 4){
            BT tree = b;
            cout<<"Here's the preorder traversal of the copied tree..."<<endl;
            tree.displayPreorder();
        }
        else if(choice == 5){
            b.nodesCount();
        }
        else{
            cout<<"Invalid option...."<<endl;
        }

        char c;
        cout<<"IF you to continue press y else press n to exit..";
        cin>>c;

        if(c == 'n'){
            break;
        }
    }
}