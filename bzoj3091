#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
 
//#define lty
#define pb push_back
typedef long long LL;
using namespace std;
 
const int maxn=50100;
vector<int> g[maxn];
int n,m,x,y,t;
LL t1,t2,t3,D;
 
struct node{
       node *ch[2],*f;
       LL w,w1,w2,l,r,d,c;
       bool rev;
       void pushdown(){
            LL n=(l+r+1);
            if (d>0){
               c+=d;w+=d*(l+r+1);
               w1+=n*(n+1)/2*d;
               w2+=n*(n+1)*(2*n+1)/6*d;
               if (ch[0]) ch[0]->d+=d;
               if (ch[1]) ch[1]->d+=d;
               d=0;
            }
            LL tmp=w1;
            if (rev){
               w1=w*(n+1)-w1;w2=w*(n+1)*(n+1)-2*tmp*(n+1)+w2;
               swap(l,r);swap(ch[0],ch[1]);
               if (ch[0]) ch[0]->rev=!ch[0]->rev;
               if (ch[1]) ch[1]->rev=!ch[1]->rev;
               rev=false;
            }
       }
       void update(){
            w=c;w1=0;w2=0;
            if (ch[0]){
               ch[0]->pushdown();
               l=ch[0]->l+ch[0]->r+1;w+=ch[0]->w;
               w1=ch[0]->w1;w2=ch[0]->w2;
            } else l=0;
            w1+=(l+1)*c;
            w2+=(l+1)*(l+1)*c;
            if (ch[1]){
               ch[1]->pushdown();
               r=ch[1]->l+ch[1]->r+1;w+=ch[1]->w;
               w1+=(l+1)*ch[1]->w+ch[1]->w1;
               w2+=2*ch[1]->w1*(l+1)+(l+1)*(l+1)*ch[1]->w+ch[1]->w2;
            } else r=0;
       }
}*c[maxn],*u,*ans;
 
 
node* New_node(int x){
      node*t=new node();
      t->ch[0]=t->ch[1]=t->f=NULL;
      t->w=t->w1=t->w2=t->c=x;
      t->d=t->l=t->r=0;
      t->rev=false;
      return t;
}
 
void dfs(int u){
     for (int v=0;v<g[u].size();v++)
         if (c[g[u][v]]!=c[u]->f) c[g[u][v]]->f=c[u],dfs(g[u][v]);
}
 
void Rotate(node*p,int w){
     node*q=p->f,*y=q->f;p->f=y;
     if (y&&(y->ch[0]==q||y->ch[1]==q))
        if (y->ch[0]==q) y->ch[0]=p; else y->ch[1]=p;
     y=p->ch[1-w];if (y)y->f=q;q->ch[w]=y;q->f=p;q->update();p->ch[1-w]=q;
}
 
void Splay(node*p){
     while (p->f&&(p->f->ch[0]==p||p->f->ch[1]==p)){
           node*q=p->f,*y=q->f;
           if (y&&(y->ch[0]==q||y->ch[1]==q)){
              y->pushdown();q->pushdown();p->pushdown();
              if (y->ch[0]==q&&q->ch[0]==p) Rotate(q,0); else
                 if (y->ch[1]==q&&q->ch[1]==p) Rotate(q,1); else
                    if (q->ch[0]==p) Rotate(p,0); else Rotate(p,1);
           } else q->pushdown(),p->pushdown();
           if (p->f->ch[0]==p) Rotate(p,0); else Rotate(p,1);
     }
     p->update();
}
 
node* Expose(node*p){
      node*q;
      for (q=NULL;p;p=p->f){
          Splay(p);
          p->ch[1]=q;
          (q=p)->update();
      }
      return q;
}
 
LL gcd(LL x,LL y){
   if (y==0) return x; else return gcd(y,x%y);
}
 
void combine(node*u,node*v){
     LL n=0,w1=0,w2=0,uw,uw1,uw2;
     uw=uw1=uw2=u->c;t2=0;t1=0;
     if (u->ch[1]){
        uw+=u->ch[1]->w;uw1+=u->ch[1]->w1+u->ch[1]->w;
        uw2+=u->ch[1]->w2+2*u->ch[1]->w1+u->ch[1]->w;
     }
     if (v){
        n=v->l+v->r+1,w1=v->w*(n+1)-v->w1,w2=v->w*(n+1)*(n+1)-2*v->w1*(n+1)+v->w2;t2=v->l+v->r+1;
     }
     w1+=uw*t2+uw1;w2+=t2*t2*uw+t2*uw1*2+uw2;t2+=u->r+1;
     t1=(t2+1)*w1-w2;t2=t2*(t2+1)/2;
}
 
int main(){
#ifdef lty
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);ans=new node();
    for (int i=1;i<=n;i++) scanf("%d",&x),c[i]=New_node(x);
    for (int i=0;i<n-1;i++) scanf("%d%d",&x,&y),g[x].pb(y),g[y].pb(x);dfs(1);
    for (;m;m--){
        scanf("%d",&t);
        switch (t){
               case 1:scanf("%d%d",&x,&y);Expose(c[x]);u=Expose(c[y]);
                      if (x==y) break;
                      if (u==c[x]||u==c[y]){
                         Splay(c[x]);
                         if (u==c[x]&&c[x]->r==1) c[y]->f=NULL,c[x]->ch[1]=NULL,c[x]->update();
                         if (u==c[y]&&c[x]->l==0) c[x]->f=NULL;
                      }
                      break;
               case 2:scanf("%d%d",&x,&y);Expose(c[x]);u=Expose(c[y]);Splay(c[x]);Splay(c[y]);
                      if (x==y) break;
                      if (!c[x]->f&&!c[y]->f) c[x]->rev=!c[x]->rev,c[x]->f=c[y],c[x]->pushdown();
                      break;
               case 3:scanf("%d%d%d",&x,&y,&D);Expose(c[x]);u=Expose(c[y]);Splay(c[x]);Splay(c[y]);
                      if (!c[x]->f&&!c[y]->f&&x!=y) break;
                      Splay(u);u->c+=D;
                      if (u->ch[1]) u->ch[1]->d+=D,u->ch[1]->pushdown();
                      u->update();if (u==c[x]) break;
                      Splay(c[x]);c[x]->d+=D;c[x]->pushdown();
                      break;
               case 4:scanf("%d%d",&x,&y);Expose(c[x]);u=Expose(c[y]);Splay(c[x]);Splay(c[y]);
                      if (!c[x]->f&&!c[y]->f&&x!=y) {puts("-1");break;}Splay(u);
                      if (u!=c[x]) Splay(c[x]),combine(u,c[x]); else combine(u,NULL);
                      t3=gcd(t1,t2);t1/=t3;t2/=t3;printf("%lld/%lld\n",t1,t2);
                      break;
        }
    }
    return 0;
}
