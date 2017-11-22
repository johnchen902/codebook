// APIO 2014 Palindromes
const int MAX_N = 300000 + 10;
struct Node {
    int fail , ch[26];
    int len;
    ll dp;

    Node() : fail(0) , dp(0) , len(0) {
        MS(ch , 0);
    }
};
char s[MAX_N];
Node mem[MAX_N];
int pmem , last;
inline int new_node() {
    int id = pmem++;
    mem[id] = Node();
    return id;
}
inline void init() {
    pmem = 0;
    int a = new_node();
    int b = new_node();
    mem[a].fail = b;
    mem[b].len = -1;
    last = b;
}
inline int idx(char c) {
    return c - 'a';
}
inline void insert(int n , char c) {
    c = idx(c);
    int p = last , np;
    while(s[n - mem[p].len - 1] != s[n]) p = mem[p].fail;
    if(!mem[p].ch[c]) {
        np = new_node();
        mem[np].len = mem[p].len + 2;
        int q = mem[p].fail;
        while(s[n - mem[q].len - 1] != s[n]) q = mem[q].fail;
        mem[np].fail = mem[q].ch[c];
        mem[p].ch[c] = np;
    }
    else np = mem[p].ch[c];
    mem[np].dp++;
    last = np;
}
int main() {
    init();
    SR(s + 1);
    int n = strlen(s + 1);
    REP1(i , 1 , n) insert(i , s[i]);
    ll ans = 0;
    for(int i = pmem - 1; i > 1; i--) {
        mem[mem[i].fail].dp += mem[i].dp;
        ans = max(ans , mem[i].dp * mem[i].len);
    }
    PL(ans);
    return 0;
}
