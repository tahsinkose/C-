#include <iostream>
#include <vector>
#include <typeinfo>

#define X(A) A[0][0]
using namespace std;

// Overloaded output operator for pretty matrix output.
template < class T >
std::ostream& operator << (ostream& os, const vector<T>& v) 
{
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

vector<vector<int> > operator+ (vector<vector<int> >& lhs,vector<vector<int> >& rhs){
	vector<vector<int> > C(lhs.size(),vector<int>(lhs.size()));
	for(int i=0;i<lhs.size();i++)
		for(int j=0;j<lhs[i].size();j++)
			C[i][j]=lhs[i][j] + rhs[i][j];
	return C;
}
vector<vector<int> > sub(vector<vector<int> >& A, int a_i,int a_j,vector<vector<int> >& B,int b_i,int b_j){
	int n=A.size();	
	vector<vector<int> > C(n/2,vector<int>(n/2));
	
	int i=0,x=a_i,l=b_i;
	do{
		int j=0;
		int y=a_j,m=b_j;
		do{
			C[i][j++] = A[x][y] - B[l][m];
			y++;
			m++;
		}while(y%(n/2)!=0);
		x++;
		l++;
		i++;
	}while(x%(n/2)!=0);

	return C;
}

vector<vector<int> > sum(vector<vector<int> >& A, int a_i,int a_j,vector<vector<int> >& B,int b_i,int b_j){
	int n=A.size();	
	vector<vector<int> > C(n/2,vector<int>(n/2));
	
	int i=0,x=a_i,l=b_i;
	do{
		int j=0;
		int y=a_j,m=b_j;
		do{
			C[i][j++] = A[x][y] + B[l][m];
			y++;
			m++;
		}while(y%(n/2)!=0);
		x++;
		l++;
		i++;
	}while(x%(n/2)!=0);

	return C;
}

vector<vector<int> > multiply(vector<vector<int> >& A,vector<vector<int> >& B,int sub_i,int sub_j,bool side){
	if(side){	
		int n=A.size();	
		vector<vector<int> > C(n/2,vector<int>(n/2));
		
		C[0][0] = A[sub_i][sub_j] * B[0][0];
		return C;
	}
	else{
		int n=B.size();	
		vector<vector<int> > C(n/2,vector<int>(n/2));
		C[0][0] = A[0][0] * B[sub_i][sub_j];
		return C;
	}
}


vector< vector<int> > strassen(vector< vector<int> >& A,vector< vector<int> >& B,int low,int high){
	int n=A.size();
	vector< vector<int> > C(n,vector<int>(n));
	
	/*----- S Matrices Declarations-------*/
	int sub_size = n/2;
	vector< vector<int> > S1(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S2(sub_size,vector<int>(sub_size));
	vector< vector<int> > S3(sub_size,vector<int>(sub_size));
	vector< vector<int> > S4(sub_size,vector<int>(sub_size));
	vector< vector<int> > S5(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S6(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S7(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S8(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S9(sub_size,vector<int>(sub_size));	
	vector< vector<int> > S10(sub_size,vector<int>(sub_size));
	/*------------------------------------*/
	/*----- S Matrices Definitions--------*/
	int mid=(low+high)/2;
	S1 = sub(B,0,mid,B,mid,mid);
	S2 = sum(A,0,0,A,0,mid);
	S3 = sum(A,mid,0,A,mid,mid);
	S4 = sub(B,mid,0,B,0,0);
	S5 = sum(A,0,0,A,mid,mid);
	S6 = sum(B,0,0,B,mid,mid);
	S7 = sub(A,0,mid,A,mid,mid);
	S8 = sum(B,mid,0,B,mid,mid);
	S9 = sub(A,0,0,A,mid,0);
	S10 = sum(B,0,0,B,0,mid);	
	/*------------------------------------*/
	/*------------- P Matrices Declarations--------*/
	vector< vector<int> > P1(sub_size,vector<int>(sub_size));	
	vector< vector<int> > P2(sub_size,vector<int>(sub_size));
	vector< vector<int> > P3(sub_size,vector<int>(sub_size));
	vector< vector<int> > P4(sub_size,vector<int>(sub_size));
	vector< vector<int> > P5(sub_size,vector<int>(sub_size));	
	vector< vector<int> > P6(sub_size,vector<int>(sub_size));	
	vector< vector<int> > P7(sub_size,vector<int>(sub_size));
	/*---------------------------------------------*/
	if(n>2){
		
		P1 = strassen(A,S1,low,mid);
		P2 = strassen(S2,B,mid,high);
		P3 = strassen(S3,B,low,mid);
		P4 = strassen(A,S4,mid,high);
		P5 = strassen(S5,S6,0,subsize);
		P6 = strassen(S7,S8,0,subsize);
		P7 = strassen(S9,S10,0,subsize);
		/*partial_sum(C,low,low,P5+P4-P2+P6);
		partial_sum(C,low,mid,P1+P2);
		partial_sum(C,mid,low,P3+P4);
		partial_sum(C,mid,mid,P5+P1-P7);*/
	}
	else{
		P1 = multiply(A,S1,low,low,true);
		P2 = multiply(S2,B,mid,mid,false);
		P3 = multiply(S3,B,low,low,false);
		P4 = multiply(A,S4,mid,mid,true);
		X(P5) = X(S5)*X(S6);
		
		P6[0][0] = X(S7)*X(S8);
		X(P7) = X(S9)*X(S10);
		C[0][0] = X(P5) + X(P4) - X(P2) + X(P6);
		C[0][1] = X(P1) + X(P2);
		C[1][0] = X(P3) + X(P4);
		C[1][1] = X(P5) + X(P1) - X(P3) - X(P7);
	}
	return C;
	
}
int main(){
	vector< vector<int> > A = {{1,3},{7,5}};
	vector< vector<int> > B = {{6,8},{4,2}};
	int n=A.size();
	vector< vector<int> > C = strassen(A,B,0,n);	
	
	for(int i=0;i<C.size();i++)
		cout<<C[i]<<endl;
	
	
	return 0;

}
