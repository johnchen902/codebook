constexpr int MAX_N = 500000 + 10;
struct Node {
	static Node mem[MAX_N * 2], *pmem;
	Node *ch[26], *fail;
	int mx, val, tag, deg;
	ll dp;
	Node(): ch(), fail(), mx(), val(), tag(), deg(), dp() {}
} Node::mem[MAX_N * 2], *Node::pmem = Node::mem, *root, *last;
int T, N;
char s[MAX_N];
void init() {
	last = root = new (Node::pmem++) Node();
}
void insert(int c) {
	c -= 'a';
	Node *p = last;
	Node *np = new (Node::pmem++)Node();
	np->mx = p->mx + 1;
	np->val = 1;
	while (p && !p->ch[c]) {
		p->ch[c] = np;
		np->deg++;
		p = p->fail;
	}
	if (!p) np->fail = root;
	else {
		Node *q = p->ch[c];
		if (q->mx == p->mx + 1) np->fail = q;
		else {
			Node *nq = new (Node::pmem++) Node();
			nq->mx = p->mx + 1;
			nq->val = 0;
			memcpy(nq->ch, q->ch, sizeof(q->ch));
			for (auto ch : nq->ch)
				if (ch) ch->deg++;
			nq->fail = q->fail;
			q->fail = np->fail = nq;
			while (p && p->ch[c] == q) {
				p->ch[c] = nq;
				q->deg--;
				nq->deg++;
				p = p->fail;
			}
		}
	}
	last = np;
}
void bfs() {
	static Node* que[MAX_N * 2];
	int l = 0, r = 0;
	que[r++] = root;
	root->tag = 2;
	vector<Node*> vec;
	while (l < r) {
		Node *u = que[l++];
		for (auto ch : u->ch)
			if (ch && --ch->deg == 0 && ch->tag != 1) {
				ch->tag = 1;
				que[r++] = ch;
				vec.push_back(ch);
			}
	}
	for (int i = vec.size() - 1; i >= 0; i--) {
		Node *u = vec[i];
		if (T) {
			if(u->fail) u->fail->val += u->val;
		}
		else u->val = 1;
	}
	root->val = 0;
	for (int i = vec.size() - 1; i >= 0; i--) {
		Node *u = vec[i];
		u->dp = u->val;
		for (auto ch : u->ch)
			if(ch) u->dp += ch->dp;
	}
	for (auto ch : root->ch)
		if(ch) root->dp += ch->dp;
}
void solve(int k) {
	Node *p = root;
	if (k > p->dp || k <= 0) {
		puts("-1");
		return;
	}
	while (k > 0) {
		int flag = 0;
		REP (i, 26) {
			if (!p->ch[i]) continue;
			if (k <= p->ch[i]->dp) {
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
	REP(i, n) insert(s[i]);
	int K;
	scanf("%d%d",&T,&K);
	bfs();
	solve(K);
	return 0;
}
