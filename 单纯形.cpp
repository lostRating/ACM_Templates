#include <cstdio>
#include <memory.h>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

const int MAXSIZE = 2000;
const int NN=1000;
const double eps = 1e-8;
const int oo = 19890709;

int n, m;
double A[MAXSIZE+1][MAXSIZE+1];
double b[MAXSIZE+1], c[MAXSIZE+1];
	double tA[MAXSIZE+1][MAXSIZE+1];
	double tb[MAXSIZE+1], tc[MAXSIZE+1];
	int N[MAXSIZE+1+1], B[MAXSIZE+1+1];
	double v;
string data[MAXSIZE+1];

struct standard
{
	void First(string mode)
	{
		if (mode == "minimize")
			for(int i=1; i<=m+2; i++)
				c[i] *= -1;
	}
	void Second()
	{
		for (int i=1; i<=m; i++) if (data[i] != "<=")
		{
			if (data[i] == "=")
			{
				data[i] = "<=";
				data[++m] = ">=";
				for(int j=1; j<=n; j++)
					A[m][j] = A[i][j];
				b[m] = b[i];
			}
			else
			{
				data[i] = "<=";
				for(int j=1; j<=n; j++)
					A[i][j] *= -1;
				b[i] *= -1;
			}
		}
	}
};


class LinearProgramming
{

	void pivot(int l, int e)
	{
		tb[e] = b[l]/A[l][e];
		tA[e][l] = 1/A[l][e];
		for(int i=1; i<=N[0]; i++)
			if (N[i] != e)
				tA[e][N[i]] = A[l][N[i]]/A[l][e];

		for(int i=1; i<=B[0]; i++)
		{
			tb[B[i]] = b[B[i]]-A[B[i]][e]*tb[e];
			tA[B[i]][l] = -A[B[i]][e]*tA[e][l];
			for(int j=1; j<=N[0]; j++)
				if (N[j] != e)
					tA[B[i]][N[j]] = A[B[i]][N[j]]-tA[e][N[j]]*A[B[i]][e];
		}

		v += tb[e]*c[e];
		tc[l] = -tA[e][l]*c[e];
		for(int i=1; i<=N[0]; i++)
			if (N[i] != e)
				tc[N[i]] = c[N[i]]-tA[e][N[i]]*c[e];

		for(int i=1; i<=N[0]; i++)
			if (N[i] == e) N[i] = l;
		for(int i=1; i<=B[0]; i++)
			if (B[i] == l) B[i] = e;
		for(int i=1; i<=B[0]; i++)
		{
			for(int j=1; j<=N[0]; j++)
				A[B[i]][N[j]] = tA[B[i]][N[j]];
			b[B[i]] = tb[B[i]];
		}
		for(int i=1; i<=N[0]; i++)
			c[N[i]] = tc[N[i]];
	}

	bool opt()//false stands for unbounded
	{
		while (true)
		{
			int e = MAXSIZE+1;
			for(int i=1; i<=N[0]; i++)
				if (c[N[i]] > eps && N[i] < e) e = N[i];
			if (e == MAXSIZE+1) break;
			double delta = oo;
			int l = MAXSIZE+1;
			for(int i=1; i<=B[0]; i++)
				if (A[B[i]][e] > eps)
				{
					double temp = b[B[i]]/A[B[i]][e];
					if (delta == oo || temp < delta || temp == delta && B[i] < l)
					{
						delta = temp;
						l = B[i];
					}
				}
			if (l == MAXSIZE+1) return false;
			pivot(l, e);
		}
		return true;
	}

	void delete0()
	{
		int p;
		for(p=1; p<=B[0]; p++)
			if (B[p] == 0) break;
		if (p <= B[0])
		{
			int i;
			for(i=1; i<=N[0]; i++)
				if (A[0][N[i]] > eps || A[0][N[i]] < -eps) break;
			pivot(0, N[i]);
		}
		for(p=1; p<=N[0]; p++)
			if (N[p] == 0) break;
		for(int i=p; i<N[0]; i++)
			N[i] = N[i+1];
		N[0]--;
	}

