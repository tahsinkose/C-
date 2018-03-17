#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <stack>
int score;
class Object {
		public:
			int y_1;
			int m_1;
			int x_1;
			Object(int y=0,int m=0,int x =0){
				y_1=y;
				m_1=m;
				x_1=x;
			}
};
unsigned long long int result = 0;
using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;
    

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
      std::hash<T> hasher;
      seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
     
namespace std
{
    template<typename S, typename T> struct hash<pair<S, T>>
    {
        inline size_t operator()(const pair<S, T> & v) const
        {
          size_t seed = 0;
          ::hash_combine(seed, v.first);
          ::hash_combine(seed, v.second);
          return seed;
        }
     };
}

std::unordered_map<std::pair<int,int>, unsigned long long int> collect_results;
bool find_function(int y,int m,unsigned long long int *p)
{
	std::unordered_map<std::pair<int,int>, unsigned long long int>::const_iterator itr = collect_results.find(make_pair(y,m));
	if(itr == collect_results.end())
		return false;
	else
		*p=itr->second;
	return true;

}

void insert_function(int y,int m,unsigned long long int r)
{
	collect_results[std::make_pair(y,m)] = r;
}
unsigned long long int F(int y,int m,int M[]){
	unsigned long long int res = 0;
	unsigned long long int *p = &res;
	if(find_function(y,m,p))
		return res;
	else
	{
		int x,limit=M[m-1],m0=M[0];
		bool y_flag = y > limit;
		if(m>1)
		{
			if(y_flag)
			{
				if(m-1==1)
				{
					if(m0>=y)
						res+=limit + 1;
					else if(m0>=y-limit)
						res+=limit - (y-m0) + 1;
					insert_function(y,m,res);
					return res;
				}
				else
					for(x=0;x<=limit;x++)
						res = res + F(y-x,m-1,M);
			}
			else
			{
				if(m-1==1)
				{
					if(m0>=y)
						res+=y+1;
					else
						res+=m0+1;
					insert_function(y,m,res);
					return res;
				}
				else
					for(x=0;x<=y;x++)
						res = res + F(y-x,m-1,M);
			}
			//cout<<"res :"<<res<<" F("<<y<<","<<m<<")"<<endl;
			if(res>1000000000+7)
				res %= 1000000000+7;
			insert_function(y,m,res);
			return res;
		}
	}//end else
	
}
/*void donest(int size,int range[],int difference){
   int k;
   
   vector<int>  maxes;
   
   for(k=size-1;k>=0;k--)
   		maxes.push_back(range[k]+1);
   sort(maxes.rbegin(),maxes.rend());
   
   const int n = size;
  
	int i[n+1],sum,max_sum=0,tmp; 

	for(k=0;k<size;k++)
		max_sum+=range[k];
	
	for (int a=0; a<n+1; a++) {
	tmp = max_sum - range[a];
	/*if(difference>max_sum)
		i[a] = difference - max_sum;
	else
  		i[a] = 0;
	i[a]=0;
	cout<<i[a]<<" ";
	}
	cout<<endl;	
	//if there are same maxes, just calculate one of them and multiply the others
	int p = 0,in=i[n]; 
	while (in==0) {
		sum = 0;
  	
		for(int a=0;a<n+1;a++)
			sum+=i[a];
		
		if(sum==difference)
			result++;
  	
  		i[0]++;
  		
  		while(i[p]==(maxes[p])) {
		
  	    	i[p]=0;
    		i[++p]++;
		for(int a=0;a<n+1;a++)
			cout<<i[a]<<" ";
		cout<<endl;
		
    		if(p==n)
    		{ in=1;	break;}
    		if(i[p]!=(maxes[p]))
    	  		p=0;
		}
	}
}*/
int main()
{

	int i,N,T,L,M,max_sum=0,min_sum=0,max_diff,min_diff,diff,range_count=0;
	
	int less [20] = {0};
	int more [20] = {0};
	int ranges [20] = {0};
	cin>>T;
	cin>>N;
	score = T;
	for(i=0;i<N;i++)
	{
		cin>>L;
		cin>>M;
		less[i] = L;
		more[i] = M;
		if(M-L!=0)
			ranges[range_count++] = M - L;
	}
	
	
	for(i=0;i<N;i++)
	{
		max_sum += more[i];
		min_sum += less[i];
	}
	
	max_diff= max_sum - T;
	min_diff= T - min_sum;
	if(min_diff<max_diff)
		diff = min_diff;
	else
		diff = max_diff;
	/*cout<<"min_sum : "<<min_sum<<" diff :"<<diff<<endl;
	cout<<"ranges :"<<endl;*/
	sort(ranges, ranges+range_count, greater<int>());
	/*for(i=0;i<range_count;i++)
		cout<<i<<" :"<<ranges[i]<<" ";
	cout<<endl;*/
	
	auto start = get_time::now(); //use auto keyword to minimize typing strokes :)
	
	
	if(min_sum<T)
		result = F(diff,range_count,ranges);
		//donest(N,ranges,diff);// Other approach, not speed enough but well in theory
	else if(min_sum==T)
		result = 1;
	else 
		result = 0;
	
	result = result % (1000000000 + 7);
	cout<<result<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}





