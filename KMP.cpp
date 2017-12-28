#include <iostream>
#include <vector>
using namespace std;

vector<int> Prefix(string& Pattern){
        int m = Pattern.length();
        int k = 0;
        vector<int> pi(m,0);
        for(int q=1;q<m;q++){
                while(k>0 && Pattern[k+1]!=Pattern[q])
                        k = pi[k];
                if(Pattern[k+1] == Pattern[q])
                        k++;
                pi[q] = k;
        }
        return pi;
}

void KMP(string& Text, string& Pattern){
        int n = Text.length();
        int m = Pattern.length();
        vector<int> pi = Prefix(Pattern);
        int q = 0;
        for(int i=0;i<n;i++){
                //cout<<"q: "<<q<<", next char in P: "<<Pattern[q]<<", current char in T: "<<Text[i]<<endl;
                while(q>0 && Pattern[q] != Text[i])
                        q = pi[q];
                if(Pattern[q] == Text[i])
                        q++;
                if(q==m){
                        //cout<<"Pattern occurs with shift "<<i-m+1<<endl;
                        q = pi[q];
                }
        }
        return;
}


int main(){
        string Text = "abacdabac";
        string Pattern = "bac";
        KMP(Text,Pattern);
        return 0;
}
