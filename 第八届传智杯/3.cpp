#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;
    
public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {
        // 初始化：所有资源都是解锁状态（值为1）
        for (int i = 1; i <= n; i++) {
            update(i, 1);
        }
    }
    
    // 更新操作：在位置 pos 加上 delta
    void update(int pos, int delta) {
        while (pos <= n) {
            tree[pos] += delta;
            pos += pos & -pos;
        }
    }
    
    // 查询前缀和 [1, pos]
    int query(int pos) {
        int sum = 0;
        while (pos > 0) {
            sum += tree[pos];
            pos -= pos & -pos;
        }
        return sum;
    }
    
    // 查询区间和 [l, r]
    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        
        FenwickTree ft(n);
        vector<bool> state(n + 1, true); // true表示解锁，false表示锁定
        
        for (int i = 0; i < m; i++) {
            int p;
            cin >> p;
            
            // 切换资源 p 的状态
            if (state[p]) {
                // 从解锁变为锁定：减去1
                ft.update(p, -1);
                state[p] = false;
            } else {
                // 从锁定变为解锁：加上1
                ft.update(p, 1);
                state[p] = true;
            }
            
            // 查询区间 [1, x] 中解锁的资源数
            int count1 = ft.rangeQuery(1, x);
            
            // 查询区间 [y, n] 中解锁的资源数
            int count2 = ft.rangeQuery(y, n);
            
            cout << count1 << " " << count2 << "\n";
        }
    }
    
    return 0;
}

