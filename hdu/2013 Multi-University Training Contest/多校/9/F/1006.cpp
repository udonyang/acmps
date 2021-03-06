#include <cstdio>
#include <vector>
#include <limits>
#include <climits>
#include <utility>
#include <cstring>
#include <cassert>
#include <numeric>
#include <algorithm>

using namespace std;

template<typename T>
struct RMQ {
  int n;
  vector<T> e;
  vector<vector<int> > rmq;

  static const int INT_BIT = sizeof(4) * CHAR_BIT;
  static inline int LG2(int i) { return INT_BIT - 1 - __builtin_clz(i); }
  static inline int BIN(int i) { return 1 << i; }

  int cmp(int l, int r) const {
    return e[l] <= e[r] ? l : r;
  }

  void init(int n, const T e[]) {
    this->n = n;
    vector<T>(e, e + n).swap(this->e);

    int m = 1;
    while (BIN(m) <= n) {
      ++m;
    }
    vector<vector<int> >(m, vector<int>(n)).swap(rmq);

    for (int i = 0; i < n; ++i) {
      rmq[0][i] = i;
    }
    for (int i = 0; BIN(i + 1) <= n; ++i) {
      for (int j = 0; j + BIN(i + 1) <= n; ++j) {
        rmq[i + 1][j] = cmp(rmq[i][j], rmq[i][j + BIN(i)]);
      }
    }
  }

  int index(int l, int r) const {
    int b = LG2(r - l);
    return cmp(rmq[b][l], rmq[b][r - (1 << b)]);
  }

  T value(int l, int r) const {
    return e[index(l, r)];
  }
};

struct SuffixArrayBase {
  vector<int> sa, rank, height;

  template<typename T>
  void init(int n, const T a[]) {
    height.resize(n);
    for (int i = 0, z = 0; i < n; ++i) {
      if (rank[i] == 0) {
        height[0] = z = 0;
      } else {
        int x = i, y = sa[rank[i] - 1];
        z = max(0, z - 1);
        while (x + z < n && y + z < n && a[x + z] == a[y + z]) {
          ++z;
        }
        height[rank[i]] = z;
      }
    }
  }
};

struct SuffixArrayYoung: SuffixArrayBase {
  template<typename T>
  void init(int n, const T a[]) {
    sa.resize(n);
    rank.resize(n);

    vector<pair<T, int> > assoc(n);
    for (int i = 0; i < n; ++i) {
      assoc[i] = make_pair(a[i], i);
    }
    sort(assoc.begin(), assoc.end());
    for (int i = 0; i < n; ++i) {
      sa[i] = assoc[i].second;
      if (i == 0 || assoc[i].first != assoc[i - 1].first) {
        rank[sa[i]] = i;
      } else {
        rank[sa[i]] = rank[sa[i - 1]];
      }
    }

    vector<int> tmp(n), cnt(n);
    vector<pair<int, int> > suffix(n);
    for (int m = 1; m < n; m <<= 1) {
      // snd
      for (int i = 0; i < m; ++i) {
        tmp[i] = n - m + i;
      }
      for (int i = 0, j = m; i < n; ++i) {
        if (sa[i] >= m) {
          tmp[j++] = sa[i] - m;
        }
      }
      // fst
      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < n; ++i) {
        ++cnt[rank[i]];
      }
      partial_sum(cnt.begin(), cnt.end(), cnt.begin());
      for (int i = n - 1; i >= 0; --i) {
        sa[--cnt[rank[tmp[i]]]] = tmp[i];
      }
      //
      for (int i = 0; i < n; ++i) {
        suffix[i] = make_pair(rank[i],
          i + m < n ? rank[i + m] : numeric_limits<int>::min());
      }
      for (int i = 0; i < n; ++i) {
        if (i == 0 || suffix[sa[i]] != suffix[sa[i - 1]]) {
          rank[sa[i]] = i;
        } else {
          rank[sa[i]] = rank[sa[i - 1]];
        }
      }
    }

    SuffixArrayBase::init(n, a);
  }
} sa;

RMQ<int> rmq;

int lcp(int i, int j) {
  i = sa.rank[i];
  j = sa.rank[j];
  if (i > j) {
    swap(i, j);
  }
  return rmq.value(i + 1, j + 1);
}

int len(int x) {
  return x < 10 ? 1 : len(x / 10) + 1;
}

const int MAXN = 100100;

char s[MAXN];

int main() {
  int n, m, c;
  pair<int, int> a, b;
  long long x, y;

  while (scanf("%s%d", s, &n) != EOF) {
    m = strlen(s);
    assert(m <= 100000 && n <= 100000);
    sa.init(m, s);
    rmq.init(m, &sa.height[0]);
    x = y = 0;
    a = make_pair(0, 0);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &b.first, &b.second);
      assert(0 <= b.first && b.first < b.second && b.second <= m);
      b.second -= b.first;
      c = a.first == b.first ? MAXN : lcp(a.first, b.first);
      c = min(c, min(a.second, b.second));
      x += b.second + 1;
      y += c - len(c) - 1;
      a = b;
    }
    y = x - y;
    printf("%I64d %I64d\n", x, y);
  }

  return 0;
}
