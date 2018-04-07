#include <iostream>
#include <vector>

using namespace std;
ostream& operator<< (ostream& out,vector<int>& v){
    out<<"[";
    for(int i=0;i<v.size();i++)
        out<<v[i]<<",";
    out<<"]";
    return out;
}
int main(){
    int tests;
    cin>>tests;
    for(int i=0;i<tests;i++){
        int n;
        cin>>n;

        vector<int> arr(n);
        for(int j=0;j<n;j++)
            cin>>arr[j];

        bool sorted = false;
        while(!sorted){
            sorted = true;
            for(int j=0;j<n-2;j++){
                if(arr[j]>arr[j+2]){
                    swap(arr[j],arr[j+2]);
                    sorted = false;
                }
            }
        }
        cout<<arr<<endl;
        bool ok = true;
        for(int j=0;j<n-1;j++){
            if(arr[j]>arr[j+1]){
                cout<<"Case #"<<i+1<<": "<<j<<endl;
                ok = false;
                break;
            }
        }
        if(ok) cout<<"Case #"<<i+1<<": OK"<<endl;
    }
}