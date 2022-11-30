#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 5e5, MAXM = 1e6;
const int MOD = 1e9 + 7;

int n, m;

int h[MAXN + 5], nxt[MAXM * 2 + 5], to[MAXM * 2 + 5], vv[MAXN + 5];
int vs[MAXN + 5], ve[MAXN + 5], vh[MAXN + 5], vnxt[MAXN + 5], vto[MAXN + 5], cnt = 0, tot = 0;

int fa[MAXN + 5], dep[MAXN + 5];

int stk[MAXN + 5], top = 0;

int Dfs(int x)
{
    int ret = dep[x];
    stk[++top] = x;
    for (int i = h[x]; i; i = nxt[i]) if (to[i] != fa[x])
    {
        if (!dep[to[i]])
        {
            fa[to[i]] = x;
            dep[to[i]] = dep[x] + 1;
            int res = Dfs(to[i]);
            ret = min(ret, res);
        }
        else if (dep[to[i]] < dep[x]) ret = min(ret, dep[to[i]]);
    }
    if (ret == dep[x])
    {
        ++cnt;
        while (dep[stk[top]] >= dep[x])
        {
            vv[stk[top]] = cnt;
            ++vs[cnt];
            for (int i = h[stk[top]]; i; i = nxt[i]) if (dep[to[i]] > dep[stk[top]])
            {
                if (vv[to[i]] != vv[stk[top]])
                {
                    ++tot;
                    vto[tot] = vv[to[i]];
                    vnxt[tot] = vh[cnt];
                    vh[cnt] = tot;
                }
                else ++ve[cnt];
            }
            --top;
        }
    }
    return ret;
}

long long p[MAXN + 5];
int sz[MAXN + 5];
long long f[MAXN + 5];

void Dp(int x)
{
    sz[x] = ve[x];
    f[x] = p[ve[x]] * p[vs[x]] % MOD;
    for (int i = vh[x]; i; i = vnxt[i])
    {
        Dp(vto[i]);
        sz[x] += sz[vto[i]] + 1;
        f[x] = f[x] * (p[sz[vto[i]]] + f[vto[i]]) % MOD;
    }
} 

long long Ans = 0;

int main()
{
    // freopen("data.in", "r", stdin);
    // freopen("run.out","w",stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &to[i * 2], &to[i * 2 - 1]);
        nxt[i * 2 - 1] = h[to[i * 2]];
        h[to[i * 2]] = i * 2 - 1;
        nxt[i * 2] = h[to[i * 2 - 1]];
        h[to[i * 2 - 1]] = i * 2;
    }

    dep[1] = 1;
    Dfs(1);
    p[0] = 1;
    for (int i = 1; i <= m; ++i) p[i] = (p[i - 1] << 1) % MOD;

    Dp(cnt);

    for (int i = 1; i <= cnt; ++i) Ans = (Ans + (f[i] - p[sz[i]]) * p[m - sz[i] - (i != cnt)] % MOD) % MOD;
    printf("%lld\n", (Ans + MOD) % MOD);

    return 0;
}
