/// {{{ Author: Wang, Yen-Jen
#include <bits/stdc++.h>
 
using namespace std;
 
// type
typedef long long ll;
typedef pair<int,int> pii;
 
// macro
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin() , (x).end()
#define PB push_back
#define MP make_pair
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = (a); i <= int(b); i++)
#define PER(i , n) for(int i = (n) - 1; i >= 0; i--)
#define PER1(i , a , b) for(int i = (a); i >= int(b); i--)
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset(x , (v) , sizeof(x))
 
// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;
 
// random function
inline int RAND() {
    static int x = 880301;
    return x = (x * 0xdefacedll + 1ll) % 0x7fffffffll;
}
/// }}}
 
const double EPS = 1e-10;
 
struct Point {
    double x , y;
 
    Point(double _x = 0.0 , double _y = 0.0) : x(_x) , y(_y) {}
 
    bool operator < (const Point &rhs) const {
        if(x != rhs.x) return x < rhs.x;
        else return y < rhs.y;
    }
};
 
typedef Point Vector;
 
inline Point operator + (Point p , Vector v) {
    return Point(p.x + v.x , p.y + v.y);
}
 
inline Vector operator - (Point a , Point b) {
    return Vector(a.x - b.x , a.y - b.y);
}
 
inline Vector operator * (Vector v , double p) {
    return Vector(v.x * p , v.y * p);
}
 
inline Vector operator / (Vector v , double p) {
    return Vector(v.x / p , v.y / p);
}
 
inline double cross(Vector a , Vector b) {
    return a.x * b.y - a.y * b.x;
}
 
inline double dot(Vector a , Vector b) {
    return a.x * b.x + a.y * b.y;
}
 
inline int dcmp(double x) {
    return fabs(x) < EPS ? 0 : x > 0 ? 1 : -1;
}
 
struct Line {
    Point p;
    Vector v;
    double ang;
 
    Line() {}
    Line(Point _p , Vector _v) : p(_p) , v(_v) {
        ang = atan2(_v.y , _v.x);
    }
 
    bool operator < (const Line &rhs) const {
        return ang < rhs.ang;
    }
};
 
inline bool on_left(Line l , Point p) {
    return cross(l.v , p - l.p) > 0;
}
 
inline Point get_line_intersection(Line a , Line b) {
    Vector u = a.p - b.p;
    double t = cross(b.v , u) / cross(a.v , b.v);
    return a.p + a.v * t;
}
 
vector<Point> half_plane_intersection(vector<Line> ls) {
    int n = SZ(ls);
    sort(ALL(ls));
    int f , r;
    vector<Point> p(n) , ans;
    vector<Line> q(n);
    q[f = r = 0] = ls[0];
    REP1(i , 1 , n - 1) {
        while(f < r && !on_left(ls[i] , p[r - 1])) r--;
        while(f < r && !on_left(ls[i] , p[f])) f++;
        q[++r] = ls[i];
        if(dcmp(cross(q[r].v , q[r - 1].v)) == 0) {
            r--;
            if(on_left(q[r] , ls[i].p)) q[r] = ls[i];
        }
        if(f < r) p[r - 1] = get_line_intersection(q[r - 1] , q[r]);
    }
    while(f < r && !on_left(q[f] , p[r - 1])) r--;
    if(r - f <= 1) return ans;
    p[r] = get_line_intersection(q[r] , q[f]);
    REP1(i , f , r) ans.PB(p[i]);
    return ans;
}