#include <iostream>
#include <vector>
#include <string>

using namespace std;
int c_occurences = 0;
vector<int> local_damages;
int compute(string s){
    int result = 0;
    int damage = 1;
    for(int i=0;i<s.size();i++){
        if(s[i]=='S'){
            result += damage;
            local_damages[i] = damage; 
        }
        else{
            damage *= 2;
            c_occurences++;
        }
    }
    return result;
}

int main(){
    int tests;
    cin>>tests;
    for(int i=0;i<tests;i++){
        int D;
        string sequence;
        cin>>D>>sequence;
        local_damages.resize(sequence.size());
        int total_damage = compute(sequence);
        if(total_damage <= D)
            cout<<"Case #"<<i+1<<": 0"<<endl;
        else if(c_occurences==0)
            cout<<"Case #"<<i+1<<": IMPOSSIBLE"<<endl;
        else{
            int hacks = 0;
            bool done_flag = false;
            for(int j=sequence.size()-2;j>=0;j--){ // look for CS substring
                if(sequence[j]=='C' && sequence[j+1]=='S'){
                    for(int k=j;k<sequence.size()-1;k++){
                        if(sequence[k]=='C' && sequence[k+1]=='S'){
                            swap(sequence[k],sequence[k+1]);
                            total_damage -= local_damages[k+1]/2;
                            local_damages[k] = local_damages[k+1]/2;
                            hacks++;
                            if(total_damage<=D){
                                done_flag = true;
                                break;
                            }
                        }
                    }
                }
                if(done_flag)
                    break;
            }
            if(done_flag)
                cout<<"Case #"<<i+1<<": "<<hacks<<endl;
            else
                cout<<"Case #"<<i+1<<": IMPOSSIBLE"<<endl;
        }
        
    }
    return 0;   
}