#include <iostream>
#include <vector>
#include <algorithm>


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

        vector<int> even_indices;
        vector<int> odd_indices;
        vector<int> arr(n);
        for(int j=0;j<n;j++){
            cin>>arr[j];
            if(j%2)
                odd_indices.push_back(arr[j]);
            else
                even_indices.push_back(arr[j]);
        }
        sort(odd_indices.begin(),odd_indices.end());
        sort(even_indices.begin(),even_indices.end());
        //cout<<odd_indices<<endl;
        //cout<<even_indices<<endl;
        int even_indice = 1, odd_indice = 0;
        int former_value = even_indices[0];
        int result = 0;
        bool ok = true;
        for(int j=1;j<n;j++){
            if(j%2==0){
                if(former_value > even_indices[even_indice]){
                    result = j-1;
                    ok = false;
                    break;
                }
                else{
                    former_value = even_indices[even_indice];
                    even_indice++;
                }
            }
            else{
                if(former_value > odd_indices[odd_indice]){
                    result = j-1;
                    ok = false;
                    break;
                }
                else{
                    former_value = odd_indices[odd_indice];
                    odd_indice++;
                }
            }
        }
        if(!ok)
            cout<<"Case #"<<i+1<<": "<<result<<endl;
        else
            cout<<"Case #"<<i+1<<": OK"<<endl;
        }
}