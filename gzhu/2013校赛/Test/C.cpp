//Kimady::S.X.Dwylkz
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
//Namespace
namespace dtd{
	//Constant
	const long long INFLL = ~0uLL>>1;
	const int INFI = ~0u>>1;
	const int MAXN = 100;
	const int MAXM = 100;
	const int MOD = 1e+7;
	//Type Definition
	typedef unsigned int UI;
	typedef long long LL;
	typedef long double LD;
	typedef int AI[MAXN];
	typedef bool AB[MAXN];
	typedef double AD[MAXN];
	typedef LL ALL[MAXN];
	typedef LD ALD[MAXN];
	typedef AI AI2[MAXM];
	typedef AB AB2[MAXM];
	typedef AD AD2[MAXM];
	typedef ALL ALL2[MAXM];
	typedef ALD ALD2[MAXM];
}
using namespace std;
using namespace dtd;
//Macro
#define Bug puts("Here")
//Global
struct Int {
	char t[10], u[30];
	bool ins(char x[]) {
		int lu = strlen(u), lx = strlen(x);
		if (lu < lx) {
			return 0;
		} else if (lu == lx) {
			return -1 < strcmp(u, x);
		} 
		return 1;
	}
};
Int I[3] = {
	{"short", "32767"},
	{"int", "2147483647"},
	{"long long",  "9223372036854775807"}
};
char s[33];
//Main
int main()
{
#if 0
	freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
#endif
#if 0
	printf("%d, %d, %lld\n", 0x7fff, 0x7fffffff, 0x7fffffffffffffff);
#endif
	while (~scanf("%s", s)) {
		int ans = -1;
		for (int i = 0; i < 3; i++) {
			if (I[i].ins(s)) {
				ans = i;
				break;
			}
		}
		puts(ans < 0? "It is too big!": I[ans].t);
	}
	return 0;
}
