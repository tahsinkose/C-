/* Finite Automaton Matcher */
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "colormod.h"

using namespace std;
vector<int> occurences; // global variable to hold all occurences of the world.


ostream& operator << (ostream& os, string& s) 
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    for (int i=0;i<s.size();i++)
    {
        if(find(occurences.begin(),occurences.end(),i)!=occurences.end())
                os <<red<<s[i];
        else
                os <<def<<s[i];
    }
    return os;
}
vector<char> ConstructAlphabet(string& Text){
        vector<char> alpha;        
        for(int i=0;i<Text.size();i++){
                if(find(alpha.begin(),alpha.end(),Text[i]) == alpha.end())
                        alpha.push_back(Text[i]);      
        }
        return alpha;
}

bool Suffix(string& a, string& b){
        int m = a.size();
        int n = b.size();
        if(n<m)
                return false;        
        for(int i=0;i<m;i++){
                if(b[n-m+i]!=a[i])
                        return false;
        }
        return true;
}

map<pair<int, char>,int > Transition(string& P,vector<char>& Alphabet){
        int m = P.length();
        map<pair<int, char>,int > sigma;                
        for(int q=0;q<m;q++){
                for(int l=0;l<Alphabet.size();l++){
                        int k = (m+1 < q+2 ) ? m+1 : q+2;
                        k--;
                        string Pk = P.substr(0,k);
                        string Pqalpha = P.substr(0,q).append(1,Alphabet[l]);
                        //cout<<"Pq: "<<Pqalpha<<endl;
                        bool is_suffix = Suffix(Pk,Pqalpha);
                        while(!is_suffix && k>0){
                                
                                k--;
                                Pk = P.substr(0,k);
                                //cout<<"Pk: "<<Pk<<endl;
                                is_suffix = Suffix(Pk,Pqalpha);
                        }
                        sigma.insert(make_pair(make_pair(q,Alphabet[l]),k));
                        //cout<<"sigma["<<q<<","<<Alphabet[l]<<"] = "<<k<<endl;
                }
        }
        return sigma;
}

int main(int argc,char* argv[]){
        if(argc!=3)
                cout<<"Usage "<<argv[0]<<" <input file> <string pattern> "<<endl;
        ifstream f(argv[1]);
        stringstream buffer;
        buffer << f.rdbuf();
        
        string Text = buffer.str();
        string Pattern = argv[2];
        int n = Text.length();
        int m = Pattern.length();
        int q = 0;
        vector<char> Alphabet = ConstructAlphabet(Text);
        map<pair<int,char>,int > sigma = Transition(Pattern,Alphabet);
        
        for(int i=0;i<n;i++){
                q = sigma[{q,Text[i]}];
                if(q==m){
                        //cout<<"Pattern occurs with shift "<<i-m+1<<endl;
                        for(int k=0;k<m;k++)
                                occurences.push_back(i-m+1+k);
                        //cout<<"Cascade up to "<<i<<endl;
                }
        }
        
        cout<<Text<<endl;
        return 0;
}

