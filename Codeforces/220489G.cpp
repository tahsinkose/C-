#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct item_status{
	int needed_time;
	int completely_burned;
	int value;
	int which_item;
};

vector<int> saved_elements;

bool compare(const item_status &a,const item_status &b ){
	return a.completely_burned < b.completely_burned;
}
int main()
{
	vector<vector<int> > dp(150,vector<int>(2500,0)); // Max n = 100, and max_d = 2000, Respecting 1-indexed problem, this is the 
													  // minimal 2-D DP storage.
	vector<vector<int> > last_saved_elements(150,vector<int>(2500,0));
    int n;
    cin>>n;
    vector<item_status> items(n+1);
	for(int i=1;i<=n;i++){
		cin>>items[i].needed_time>>items[i].completely_burned>>items[i].value;
		items[i].which_item = i;
	}
    for(int i=1;i<=n;i++){
    	cin>>items[i].needed_time>>items[i].completely_burned>>items[i].value;
    	items[i].which_item=i;
    }
    sort(items.begin()+1,items.begin()+1+n,compare);
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=2000;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=items[i].needed_time && j<items[i].completely_burned)
            {
            	int psv = dp[i-1][j-items[i].needed_time]+items[i].value;
                if(psv>dp[i][j])
                {
                    dp[i][j]=psv;
                    last_saved_elements[i][j]=i;
                }
            }
        }
    }
    int result=0,last_saved_element;
    for(int i=1;i<=2000;i++)
    {
        if(result<dp[n][i])
        {
            result=dp[n][i];
            last_saved_element=i;
        }
    }
    cout<<result<<endl;

    int level=n;
    while(last_saved_element>0&&level>0)
    {
      if(last_saved_elements[level][last_saved_element]>0){
        saved_elements.push_back(items[last_saved_elements[level][last_saved_element]].which_item);
        last_saved_element-=items[last_saved_elements[level][last_saved_element]].needed_time;
      }
        level--;
    }
    int sz = saved_elements.size();
	cout<<sz<<endl;
	for(int i=sz-1;i>=0;i--)
		cout<<saved_elements[i]<<" ";
	cout<<endl;
}