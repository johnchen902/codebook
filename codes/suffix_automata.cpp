// BZOJ 3998
const int MAX_N = 500000 + 10;
struct Node {
    static Node mem[MAX_N<<1] , *pmem;
    Node *ch[26] , *fail;
    int mx , val;
    ll dp;
    int tag , deg;
    Node() : mx(0) , fail(0) , dp(0) , val(0) , tag(0) , deg(0) {
        MS(ch , 0);
    }
} Node::mem[MAX_N<<1] , *Node::pmem = Node::mem , *root , *last;
int T , N;
char s[MAX_N];
inline void init() {
    last = root = new (Node::pmem++)Node();
}
inline int idx(char c) {
    return c - 'a';
}
inline void insert(char c) {
    c = idx(c);
    Node *p = last;
    Node *np = new (Node::pmem++)Node();
    np->mx = p->mx + 1;
    np->val = 1;
    while(p && !p->ch[c]) {
        p->ch[c] = np;
        np->deg++;
        p = p->fail;
    }
    if(!p) np->fail = root;
    else {
        Node *q = p->ch[c];
        if(q->mx == p->mx + 1) np->fail = q;
        else {
            Node *nq = new (Node::pmem++)Node();
            nq->mx = p->mx + 1;
            nq->val = 0;
            memcpy(nq->ch , q->ch , sizeof(q->ch));
            REP(i , 26) {
                if(nq->ch[i]) nq->ch[i]->deg++;
            }
            nq->fail = q->fail;
            q->fail = np->fail = nq;
            while(p && p->ch[c] == q) {
                p->ch[c] = nq;
                q->deg--;
                nq->deg++;
                p = p->fail;
            }
        }
    }
    last = np;
}
inline void bfs() {
    static Node* que[MAX_N<<1];
    int l = 0 , r = 0;
    que[r++] = root;
    root->tag = 2;
    vector<Node*> vec;
    while(l < r) {
        Node *u = que[l++];
        REP(i , 26) {
            if(u->ch[i]) {
                if(--u->ch[i]->deg == 0 && u->ch[i]->tag != 1) {
                    u->ch[i]->tag = 1;
                    que[r++] = u->ch[i];
                    vec.PB(u->ch[i]);
                }
            }
        }
    }
    for(int i = SZ(vec) - 1; i >= 0; i--) {
        Node *u = vec[i];
        if(T) {
            if(u->fail) u->fail->val += u->val;
        }
        else u->val = 1;
    }
    root->val = 0;
    for(int i = SZ(vec) - 1; i >= 0; i--) {
        Node *u = vec[i];
        u->dp = u->val;
        REP(j , 26) {
            if(u->ch[j]) u->dp += u->ch[j]->dp;
        }
    }
    REP(i , 26) {
        if(root->ch[i]) root->dp += root->ch[i]->dp;
    }
}
inline void solve(int k) {
    Node *p = root;
    if(k > p->dp || k <= 0) {
        puts("-1");
        return;
    }
    while(k > 0) {
        int flag = 0;
        REP(i , 26) {
            if(!p->ch[i]) continue;
            if(k <= p->ch[i]->dp) {
                putchar('a' + i);
                k -= p->ch[i]->val;
                p = p->ch[i];
                flag = 1;
                break;
            }
            else k -= p->ch[i]->dp;
        }
        if(!flag) break;
    }
}
int main() {
    scanf("%s",s);
    int n = strlen(s);
    N = n;
    init();
    REP(i , n) insert(s[i]);
    int K;
    scanf("%d%d",&T,&K);
    bfs();
    solve(K);
    return 0;
}
