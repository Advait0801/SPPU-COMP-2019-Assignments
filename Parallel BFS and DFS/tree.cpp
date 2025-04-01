#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree(int rootVal) {
        root = new TreeNode(rootVal);
    }

    void parallelBFS() {
        if (!root) return;

        queue<TreeNode*> q;
        q.push(root);
        cout<<"The parallel BFS of the given tree is..."<<endl;
    
        while(!q.empty()) {
            int levelSize = q.size();
            
            #pragma omp parallel for
            for(int i=0;i<levelSize;i++) {
                TreeNode* node = nullptr;
                
                #pragma omp critical
                {
                    if(!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout<<node -> val<<" ";
                    }
                }
    
                #pragma omp critical
                {
                    if(node -> left) q.push(node -> left);
                    if(node -> right) q.push(node -> right);
                }
            }
        }
        cout<<endl;
    }
    

    void parallelDFS() {
        if (!root) return;

        stack<TreeNode*> s;
        s.push(root);
        cout<<"The parallel DFS of the given tree is..."<<endl;

        #pragma omp parallel
        {
            while(!s.empty()) {
                TreeNode* node = nullptr;

                #pragma omp critical
                {
                    if(!s.empty()) {
                        node = s.top();
                        s.pop();
                        cout<<node -> val<<" ";
                    }
                }

                #pragma omp parallel sections
                {
                    #pragma omp section
                    {
                        if(node -> right) {
                            #pragma omp critical
                            s.push(node -> right);
                        }
                    }

                    #pragma omp section
                    {
                        if(node -> left) {
                            #pragma omp critical
                            s.push(node -> left);
                        }
                    }
                }
            }
        }
        cout<<endl;
    }
};

int main() {
    BinaryTree tree(1);
    tree.root->left = new TreeNode(2);
    tree.root->right = new TreeNode(3);
    tree.root->left->left = new TreeNode(4);
    tree.root->left->right = new TreeNode(5);
    tree.root->right->left = new TreeNode(6);
    tree.root->right->right = new TreeNode(7);

    tree.parallelBFS();
    tree.parallelDFS();

    return 0;
}

// Compile with: g++ -fopenmp -o tree tree.cpp
// Run with: ./tree
