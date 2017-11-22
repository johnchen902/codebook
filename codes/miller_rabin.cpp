const bool PRIME = 1 , COMPOSITE = 0;
inline ll mul(ll a , ll b , ll n) {
    ll r = 0;
    a %= n , b %= n;
    while(b) {
        if(b&1) r = (r + a >= n ? r + a - n : r + a);
        a = (a + a >= n ? a + a - n : a + a);
        b >>= 1;
    }
    return r;
}
inline ll power(ll a , ll b , ll m) {
    ll r = 1;
    while(b) {
        if(b&1) r = mul(r , a , m);
        a = mul(a , a , m);
        b >>= 1;
    }
    return r;
}
inline bool miller_rabin(ll n , ll a) {
    if(__gcd(a , n) == n) return PRIME;
    if(__gcd(a , n) != 1) return COMPOSITE;
    ll d = n - 1 , r = 0 , res;
    while(~d&1) r++ , d >>= 1;
    res = power(a , d , n);
    if(res == 1 || res == n - 1) return PRIME;
    while(r--) {
        res = mul(res , res , n);
        if(res == n - 1) return PRIME;
    }
    return COMPOSITE;
}
inline bool is_prime(ll n) {
    // ll table[3] = {2 , 7 , 51};
    // REP(i , 3) if(miller_rabin(n , table[i]) == COMPOSITE) return COMPOSITE;
    ll table[7] = {2 , 325 , 9375 , 28178 , 450775 , 9780504 , 1795265022};
    REP(i , 7) if(miller_rabin(n , table[i]) == COMPOSITE) return COMPOSITE;
    return PRIME;
}
