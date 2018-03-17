#include <stdio.h>
#include <stdlib.h>


int dp[101][101];
int triangle[101][101];
void clear_dp_and_triangle(){
	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++){
			dp[i][j] = 0;
			triangle[i][j] = 0;
		}
}
int main(){
	int tests;
	scanf("%d",&tests);
	for(int i=0;i<tests;i++){
		int level;
		scanf("%d",&level);
		clear_dp_and_triangle();
		for(int j=0;j<level;j++){
			for(int k=0;k<=j;k++)
				scanf("%d",&triangle[j][k]);
		}
		dp[0][0] = triangle[0][0];
		int max = dp[0][0];
		for(int i=1;i<level;i++){
			for(int j=0;j<=i;j++){
				if(j==0)
					dp[i][j] = dp[i-1][j] + triangle[i][j];
				else if(j)
					dp[i][j] = (dp[i-1][j] > dp[i-1][j-1] ? dp[i-1][j] : dp[i-1][j-1]) + triangle[i][j];
				max = (max > dp[i][j] ? max : dp[i][j]);
			}
		}
		printf("%d\n",max);
	}
	return 0;
}
