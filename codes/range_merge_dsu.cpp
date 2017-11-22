const int MAX_N = 100000 + 10;
int A[MAX_N];
char str[MAX_N];
int par[MAX_N][20];
vector<int> can_not[MAX_N];
int find(int x , int y) {
    if(par[x][y] == x) return x;
    else return par[x][y] = find(par[x][y] , y);
}
inline bool merge(int x , int y , int k) {
    x = find(x , k);
    y = find(y , k);
    if(x == y) return 0;
    par[y][k] = x;
    if(k--) {
        merge(x , y , k);
        merge(x + (1<<k) , y + (1<<k) , k);
    }
    return 1;
}
int main() {
    int N;
    scanf("%d",&N);
    REP1(i , 1 , N) {
        REP(j , 20) par[i][j] = i;
    }
    REP1(i , 1 , N) {
        scanf("%d",&A[i]);
        if(A[i] == 0) continue;
        int k = 0;
        int l1 = 1 , r1 = 1 + A[i] - 1;
        int l2 = i , r2 = i + A[i] - 1;
        while((1<<(k + 1)) <= r1 - l1 + 1) k++;
        merge(l1 , l2 , k);
        merge(r1 - (1<<k) + 1 , r2 - (1<<k) + 1 , k);
    }
    REP1(i , 1 , N) {
        if(i + A[i] <= N) {
            if(find(A[i] + 1 , 0) == find(i + A[i] , 0)) {
                puts("-1");
                return 0;
            }
            can_not[i + A[i]].PB(A[i] + 1);
        }
    }
    MS(str , 0);
    str[1] = 'a';
    REP1(i , 2 , N) {
        if(A[i] != 0) str[i] = str[1];
        else {
            int p = find(i , 0);
            if(p == i) {
                bool arr[26];
                int ch = -1;
                MS(arr , 0);
                arr[str[1] - 'a'] = 1;
                for(int x : can_not[i]) arr[str[x] - 'a'] = 1;
                REP(j , 26) {
                    if(!arr[j]) {
                        ch = j;
                        break;
                    }
                }
                if(ch == -1) {
                    puts("-1");
                    return 0;
                }
                str[i] = 'a' + ch;
            }
            else str[i] = str[p];
        }
    }
    printf("%s\n",str + 1);
    return 0;
}
