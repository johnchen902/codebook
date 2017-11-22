const int MAX_N = 100 + 10;
int ans;
int G[MAX_N][MAX_N];
__int128 adj_v[MAX_N];
inline int count_bit(__int128 x) {
    return __builtin_popcountll((ll)(x>>50)) + __builtin_popcountll((ll)(x&((((__int128)1)<<50) - 1)));
}
inline int bit_pos(__int128 x) {
    if(x&((((__int128)1)<<50) - 1)) return __builtin_ctzll((ll)(x&((((__int128)1)<<50) - 1)));
    else return __builtin_ctzll((ll)(x>>50)) + 50;
}
void dfs(__int128 R , __int128 P , __int128 X) {
    ans = max(ans , count_bit(R));
    int t = count_bit(R) + count_bit(P);
    if(t <= ans || !P) return;
    int pivot = bit_pos(P | X);
    __int128 tp = P & ~adj_v[pivot];
    while(tp && t > ans) {
        int v = bit_pos(tp);
        dfs(R | ((__int128)1<<v) , P & adj_v[v] , X & adj_v[v]);
        P ^= ((__int128)1<<v);
        X |= ((__int128)1<<v);
        t--;
        if(t <= ans) return;
        tp ^= (((__int128)1)<<v);
    }
}
