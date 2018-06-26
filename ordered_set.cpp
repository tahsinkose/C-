#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>


using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main(){
	ordered_set o_set;
	o_set.insert(2);
	o_set.insert(3);
	o_set.insert(7);

	cout<<*(o_set.find_by_order(1))<<endl;
	cout<<o_set.order_of_key(4)<<endl;

	cout<<o_set.order_of_key(5)<<endl;

	return 0;
}	
