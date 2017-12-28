#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

template <class T>
void printVector(vector<T> arr){
	for(int i=0;i<arr.size();i++)
		cout<<arr[i]<<endl;
	cout<<endl;
}

bool search(string& v,string& w){
	for(int i=0;i<v.size();i++){
		if(v[i]<w[i])
			return true;
		else if(v[i]>w[i])
			return false;
		else
			continue;
	}
	return false;
}

void merge(vector<string>& A,int p,int q ,int r,vector<int>& A_len){
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<string> L;
	vector<string> R;
	vector<int>L_len;
	vector<int>R_len;
	for(int i=0;i<n1;i++){
		L.push_back(A[p+i]);
		L_len.push_back(A_len[p+i]);
	}
	/*cout<<"L: "<<endl;
	printVector(L);
	cout<<"L-size: "<<endl;
	printVector(L_len);
	*/
	
	for(int j=0;j<n2;j++){
		R.push_back(A[q+j+1]);
		R_len.push_back(A_len[q+j+1]);
	}
	/*
	cout<<"R: "<<endl;
	printVector(R);
	cout<<"R-size: "<<endl;
	printVector(R_len);
	*/
	int i=0,j=0,k=p;
	while(i!=n1 && j!=n2){
		if(L_len[i]<R_len[j]){
			A[k] = L[i];
			A_len[k] = L_len[i];
			i++;
		}
		else if(R_len[j]<L_len[i]){
			A[k] = R[j];
			A_len[k] = R_len[j];
			j++;
		}
		else{//Lengths are equal. Recursively search for smaller char.
			bool left = search(L[i],R[j]);
			if(left){
				A[k] = L[i];
				A_len[k] = L_len[i++];
			}
			else{
				A[k] = R[j];
				A_len[k] = R_len[j++];
			}		
		}
		k++;
	}
	for(int ii=i;ii<n1;ii++){
		A[k] = L[ii];
		A_len[k++] = L_len[ii];
	}

	for(int jj=j;jj<n2;jj++){
		A[k] = R[jj];
		A_len[k++] = R_len[jj];
	}
}

void merge_sort(vector<string>& A,int p,int r,vector<int>& A_len){
	if(p<r){
		int q = (p + r) / 2;
		merge_sort(A,p,q,A_len);
		merge_sort(A,q+1,r,A_len);
		merge(A,p,q,r,A_len);
	}
}

int main(){
	int n;
	cin>>n;
	vector<string> unsorted(n);
	vector<int> unsorted_length(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       cin >> unsorted[unsorted_i];
	   unsorted_length[unsorted_i] = unsorted[unsorted_i].size();
    }

	merge_sort(unsorted,0,n-1,unsorted_length);
	for(int i=0;i<n;i++)
		cout<<unsorted[i]<<endl;

	return 0;
}
