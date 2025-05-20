#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];

class heap {
private:
  int items[maxn];
  size_t size;

  void __push_down(size_t v) {
    size_t max_v = -1;
    if ((v << 1) <= size)
      max_v = v << 1;
    if ((v << 1 | 1) <= size && items[v << 1 | 1] > items[v])
      max_v = v << 1 | 1;

    if (max_v > 0 && (items[max_v] > items[v])) {
      swap(items[max_v], items[v]);
      __push_down(max_v);
    }
  }

  void __push_up(size_t v) {
    if (v == 1 || items[v] < items[v >> 1])
      return;
    swap(items[v], items[v >> 1]);
    __push_up(v >> 1);
  }

public:
  heap() {
    size = 0;
    memset(items, 0, sizeof(items));
  }
  void push(int val) {
    size++;
    items[size] = val;
    __push_up(size);
  }

  void pop() {
    swap(items[1], items[size]);
    size--;
    __push_down(1);
  }

  int top() { return items[1]; }

  size_t len() { return size; }
};

int main() {
  cin.tie(0), cout.tie(0);
  ios_base::sync_with_stdio(0);

  int t, k, n, m, k_counter, mx, tmp;
  cin >> t;

  while (t--) {
    cin >> n >> m >> k;
    k_counter = k, mx = n * m - 3;

    for (int i = 0; i < k; i++)
      cin >> a[i];

    set<int> s;

    string ans = "Yes";
    for (int i = 0; i < k; i++) {
      s.insert(a[i]);
      tmp = *(--s.end());
      if (tmp == k_counter)
        s.erase(tmp), k_counter--;
      if (s.size() >= mx) {
        ans = "No";
        break;
      }
    }
    cout << ans << '\n';
  }
}

