const int MAX_N = 1000000 + 10;
const ll MOD = 1000000000 + 7;
ll inv[MAX_N];
int main() {
    int n;
    scanf("%d",&n);
    inv[0] = 1;
    inv[1] = 1;
    REP1(i , 2 , n) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    return 0;
}
