/*
Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data
value found in the tree, iv. Change a tree so that the roles of the left and right pointers
are swapped at every node, v. Search a value

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
using namespace std;

class Node{
    int value;
    Node *left;
    Node *right;

public:
    Node(int i){
        this -> value = i;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    friend class BST;
};

class BST{
    Node *root;

public:
    BST(int r){
        this -> root = new Node(r);
    }

    Node *getroot(){
        return this -> root;
    }

    void insert(int i){
        Node *current = root;
        Node *previous = nullptr;

        while(current!=nullptr){
            previous = current;
            if(i < current -> value){
                current = current -> left;
            }
            else{
                current = current -> right;
            }
        }

        if(i < previous -> value){
            Node *newnode = new Node(i);
            previous -> left = newnode;
        }
        else{
            Node *newnode = new Node(i);
            previous -> right = newnode;
        }
    }

    void displayInorder(Node *node){
        if(node == nullptr){
            return;
        }

        displayInorder(node -> left);
        cout<<node -> value<<" ";
        displayInorder(node -> right);
    }

    void displayPreorder(Node *node){
        if(node == nullptr){
            return;
        }

        cout<<node -> value<<" ";
        displayPreorder(node -> left);
        displayPreorder(node -> right);
    }

    void displayPostorder(Node *node){
        if(node == nullptr){
            return;
        }
        
        displayPostorder(node -> left);
        displayPostorder(node -> right);
        cout<<node -> value<<" ";
    }

    void search(int key){
        Node *current = root;
        int level = 0;
        while(current!=nullptr){
            if(key == current -> value){
                cout<<"Element found..."<<endl;
                cout<<"It is present at level "<<level<<endl;
            }

            else if(key < current -> value){
                current = current -> left;
                level++;
            }

            else{
                current = current -> right;
                level++;
            }
        }

        if(current==nullptr){
            cout<<"Element not found..."<<endl;
        }
    }

    void minElement(){
        Node *current = root;
        while(current -> left != nullptr){
            current = current -> left;
        }

        cout<<"Minimum element in the BST is "<<current -> value<<endl;
    }

    void maxElement(){
         Node *current = root;
        while(current -> right != nullptr){
            current = current -> right;
        }

        cout<<"Maximum element in the BST is "<<current -> value<<endl;
    }

    int longest_path(Node* root){
        if(root==NULL){
            return -1;
        }
        int left = longest_path(root->left);
        int right = longest_path(root->right);
        int count;
        if(left>=right){
            count = left+1;
        }
        else{
            count = right+1;
        }
        return count;
    }

    void swapNodes(Node *root){
        Node *current = root;
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
};

int main(){
    cout<<"Enter the root of the binary search tree: ";
    int r;
    cin>>r;
    BST b(r);
    cout<<"Enter no of elements to insert in the binary search tree: ";
    cin>>r;
    for(int i=0;i<r;i++){
        int data;
        cout<<"Enter element: ";
        cin>>data;
        b.insert(data);
    }

    while(true){
        int choice;
        cout<<"Press 1 for inorder display, 2 for preorder display, 3 for postorder display , 4 for searching an element in the tree, 5 for printing min and max elements of tree, 6 for printing the longest path and 7 for swapping the nodes of the tree i.e. mirroring the tree"<<endl;
        cin>>choice;
        if(choice==1){
            cout<<"Following is the inorder display of the BST.."<<endl;
            Node *root = b.getroot();
            b.displayInorder(root);
            cout<<endl;
        }

        else if(choice==2){
            cout<<"Following is the preorder display of the BST.."<<endl;
            Node *root = b.getroot();
            b.displayInorder(root);
            cout<<endl;
        }

        else if(choice==3){
            cout<<"Following is the postorder display of the BST.."<<endl;
            Node *root = b.getroot();
            b.displayInorder(root);
            cout<<endl;
        }

        else if(choice==4){
            int key;
            cout<<"Enter element to be found: ";
            cin>>key;
            b.search(key);
        }

        else if(choice==5){
            b.maxElement();
            b.minElement();
        }

        else if(choice==6){
            Node *root = b.getroot();
            int length = b.longest_path(root);
            cout<<"The longest path of the given BST has "<<length<<" nodes."<<endl;
        }

        else if(choice==7){
            Node *root = b.getroot();
            b.swapNodes(root);
            cout<<"Following is the preorder display of the binary tree after swapping.."<<endl;
            b.displayPreorder(root);
            break;
        }

        else{
            cout<<"Invalid option...."<<endl;
        }

        cout<<"If you wish to try again press y else press n: ";
        char c;
        cin>>c;

        if(c=='n'){
            break;
        }
    }
}


