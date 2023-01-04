#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int v,id;
	Node *child,*sibling;
}node[100010];

Node* meld(Node* x, Node* y){
	if (x->v == 0) return y; 
	if (y->v == 0) return x;
	if (x->v > y->v || (x->v == y->v && x > y)) 
		swap(x,y);  //注意在元素值相同时比编号，即把编号当第二关键字

	y->sibling = x->child; 
	x->child = y;
	return x;
}

Node* merges(Node* x){
	if (x->v == 0 || x->sibling->v == 0) 
		return x;

	Node *y = x->sibling;
	Node *c = y->sibling; 
	x->sibling = y->sibling = node;
	return meld(meld(x, y), merges(c));
}

Node* remove_top(Node* x){ 
	Node* t = merges(x->child);
	return t;
}

int fa[100010];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool Union(int fx,int fy)
{
	if (fx == fy) return true;
	fa[fy] = fx;
	return false;
}

Node* heap[100010];
bool used[100010];

int main(){
	int n, m;
	scanf("%d%d",&n ,&m);
	node[0].v = 0;

	for(int i = 1; i <= n; i ++) 
		fa[i] = i;

	for(int i = 1; i <= n; i ++){
		scanf("%d", &node[i].v);
		node[i].id = i;
		node[i].child = node[i].sibling = node;
		heap[i] = &node[i];
	}
	
	for(int i=1; i<=m; i++){
		int op,x;
		scanf("%d%d",&op,&x);

		if (op==1){
			int y;
			scanf("%d", &y);
			int fx=find(x), fy=find(y);
			if (used[x] || used[y] || Union(fx,fy))
				continue;
			heap[fx]=meld(heap[fx],heap[fy]);
		}

		else{
			int fx=find(x);

			if (used[x]){
				printf("-1\n");
				continue;
			}

			printf("%d\n", heap[fx]->v);

			used[heap[fx]->id] = true;
			heap[fx] = remove_top(heap[fx]);
		}
	}
	return 0;
}
