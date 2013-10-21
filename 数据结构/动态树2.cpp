#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>

using namespace std;

typedef long long LL;
typedef long double real;

#define mp make_pair
#define pb push_back
#define sz(X) ((int)((X).size()))

struct Node{
	LL maxl, maxr, maxsum, sum, w, size, flag;
	bool ff;
	Node *ch[2], *f;
	void pushdown(){
	}
	void update(){
	}
}*c[maxn];

Node* New_Node(LL Value){
}

void Rotate(Node *p, int w){
	Node *q = p->f, *y = q->f;
	p->f = y;
	if (y && (y->ch[0] == q || y->ch[1] == q))
		if (y->ch[0] == q) y->ch[0] = p; else y->ch[1] = p;
	y = p->ch[1 - w];
	if (y) y->f = q;
	q->ch[w] = y;
	q->f = p;
	q->update();
	p->ch[1 - w] = q;
}

void Splay(Node *p){
	p->pushdown();
	while (p->f && (p->f->ch[0] == p || p->f->ch[1] == p)){
		Node *q = p->f, *y = q->f;
		if (y && (y->ch[0] == q || y->ch[1] == q)){
			y->pushdown();
			q->pushdown();
			p->pushdown();
			if (y->ch[0] == q && q->ch[0] == p) Rotate(q, 0); else 
				if (y->ch[1] == q && q->ch[1] == p) Rotate(q, 1); else 
					if (q->ch[0] == p) Rotate(p, 0); else Rotate(p, 1);
		} else q->pushdown(), p->pushdown();
		if (p->f->ch[0] == p) Rotate(p, 0); else Rotate(p, 1);
	}
	p->update();
}

Node* Expose(Node* p){
	Node *q;
	for (q = NULL; p; p = p->f){
		Splay(p);
		p->ch[1] = q;
		(q = p)->update();
	}
	return q;
}

int main(){
	return 0;
}

