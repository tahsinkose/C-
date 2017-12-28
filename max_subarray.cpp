#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <cmath>
#include <chrono>
#include <cstdlib>

#define N 100

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

tuple<int,int,int> max_subarray_n2(vector<int>& A);

/*This version has complexity O(nlogn)*/
tuple<int,int,int> find_max_crossing_subarray(vector<int>& A,int low,int mid,int high){
	int left_sum=INT_MIN;
	int sum=0;
	int max_left,max_right;
	for(int i=mid;i>=low;i--){
		sum+=A[i];
		if(sum>left_sum){
			left_sum=sum;
			max_left=i;
		}
	}
	int right_sum=INT_MIN;
	sum=0;
	for(int j=mid+1;j<=high;j++){
		sum+=A[j];
		if(sum>right_sum){
			right_sum=sum;
			max_right=j;
		}
	}
	tuple<int,int,int> result;
	get<0>(result)=max_left;
	get<1>(result)=max_right;
	get<2>(result)=left_sum + right_sum;
	return result;	
}

tuple<int,int,int> find_max_subarray(vector<int>& A,int low,int high){
	if(N<100)
		return max_subarray_n2(A);
	if (high==low){
		tuple<int,int,int> base_case;
		get<0>(base_case)=low;
		get<1>(base_case)=high;
		get<2>(base_case)=A[low];
		return base_case;
	}
	else{
		int mid=floor((low+high)/2);
		tuple<int,int,int> left_sub = find_max_subarray(A,low,mid);
		tuple<int,int,int> right_sub = find_max_subarray(A,mid+1,high);
		tuple<int,int,int> cross_sub = find_max_crossing_subarray(A,low,mid,high);
		int left_sum=get<2>(left_sub);
		int right_sum=get<2>(right_sub);
		int cross_sum=get<2>(cross_sub);
		if(left_sum>=right_sum && left_sum>=cross_sum)
			return left_sub;
		else if(right_sum>=left_sum && right_sum>=cross_sum)
			return right_sub;
		else
			return cross_sub;
	}
}

/*--------------------------------*/

/*This version has complexity O(n^2)*/
tuple<int,int,int> max_subarray_n2(vector<int>& A){
	int max_sum = INT_MIN,right,left;
	for(int i=0;i<A.size();i++){
		int sum=0;
		for(int j=i;j<A.size();j++){
			sum+=A[j];
			if(sum>max_sum){
				max_sum=sum;
				left=i;
				right=j;
			}
		}	
	}
	tuple<int,int,int> result;
	get<0>(result) = left;
	get<1>(result) = right;
	get<2>(result) = max_sum;
	return result;
}
/*--------------------------------------------*/

/*This version is the best. Has O(n) complexity.*/
tuple<int,int,int> max_subarray_n(vector<int>& A){
	int max_sum = INT_MIN;
	int sum=0;
	int high,low;
	for(int i=0;i<A.size();i++){
		sum+=A[i];
		if(sum>max_sum){
			max_sum=sum;
			high=i;
		}
		if(sum<0)
			sum=0;
	}
	sum=0;
	for(int k=high;k>=0;k--){
		sum += A[k];
		if(sum==max_sum){
			low=k;
			break;
		}
	}
	tuple<int,int,int> result;
	get<0>(result) = low;
	get<1>(result) = high;
	get<2>(result) = max_sum;
	return result;
}

int main(){
	
	srand(time(NULL));
	vector<int> arr;
	for(int i=0;i<N;i++)
		arr.push_back((rand() % 100) - 50);

	/*Recursive benchmark*/ 
	auto start = get_time::now();
	tuple<int,int,int> end_result1 = find_max_subarray(arr,0,arr.size()-1);
	auto end = get_time::now();
	auto differ = end - start;
	cout<<get<0>(end_result1)<<" to "<<get<1>(end_result1)<<" -> max: "<<get<2>(end_result1)<<endl;
	cout<<"Elapsed time for recursive approach is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	/*-------------------*/

	/*Polynomial benchmark*/
	start = get_time::now();
	tuple<int,int,int> end_result2=max_subarray_n2(arr);		
	cout<<get<0>(end_result2)<<" to "<<get<1>(end_result2)<<" -> max: "<<get<2>(end_result2)<<endl;
	end = get_time::now();
	differ = end - start;
	cout<<"Elapsed time for brute-force approach is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	/*--------------------*/
	
	/*Linear benchmark*/
	start = get_time::now();
	tuple<int,int,int> end_result3=max_subarray_n(arr);		
	cout<<get<0>(end_result3)<<" to "<<get<1>(end_result3)<<" -> max: "<<get<2>(end_result3)<<endl;
	end = get_time::now();
	differ = end - start;
	cout<<"Elapsed time for linear approach is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}	
	
