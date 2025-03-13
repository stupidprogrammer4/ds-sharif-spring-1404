#include <bits/stdc++.h>

using namespace std;
#define pdd pair<double, double>
#define F first
#define S second

const int maxn = 1e5 + 10;
pdd p[maxn];
map<pdd, int> lines;
double epsilon = 1e-5;

inline bool at_line(double a, double b, pdd point) {
  return abs(point.S - (point.F * a + b)) <= epsilon;
}

void brute_force(int begin, int end) {
  set<pdd> curr_lines;
  for (int i = begin; i < end; i++) {
    for (int j = i + 1; j < end; j++) {
      double dy = p[j].S - p[i].S, dx = p[j].F - p[i].F, a = 0., b = 0.;
      if (dx == 0.) {
        a = DBL_MAX;
        b = p[j].F;
      } else {
        a = dy / dx;
        b = p[j].S - p[j].F * a;
      }

      curr_lines.insert({a, b});
    }
  }

  for (pdd ln : curr_lines) {
    for (int i = begin; i < end; i++) {
      if (ln.F == DBL_MAX) {
        if (ln.S == p[i].F)
          lines[ln] += 1;
        continue;
      }
      if (at_line(ln.F, ln.S, p[i]))
        lines[ln] += 1;
    }
  }
}

auto main() -> int32_t {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
    cin >> p[i].F >> p[i].S;

  sort(p, p + n);

  if (n <= 1000) {
    brute_force(0, n);
    int ans = 0;
    for (auto item : lines)
      ans = max(ans, item.S);
    cout << ans << '\n';
    exit(0);
  }

  for (int i = 0; i < n; i += 6)
    brute_force(i, min(i + 6, n));

  vector<pdd> final_lines;

  for (auto ln : lines)
    if (ln.S >= n / 30)
      final_lines.push_back(ln.F);

  int ans = 0;
  for (auto ln : final_lines) {
    int curr = 0;
    for (int i = 0; i < n; i++)
      if (at_line(ln.F, ln.S, p[i]))
        curr++;

    ans = max(ans, curr);
  }

  cout << ans << '\n';
}
