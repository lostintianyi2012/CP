#include <iostream>
#include <stdio.h>
#include <algorithm>
#define nptr nullptr
using namespace std;

template<typename T>
class PairingHeap{
    struct Node{
        T val;
        Node *sib, *son;
        Node(){}
        Node(T _val, Node* _sib, Node* _son){
            val = _val, sib = _sib, son = _son;
        }
    };
    int _size;
    public:
    Node* root = nptr;
    Node* meld(Node* x, Node* y){
        if(x == nptr)
            return y;
        if(y == nptr)
            return x;
        if(x->val > y->val)
            swap(x, y);
        y->sib = x->son;
        x->son = y;
        return x;
    }

    Node* merge(Node* x){
        if(x == nptr || x->sib == nptr)
            return x;
        Node* y = x->sib;
        Node* c = y->sib;
        x->sib = y->sib = nptr;
        return meld(meld(x, y), merge(c));
    }

    void heap_merge(PairingHeap y){
        _size += y._size;
        meld(root, y.root);
    }

    void push(T x){
        Node* y = new Node{x, nptr, nptr};
        root = meld(root, y);
        _size++;
    }

    void pop(){
        Node* x = root;
        if(x == nptr)
            return ;
        root = merge(x->son);
        delete(x);
        _size--;
    }

    T top(){
        return root->val;
    }

    int size(){
        return _size;
    }
};

int main(){
    int n;
    PairingHeap<int> h;
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