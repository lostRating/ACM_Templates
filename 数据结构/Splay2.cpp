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
#include <iomanip>

using namespace std;

typedef long long int64;
typedef long long LL;
typedef long double real;
typedef long double LD;

#define mp make_pair
#define PII pair<int, int>
#define pb push_back
#define sz(X) ((int)((X).size()))

const double eps = 1e-8;
const double PI = acos(0.) * 2;
const int lim = 1000000000;
const int inf = ~0U >> 1;

template<class T> T abs(T x){return x < 0 ? -x : x;}

int tt[30];

struct Node{
	int size, t, w, l, r, s;
	Node *ch[2], *f;
	Node (int _size, int _t):size(_size), s(_size), t(_t), w(_t){
		ch[0] = ch[1] = f = NULL;
	}
	void update(){
		t = w;
		l = r = 0;
		if (ch[0]){
			t |= ch[0]->t;
			l = ch[0]->size;
		}
		if (ch[1]){
			t |= ch[1]->t;
			r = ch[1]->size;
		}
		size = l + r + s;
	}
}*root;

void Rotate(Node *p, int w){
	Node *q = p->f, *y = q->f;
	p->f = y;
	if (y)
		if (y->ch[0] == q) y->ch[0] = p; else y->ch[1] = p;
	y = p->ch[1 - w];
	if (y) y->f = q;
	q->ch[w] = y;
	q->f = p;
	p->ch[1 - w] = q;
	q->update();
}

void Splay(Node *p, Node *t){
	while (p->f != t){
		Node *q = p->f, *y = q->f;
		if (y != t){
			if (y->ch[0] == q && q->ch[0] == p) Rotate(q, 0); else 
				if (y->ch[1] == q && q->ch[1] == p) Rotate(q, 1); else 
					if (q->ch[0] == p) Rotate(p, 0); else Rotate(p, 1);
		}
		if (p->f->ch[0] == p) Rotate(p, 0); else Rotate(p, 1);
	}
	p->update();
	if (!t) root = p;
}

// find xth in which node
Node* rk(int &x){
	Node *u = root;
	while (true){
		if (u->l >= x){
			u = u->ch[0];
			continue;
		} 
		x -= u->l;
		if (x <= u->s) return u;
		x -= u->s;
		u = u->ch[1];
	}
}


void Delete(Node *u){
	Splay(u, NULL);
	if (!u->ch[0]){
		if (!u->ch[1]){
			root = NULL;
			return;
		}
		root = u->ch[1];
		root->f = NULL;
	} else {
		Node *v = u->ch[0];
		while (v->ch[1]) v = v->ch[1];
		Splay(v, root);
		v->ch[1] = u->ch[1];
		u->ch[1]->f = v;
		v->f = NULL;
		v->update();
		root = v;
	}
}


// 插在x位置后面
void Insert(Node *t, int x){
	if (!root){
		root = t;
		return;
	}
	Node *u = root;
	while (true){
		if (u->l + u->s > x){
			if (u->ch[0]) u = u->ch[0]; else {
				u->ch[0] = t;
				t->f = u;
				break;
			}
			continue;
		}
		x -= u->l + u->s;
		if (u->ch[1]) u = u->ch[1]; else {
			u->ch[1] = t;
			t->f = u;
			break;
		}
	}
	Splay(t, NULL);
}

// split [l, r] into [l, x - 1] & [x, r]
void Split(int x){
	int t = x;
	Node *u = rk(t);
	if (t == 1) return; else {
		Node *t1 = new Node(t - 1, u->w);
		Node *t2 = new Node(u->s - t + 1, u->w);
		Delete(u);
		Insert(t2, x - t);
		Insert(t1, x - t);
	}
}

int main(){
	tt[0] = 1;
	for (int i = 1; i < 26; ++i)
		tt[i] = tt[i - 1] << 1;

	int Q;
	scanf("%d", &Q);
	root = new Node(2, 0);
	for (; Q; --Q){
		char ch;
		scanf(" %c", &ch);
		int x, y;
		scanf("%d%d", &x, &y);
		if (ch == '+'){
			char cc;
			scanf(" %c", &cc);
			Node *t = new Node(y, tt[cc - 'a']);
			Split(++x);
			Insert(t, x - 1);
		} else if (ch == '-'){
			y = x + y - 1;
			Split(y + 2);
			Split(x + 1);
			int t = x;
			Node *u = rk(t);
			t = y + 2;
			Node *v = rk(t);
			Splay(v, NULL);
			Splay(u, root);
			root->ch[0]->ch[1] = NULL;
			root->ch[0]->update();
			root->update();
		} else {
			Split(y + 2);
			Split(x + 1);
			int t = x;
			Node *u = rk(t);
			t = y + 2;
			Node *v = rk(t);
			Splay(v, NULL);
			Splay(u, root);

			t = root->ch[0]->ch[1]->t;
			int ans = 0;
			while (t){
				if (t & 1) ++ans;
				t >>= 1;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

