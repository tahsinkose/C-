/*For f(i, j) = i and g(i) = min(j), there must exist a cycle of length min(j) 
  beginning from index i and ending at the same index i of permutation P. 
  While generating a permutation P, we are constrained to generate cycles of length 
  either A or B as g(i) for all 1 ≤ i ≤ N must be equal to either of them.
*/

/* A couple of examples to cycle generation method resides below. In fact, it is a general method.
   P_before = 1 2 3 4
   ------- becomes after applying P[i] = i + k -1 to ith indice and P[j] = j-1 for the rest. 
   P_after = 4 1 2 3

   Let's see for first element. 4-3-2-1-4 => A cycle of length 4

   P_before = 2 1 4 3 5 6 7 8 9
   ---------
   P_after = 2 1 4 3 6 7 8 9 5
	
  6-7-8-9-5-6 => A cycle of length 5.
  [5]-[6]-[7]-[8]-[9]-[5] -> indices
 */
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

ostream& operator <<(ostream& os,const vector<int>& v){
	for(int i=0;i<v.size();i++)
		os<<v[i]<<" ";
	return os;
}

void rotate_(vector<int>& arr,int i,int k){
	arr[i] = i + k;
	//cout<<"arr["<<i<<"]: "<<arr[i]<<endl;
	for(int l=i+1;l<i+k;l++)
		arr[l] = l;
}

int main(){
	auto start = get_time::now();
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int N,A,B;
	cin>>N>>A>>B;
	vector<int> arr(N);
	for(int i=0;i<N;i++)
		arr[i] = i + 1;
	int i=0;
	while(i<N){
		if((N-i)%B==0){
			//rotate(arr.begin()+i,arr.begin()+i+1,arr.begin()+i+B);
			rotate_(arr,i,B);
			i+=B;
		}
		else{
			if(i+A>N){ // Ax + By = N does not have a solution pair (x,y) in the domain of integers. 
					   // Therefore permutation cannot be constructed based on these sole cycles.
				cout<<-1<<endl;
				return 0;
			}
			//rotate(arr.begin()+i,arr.begin()+i+1,arr.begin()+i+A);
			rotate_(arr,i,A);
			i+=A;
		}
	}
	cout<<arr<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}