const int INF = 0x3f3f3f3f;
const int MAX_N = 200000 + 10;
struct Node {
    Node *par , *ch[2] , *mx;
    int id , sz , rev_tag , val;
    Node(int _id = 0 , int _val = 0) : par(0) , id(_id) , sz(1) , rev_tag(0) , mx(this) , val(_val) {
        MS(ch , 0);
    }
};
struct Edge {
    int x , y , a , b;
    Edge() {}
    Edge(int _x , int _y , int _a , int _b) : x(_x) , y(_y) , a(_a) , b(_b) {}
    bool operator < (const Edge &rhs) const {
        return a < rhs.a;
    }
};
int N , M;
Node *tr[MAX_N];
vector<Edge> edges;
inline void rev(Node *o) {
    swap(o->ch[0] , o->ch[1]);
    o->rev_tag ^= 1;
}
inline int sz(Node *o) {
    return o ? o->sz : 0;
}
inline void push(Node *o) {
    if(o->rev_tag) {
        REP(i , 2) if(o->ch[i]) rev(o->ch[i]);
        o->rev_tag ^= 1;
    }
}
inline void pull(Node *o) {
    o->sz = sz(o->ch[0]) + 1 + sz(o->ch[1]);
    o->mx = o;
    REP(i , 2) if(o->ch[i] && o->ch[i]->mx->val > o->mx->val) o->mx = o->ch[i]->mx;
}
inline int get_ch_id(Node *p , Node *o) {
    REP(i , 2) if(p->ch[i] == o) return i;
    return -1;
}
inline void rotate(Node *o , int d) {
    push(o);
    push(o->ch[d]);
    Node *u = o;
    o = o->ch[d];
    Node *p = u->par;
    int t;
    if(p && (t = get_ch_id(p , u)) != -1) p->ch[t] = o;
    o->par = p;
    u->par = o;
    if(o->ch[d^1]) o->ch[d^1]->par = u;
    u->ch[d] = o->ch[d^1];
    o->ch[d^1] = u;
    pull(u);
    pull(o);
}
inline void rotate(Node *o) {
    if(sz(o->ch[0]) > sz(o->ch[1])) rotate(o , 0);
    else if(sz(o->ch[0]) < sz(o->ch[1])) rotate(o , 1);
}
inline void all_push(Node *o) {
    if(o->par && get_ch_id(o->par , o) != -1) all_push(o->par);
    push(o);
}
inline void splay(Node *o) {
    all_push(o);
    Node *p;
    for(int d; (p = o->par) && (d = get_ch_id(p , o)) != -1;) {
        rotate(p , d);
        rotate(p);
    }
}
inline Node* access(Node *o) {
    Node *last = 0;
    while(o) {
        splay(o);
        o->ch[1] = last;
        pull(o);
        last = o;
        o = o->par;
    }
    return last;
}
inline void make_root(Node *o) {
    rev(access(o));
    splay(o);
}
inline void link(Node *a , Node *b) {
    make_root(b);
    b->par = a;
}
inline void cut(Node *a , Node *b) {
    make_root(a);
    access(b);
    splay(b);
    b->ch[0] = 0;
    a->par = 0;
    pull(b);
}
inline Node* find_root(Node *o) {
    o = access(o);
    while(o->ch[0]) o = o->ch[0];
    splay(o);
    return o;
}
inline void add_edge(int i , int x , int y , int v) {
    tr[N + i] = new Node(N + i , v);
    if(find_root(tr[x]) == find_root(tr[y])) {
        make_root(tr[x]);
        access(tr[y]);
        splay(tr[x]);
        int id = tr[x]->mx->id - N;
        if(edges[id].b > v) {
            cut(tr[edges[id].x] , tr[N + id]);
            cut(tr[edges[id].y] , tr[N + id]);
            link(tr[x] , tr[N + i]);
            link(tr[y] , tr[N + i]);
        }
    }
    else {
        link(tr[x] , tr[N + i]);
        link(tr[y] , tr[N + i]);
    }
}
int main() {
    RI(N , M);
    edges.clear();
    REP(i , N) tr[i] = new Node(i);
    REP(i , M) {
        int x , y , a , b;
        RI(x , y , a , b);
        x-- , y--;
        if(x == y) continue;
        edges.PB(Edge(x , y , a , b));
    }
    sort(ALL(edges));
    M = SZ(edges);
    int ans = INF;
    for(int a = 1 , ptr = 0; a <= 50000; a++) {
        while(ptr < SZ(edges) && edges[ptr].a <= a) {
            add_edge(ptr , edges[ptr].x , edges[ptr].y , edges[ptr].b);
            ptr++;
        }
        if(find_root(tr[0]) == find_root(tr[N - 1])) {
            make_root(tr[0]);
            access(tr[N - 1]);
            splay(tr[0]);
            ans = min(ans , a + tr[0]->mx->val);
        }
    }
    PL(ans == INF ? -1 : ans);
    return 0;
}
