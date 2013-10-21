typedef long long LL;
typedef pair<int, int> pii;

const double PI = 3.14159265358979323846264338327950288;
const int MAXN = 83;
const double EPS = 1e-8;

template <class T>
inline int Sign(T x) {
	if (x > EPS) return 1;
	if (x <-EPS) return -1;
	return 0;
}

inline double Sqrt(double x) {
	return x < 0 ? 0 : sqrt(x);
}

struct Point {
	double x, y, z;

	Point(): x(0.0), y(0.0), z(0.0) {
	}

	Point(double x, double y, double z): x(x), y(y), z(z) {
	}

	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		if (y != p.y) return y < p.y;
		return z < p.z;
	}

	bool operator == (const Point &p) const {
		return Sign(x - p.x) == 0 && Sign(y - p.y) == 0 && Sign(z - p.z) == 0;
	}

	Point operator + (const Point &p) const {
		return Point(x + p.x, y + p.y, z + p.z);
	}

	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y, z - p.z);
	}

	Point operator * (double k) const {
		return Point(x * k, y * k, z * k);
	}

	Point operator / (double k) const {
		return Point(x / k, y / k, z / k);
	}

	Point cross(const Point &p) const {
		return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}

	double dot(const Point &p) const {
		return x * p.x + y * p.y + z * p.z;
	}

	double norm() const {
		return dot(*this);
	}

	double length() const {
		return Sqrt(norm());
	}

	void input() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}

	void output() const {
		printf("%.6f %.6f %.6f\n", x, y, z);
	}
};

int mark[MAXN][MAXN];
Point info[MAXN];
int n, cnt;

double mix(const Point &a, const Point &b, const Point &c) {
	return a.dot(b.cross(c));
}

double area(int a, int b, int c) {
	return ((info[b] - info[a]).cross(info[c] - info[a])).length();
}

double volume(int a, int b, int c, int d) {
	return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}

struct Face {
	int a, b, c;

	Face(): a(0), b(0), c(0) {
	}

	Face(int a, int b, int c): a(a), b(b), c(c) {
	}

	int &operator[] (int k) {
		assert(0 <= k && k <= 2);
		if (k == 0) return a;
		if (k == 1) return b;
		return c;
	}
};

vector<Face> face;

inline void insert(int a, int b, int c) {
	face.push_back(Face(a, b, c));
}

void add(int v) {
	vector<Face> tmp;
	int a, b, c;
	++cnt;
	for (int i = 0; i < SIZE(face); ++i) {
		a = face[i][0];
		b = face[i][1];
		c = face[i][2];
		if (Sign(volume(v, a, b, c)) < 0)
			mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
		else
			tmp.push_back(face[i]);
	}
	face = tmp;
	for (int i = 0; i < SIZE(tmp); ++i) {
		a = face[i][0];
		b = face[i][1];
		c = face[i][2];
		if (mark[a][b] == cnt) insert(b, a, v);
		if (mark[b][c] == cnt) insert(c, b, v);
		if (mark[c][a] == cnt) insert(a, c, v);
	}
}

int Find() {
	for (int i = 2; i < n; ++i) {
		Point ndir = (info[0] - info[i]).cross(info[1] - info[i]);
		if (ndir == Point()) continue;
		swap(info[i], info[2]);
		for (int j = i + 1; j < n; ++j)
			if (Sign(volume(0, 1, 2, j)) != 0) {
				swap(info[j], info[3]);
				insert(0, 1, 2);
				insert(0, 2, 1);
				return 1;
			}
	}
	return 0;
}

double calcDist(const Point &p, int a, int b, int c) {
	return fabs(mix(info[a] - p, info[b] - p, info[c] - p) / area(a, b, c));
}

double findDist() {
	double totalWeight = 0;
	Point center(0, 0, 0);
	Point first = info[face[0][0]];
	Foru(i, 0, SIZE(face)) {
		Point p = (info[face[i][0]] + info[face[i][1]] + info[face[i][2]] + first) * 0.25;
		double weight = mix(info[face[i][0]] - first, info[face[i][1]] - first, info[face[i][2]] - first);
		totalWeight += weight;
		center = center + p * weight;
	}
	center = center / totalWeight;
	double res = 1e100;
	Foru(i, 0, SIZE(face))
		res = min(res, calcDist(center, face[i][0], face[i][1], face[i][2]));
	return res;
}

double solve() {
	memset(mark, 0, sizeof(mark));
	n = cnt = 0;
	face.clear();

	scanf("%d", &n);
	Foru(i, 0, n) info[i].input();
	sort(info, info + n);
	n = unique(info, info + n) - info;
	face.clear();
	random_shuffle(info, info + n);
	Find();
	memset(mark, 0, sizeof(mark));
	cnt = 0;
	Foru(i, 3, n) add(i);
	return findDist();
}

int main() {
	printf("%.5f\n", solve() + solve());
	return 0;
}
