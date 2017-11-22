char str[maxn]; // need null character
// sa[0]="", ht[i+1]=lcp(sa[i],sa[i+1])
int sa[maxn], cnt[maxn], x[maxn], y[maxn], ht[maxn];
void build_sa(int n, int m) {
	copy_n(str, n + 1, x);
	fill_n(cnt, m, 0);
	for (int i = 0; i <= n; i++)
		cnt[x[i]]++;
	partial_sum(cnt, cnt + m, cnt);
	for (int i = n; i >= 0; i--)
		sa[--cnt[x[i]]] = i;
	for (int k = 1; ; k <<= 1, m = p) {
		int p = 0;
		for (int i = n - k + 1; i <= n; i++)
			y[p++] = i;
		for (int i = 0; i <= n; i++)
			if (sa[i] >= k)
				y[p++] = sa[i] - k;
		fill_n(cnt, m, 0);
		for (int i = 0; i <= n; i++)
			cnt[x[y[i]]]++;
		partial_sum(cnt, cnt + m, cnt);
		for (int i = n; i >= 0; i--)
			sa[--cnt[x[y[i]]]] = y[i];
		copy_n(y, n + 1, x);
		p = 1;
		x[sa[0]] = 0;
		for (int i = 1; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p - 1 : p++);
		if (p >= n + 1) break;
	}
}
void build_ht(int n) {
	for (int i = 1; i <= n; i++)
		x[sa[i]] = i;
	for (int i = 0, h = 0; i < n; i++) {
		int j = sa[x[i] - 1];
		if (h) h--;
		while (str[i + h] == str[j + h]) h++;
		ht[x[i]] = h;
	}
}
