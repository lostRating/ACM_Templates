const int maxn = 20000;
const int infinite = 1;

struct point{
	double x, y;
	point() {}
	point(double a , double b): x(a) , y(b) {}

	void input(){
		scanf("%lf%lf", &x, &y);
	}
	point rotate()
	{
		return point( y , -x );
	}
	point operator + ( const point &p ) const {
		return point( x+p.x , y+p.y );
	}
	point operator - ( const point &p ) const {
		return point( x-p.x , y-p.y ) ;
	}
	point operator / ( const double p ) const {
		return point( x/p , y/p ) ;
	}
}sol[maxn], tmp[maxn] , p [maxn] ;

struct Tline{
	point a, b;
}line[maxn];

int n, m;

int cmp(double x){
	if (abs(x) < eps) return 0;
	if (x > eps) return 1;
	return -1;
}

double area(point a, point b, point c){
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x) ;
}

void rebuild(point a, point b){
	int i, t;
	double k1, k2;
	sol[m] = sol[0];
	t = 0;
	for (int i = 1; i <= m; ++i){
		k1 = area(a, b, sol[i]);
		k2 = area(a, b, sol[i - 1]);
		if (cmp(k1) * cmp(k2) < 0){
			tmp[t].x = (sol[i].x * k2 - sol[i - 1].x * k1) / (k2 - k1);
			tmp[t].y = (sol[i].y * k2 - sol[i - 1].y * k1) / (k2 - k1);
			++t;
		}
		if (cmp(area(a, b, sol[i])) >= 0){
			tmp[t] = sol[i];
			++t;
		}
	}
	m = t;
	for (int i = 0; i < m; ++i) sol[i] = tmp[i];
}

void work(){
	int i, j, k;
	double ans;
	point o;
	sol[0].x = 0;			sol[0].y = 0;
	sol[1].x = 1;	sol[1].y = 0;
	sol[2].x = 1;	sol[2].y = 1;
	sol[3].x = 0;			sol[3].y = 1;
	m = 4;
	for (int i = 0; i < n; ++i) rebuild(line[i].a, line[i].b);
	//if (m > 0) printf("1\n"); else printf("0\n");
}
