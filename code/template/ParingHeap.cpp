#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;

template<typename T>
class ParingHeap{
    struct Node{
        T val;
        Node *sibling, *child;

        Node(){}
        Node(T _val, Node *_sibling, Node *_child){
            val = _val, sibling = _sibling, child = _child;
        }
    };

    public:
    Node* root = nullptr;
    Node* meld(Node* x, Node* y){
        if(x == nullptr)
            return y;
        if(y == nullptr)
            return x;
        if(x->val > y->val)
            swap(x, y);
        y->sibling = x->child;
        x->child = y;
        return x;
    }

    void push(T x){
        Node* y = new Node;
        y->val = x;
        y->sibling = y->child = nullptr;
        root = meld(root, y);
    }

    void heap_merge(ParingHeap& b){
        root = meld(root, b.root);
    }

    Node* merge(Node* x){
        if(x == nullptr || x->sibling == nullptr)
            return x;
        Node* y = x->sibling;
        Node* nxt = y->sibling;
        x->sibling = y->sibling = nullptr;
        return meld(meld(x,y), merge(nxt));
    }

    void pop(){
        Node* x = root;
        if(x == nullptr)
            return ;
        root = merge(root->child);
        delete(x);
    }

    T top(){
        return root->val;
    }

    bool empty(){
        return root == nullptr;
    }
};

int main(){
    int n;
    ParingHeap<int> h;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x;
            scanf("%d", &x);
            h.push(x);
        }
        else if(op == 2){
            printf("%d\n", h.top());
        }
        else if(op == 3){
            h.pop();
        }
    }
    return 0;
}