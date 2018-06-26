
 
#include "iostream"  
#include "algorithm"  
#include "cmath"  
using  namespace std;  
#define esp 1e-8  
int a[105];  
int main()  
{  
    int n,sum=0;  
    cin>>n;  
    for(int i=0;i<n;i++) {cin>>a[i];sum+=a[i];}  
    sort(a,a+n);  
    double ans=sum*1.0/n;  
    if(ans-4.5>esp||fabs(ans-4.5)<esp) cout<<"0"<<endl;  
    else{  
        int cnt=0;  
        for(int i=0;i<n;i++){  
            sum+=5-a[i];  
            ans=sum*1.0/n;  
            cnt++;  
            if(ans-4.5>esp||fabs(ans-4.5)<esp) break;  
        }  
        cout<<cnt<<endl;  
    }  
    return 0;  
}  