	bool initialize()
	{
		N[0] = B[0] = 0;
		for(int i=1; i<=n; i++)
			N[++N[0]] = i;
		for(int i=1; i<=m; i++)
			B[++B[0]] = n+i;
		v = 0;

		int l = B[1];
		for(int i=2; i<=B[0]; i++)
			if (b[B[i]] < b[l])
				l = B[i];
		if (b[l] >= 0) return true;

		double origC[MAXSIZE+1];
		memcpy(origC, c, sizeof(double)*(n+m+1));
		N[++N[0]] = 0;
		for(int i=1; i<=B[0]; i++)
			A[B[i]][0] = -1;
		memset(c, 0, sizeof(double)*(n+m+1));
		c[0] = -1;
		pivot(l, 0);
		opt();
		if (v < -eps) return false;
		delete0();

		memcpy(c, origC, sizeof(double)*(n+m+1));
		bool inB[MAXSIZE+1];
		memset(inB, false, sizeof(bool)*(n+m+1));
		for(int i=1; i<=B[0]; i++)
			inB[B[i]] = true;
		for(int i=1; i<=n+m; i++)
			if (inB[i] && c[i] != 0)
			{
				v += c[i]*b[i];
				for(int j=1; j<=N[0]; j++)
					c[N[j]] -= A[i][N[j]]*c[i];
				c[i] = 0;
			}
		return true;
	}

	public: void simplex()
	{
		if (!initialize())
		{
			printf("-1\n");
			return;
		}
		if (!opt())
		{
			printf("Unbounded\n");
			return;
		}
		else printf("%.5lf\n", b[n]-b[n-1]); //v
		//
		/*
		bool inN[MAXSIZE+1];
		memset(inN, false, sizeof(bool)*(n+m+1));
		for(int i=1; i<=N[0]; i++)
			inN[N[i]] = true;
		for(int i=1; i<=n; i++)
			if (inN[i]) printf("x%d = %lf\n", i, 0.0);
			else printf("x%d = %lf\n", i, b[i]);*/
	}
};

int main()
{
	freopen("n.in", "r", stdin);
	freopen("n.out","w",stdout);
	int task;
	cin>>task;
	for (int now=1;now<=task;now++)
	{
		standard a;
		cin>>n>>m;
		for (int i=0;i<=NN;i++) c[i]=0;
		c[m+1]=-1;
		c[m+2]=1;
		a.First("minimize");
		for (int i=0;i<=n+m*4;i++)
		{
			b[i]=0;
			for (int j=0;j<=m+2;j++) A[i][j]=0;
		}
		for (int i=0;i<=NN;i++) data[i]="=";
		for (int i=1;i<=m;i++)
		{
			int x,y,p,q;
			cin>>x>>y>>p>>q;
			A[x][i]=1;
			A[y][i]=-1;
			A[n+i][i]=1; data[n+i]=">="; b[n+i]=p;
			A[n+m+i][i]=1; data[n+m+i]="<="; b[n+m+i]=q;
			A[n+m*2+i][i]=1; A[n+m*2+i][m+1]=-1; data[n+m*2+i]=">=";
			A[n+m*3+i][i]=1; A[n+m*3+i][m+2]=-1; data[n+m*3+i]="<=";
		}
		int t1=m+2,t2=n+m*4;

		n=t1; m=t2;
		a.Second();
		for (int i=m;i>=1;i--)
		{
			for (int j=1;j<=n;j++)
				A[n+i][j]=A[i][j];
			b[n+i]=b[i];
		}
		printf("Case %d: ",now);
//		v=0;
//		for (int i=0;i<=NN;i++)
//			for (int j=0;j<=NN;j++)
//				tA[i][j]=tb[i]=tc[i]=N[i]=B[i]=0;
		LinearProgramming test;
		test.simplex();
	}
}
