#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        
        int n;
        cin >> n;
        int min = INT_MAX;
        vector<int> arr(n),delta(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           cin >> arr[arr_i];
           if(arr[arr_i] < min) min = arr[arr_i];
        }
        int result = INT_MAX;
        int target = min;
        for(int target=min;target>=min-10;target--){ // Try each baseline down to min-10 (including)
            if(target<0)break;
            int total= 0;
            // Below code block computess the minimal partition possible for each element. 
            // Namely, if an element is greater than 5; it is first divised by 5 and so on.
            // By finding minimal partitions, per element computation reduces to O(1). In total one pass for each baseline is O(n).
            // Total complexity is O(5*n)
            for(int i=0;i<n;i++){
                delta[i] = arr[i] - target;
                if(delta[i]>=5){
                    int factor = delta[i]/5;
                    total+=factor;
                    delta[i] -= 5*factor;
                }
                if(delta[i]>=2){
                    int factor = delta[i]/2;
                    total+=factor;
                    delta[i] -= 2*factor;
                    
                }
                if(delta[i]>=1){
                    total += delta[i];

                }
            }
            if(total < result)
                result = total;
        }
        cout<<result<<endl;
        
        
    }
    return 0;
}
