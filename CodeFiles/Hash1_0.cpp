#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
unordered_map<ll, int> mp;
int num[100010];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        mp[a]++, mp[b]++;
    }
    ll ans = 1e12+10, max = 0;
    for (auto it : mp) {
        if (it.second >= max ) {
            if(it.second == max ){
                num[max]++;
                if(it.first<ans){
                    max = it.second;
                    ans = it.first;
                }
            }
            else{
                max = it.second;
                ans = it.first;
            }
        }
    }if(num[max]==0)
    cout << ans << " " << max;
    else cout << ans << " " << max << " "<<num[max]+1;
    return 0;
}
