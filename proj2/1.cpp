#include <bits/stdc++.h>

using namespace std;

#define int long long int

const int maxn=2e5+10;

int a[maxn], seg_a[4*maxn], n, 
b[maxn], seg_b[4*maxn], lazy[4*maxn];

void build_a(int begin=0, int end=n-1, int id=1) {
    if (begin >= end) {
        seg_a[id] = a[begin];
        return;
    }

    int mid=(begin+end)>>1;
    build_a(begin, mid, id<<1|0);
    build_a(mid+1, end, id<<1|1);

    seg_a[id] = min(seg_a[id<<1|0], seg_a[id<<1|1]);
}

void update_a(int i, int d,
        int begin=0, int end=n-1, int id=1) {
    if (begin >= end) {
        seg_a[id] -= d;
        return;
    }

    int mid=(begin+end)>>1;
    if (i <= mid)
        update_a(i, d, begin, mid, id<<1|0);
    else
        update_a(i, d, mid+1, end, id<<1|1);

    seg_a[id] = min(seg_a[id<<1|0], seg_a[id<<1|1]);
}

int first_less_than(int k, int l, int r,
        int begin=0, int end=n-1, int id=1) {
    if (begin > r || l > end || seg_a[id] >= k || l > r)
        return n;

    if (begin >= end)
        return begin;

    int mid=(begin+end)>>1;
    int idx = first_less_than(k, l, r, begin, mid, id<<1|0);
    if (idx >= n)
        idx = first_less_than(k, l, r, mid+1, end, id<<1|1);

    return idx;
}

int get_min(int l, int r,
        int begin=0, int end=n-1, int id=1) {
    if (begin > r || l > end || l > r)
        return INT64_MAX;

    if (begin >= l && end <= r)
        return seg_a[id];
    
    int mid=(begin+end)>>1;
    int left = get_min(l, r, begin, mid, id<<1|0),
       right = get_min(l, r, mid+1, end, id<<1|1);

    return min(left, right);
}

void build_b(int begin=0, int end=n-1, int id=1) {
    if (begin >= end) {
        seg_b[id] = b[begin];
        return;
    }

    int mid=(begin+end)>>1;
    build_b(begin, mid, id<<1|0);
    build_b(mid+1, end, id<<1|1);

    seg_b[id] = seg_b[id<<1|0] + seg_b[id<<1|1];
}

inline void lazy_propagate(int begin, int end, int id) {
    if (lazy[id] >= 0) {
        seg_b[id] = (end - begin + 1) * lazy[id];
        if (begin < end)
            lazy[id<<1|0] = lazy[id<<1|1] = lazy[id];

        lazy[id] = -1;
    }
}

void set_bit(int bit, int l, int r,
        int begin=0, int end=n-1, int id=1) {
    lazy_propagate(begin, end, id);

    if (begin > r || l > end || l > r)
        return;

    if (begin >= l && end <= r) {
        seg_b[id] = (end - begin + 1)*bit;

        if (begin < end)
            lazy[id<<1|0] = lazy[id<<1|1] = bit;

        return;
    }

    int mid=(begin+end)>>1;
    set_bit(bit, l, r, begin, mid, id<<1|0);
    set_bit(bit, l, r, mid+1, end, id<<1|1);

    seg_b[id] = seg_b[id<<1|0] + seg_b[id<<1|1];
}

int32_t main() {
    ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
    int q, idx, d;

    cin>>n>>q;

    for (int i=0; i<n; i++) cin>>a[i];

    int mn=a[0];
    for (int i=0; i<n; i++)
        if (a[i] < mn)
            mn = a[i], b[i] = 1;
    
    
    memset(lazy, 0xff, sizeof(lazy));
    build_a();
    build_b();
    while (q--) {
        cin>>idx>>d;
        idx--;
        a[idx] -= d;

        update_a(idx, d);
        mn = get_min(0, idx-1);

        if (a[idx] < mn && idx > 0)
            set_bit(1, idx, idx);
        
        int j = first_less_than(a[idx], idx+1, n-1);
        set_bit(0, idx+1, j-1);

        cout<<seg_b[1]<<'\n';
    }
}

