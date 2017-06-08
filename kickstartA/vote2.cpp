#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
double f[2001][2001];

int main() {
    freopen("A-small-practice.in", "r", stdin);
    freopen("out1.txt", "w", stdout);
    int test;
    scanf("%d", &test);
    for (int t = 1; t <= test; t++) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(f, 0, sizeof(f));
        f[1][0] = (double)n / double(n + m);
        for (int i = 2; i <= n + m; i++)
            for (int j = 1; j <= min(n, i); j++) {
                int k = i - j;
                if ((k > m) || (k >= j)) { continue; }
                if (j - 1 > k) {
                    f[j][k] += f[j - 1][k] * (double)(n - j + 1) / double(n + m - i + 1);
                }
                if (k > 0) {
                    f[j][k] += f[j][k - 1] * (double)(m - k + 1) / (double)(n + m - i + 1);
                }
            }
        printf("Case #%d: %.6f\n", t, f[n][m]);
    }
    return 0;
}
