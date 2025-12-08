#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, L;
    cin >> N >> L;
    
    vector<int> fruits(N);
    for (int i = 0; i < N; i++) {
        cin >> fruits[i];
    }
    
    // 将水果按高度从小到大排序
    sort(fruits.begin(), fruits.end());
    
    int currentLength = L;
    
    // 贪心策略：从最小的水果开始，能吃就吃
    for (int i = 0; i < N; i++) {
        if (currentLength >= fruits[i]) {
            // 可以吃这个水果，长度+1
            currentLength++;
        } else {
            // 如果当前水果吃不了，后面的也吃不了（因为已排序）
            break;
        }
    }
    
    cout << currentLength << endl;
    
    return 0;
}