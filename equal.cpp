#include <bits/stdc++.h>
#define MIN(x,y,z) (x<y ? (x<z ? x : z) : (y<z ? y : z)) 
using namespace std;


int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i=0;i<n;i++)
        	cin>>arr[i];
        sort(arr.begin(), arr.end());
        
        int min = arr[0];
        int result = 0;
        for(int i=0;i<n;i++){
            int tmp = arr[i]-min;
            arr[i] = tmp%5;
            result += tmp/5;
        }
        min = *min_element(arr.begin(),arr.end());
        vector<int> freq(5);
        for(int i=0;i<n;i++) freq[arr[i]-min]++;

        int case1 = (freq[1]+freq[2]) + 2*(freq[3]+freq[4]);
        int case2 = (freq[0]+freq[1]+freq[4]) + 2*(freq[2]+freq[3]);
		int case3 = (freq[0]+freq[3]) + 2*(freq[1]+freq[2]+freq[4]);

        cout<<result+MIN(case1,case2,case3)<<endl;
    }
    return 0;
}
