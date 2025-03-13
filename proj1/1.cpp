#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pii pair<int, int>
#define F first
#define S second

const int maxn = 3e5 + 10;
int a[maxn], n;
pii seg[4 * maxn];

void update(int index, int val, int begin = 1, int end = n, int id = 1) {

  if (end == begin && index == begin) {
    seg[id].F += val;
    seg[id].S += 1;
    return;
  }

  int mid = (begin + end) >> 1;

  if (index <= mid)
    update(index, val, begin, mid, id << 1 | 0);
  else
    update(index, val, mid + 1, end, id << 1 | 1);

  seg[id].F = seg[id << 1 | 0].F + seg[id << 1 | 1].F;
  seg[id].S = seg[id << 1 | 0].S + seg[id << 1 | 1].S;
}

pii get_sum(int l, int r, int begin = 1, int end = n, int id = 1) {

  if (begin > r || l > end)
    return {0, 0};

  if (begin >= l && end <= r) {
    return seg[id];
  }

  int f, s, mid = (begin + end) >> 1;

  pii left = get_sum(l, r, begin, mid, id << 1 | 0),
      right = get_sum(l, r, mid + 1, end, id << 1 | 1);

  f = left.F + right.F;
  s = left.S + right.S;

  return {f, s};
}

int32_t main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  int ans = 0;

  for (int i = 0; i < n; i++) {
    update(a[i], i);
    pii curr = get_sum(a[i] + 1, n);
    ans = ans + (curr.S * i - curr.F);
  }

  cout << ans << '\n';
}

