#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long int dp[101][101];
long long int triangle[101][101];
void fill_dp(){
	for(int i=0;i<101;i++){
		for(int j=0;j<101;j++)
			dp[i][j] = LONG_MAX;
	}
}
int main(){
	
	int level;
	scanf("%d",&level);
	for(int j=0;j<level;j++){
		for(int k=0;k<=j;k++)
			scanf("%llu",&triangle[j][k]);
	}
	fill_dp();
	dp[0][0] = triangle[0][0];
	long long int min = LONG_MAX;
	for(int i=0;i<level;i++){
		for(int j=0;j<level;j++){
			if(i==0 && j==0)continue;
			if(j==0)
				dp[i][j] = dp[i-1][j] + triangle[i][j];
			else if(i==0)
				dp[i][j] = dp[i][j-1] + triangle[i][j];
			else{
				long long int m;
				if(dp[i-1][j-1]<dp[i-1][j]){
					if(dp[i-1][j-1]<dp[i][j-1])
						m = dp[i-1][j-1];
					else
						m = dp[i][j-1];
				}
				else{
					if(dp[i-1][j]<dp[i][j-1])
						m = dp[i-1][j];
					else
						m = dp[i][j-1];
				}
				dp[i][j] = m + triangle[i][j];
			}
		}
	}
	printf("%llu\n",dp[level-1][level-1]);
	return 0;
}
