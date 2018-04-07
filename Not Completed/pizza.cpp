#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <tuple>
using namespace std;

#define MAX 1010
#define ft first
#define sd second

int n, m, l, h; char s[MAX][MAX];
pair < int, int > p[MAX][MAX][4];
int sm[MAX][MAX], st[MAX][MAX];
vector < tuple < int, int, int, int > > rec;
 

int mushrooms ( int x0, int y0, int x1, int y1 )
	{return sm[x1][y1]-sm[x1][y0]-sm[x0][y1]+sm[x0][y0];}


int tomatos ( int x0, int y0, int x1, int y1 )
	{return st[x1][y1]-st[x1][y0]-st[x0][y1]+st[x0][y0];}

pair < int, pair < int, int > > b ( int x0, int y0, int x1, int y1, int depth )
{
	
	pair < int, pair < int, int > > ans { 0, { -1, -1 } };
	cout << "b(" << x0 << " " << y0 << " " << x1 << " " << y1 << ")\n";
	if (x0==x1 || y0 ==y1)
		return {0, {-2,-2}};

	for ( int i = x0; i < x1; ++ i )
	{
		for ( int j = y0; j < y1; ++ j )
		{
			if ( i == x0 && j == y0 ) continue;
			int sum = 0; pair < int, int > A {-1,-1}, B{-1,-1}, C{-1,-1}, D{-1,-1};
			if ( mushrooms ( x0, y0, i, j ) >= l && tomatos ( x0, y0, i, j ) >= l && (i-x0)*(j-y0) <= h )
				sum += (i-x0)*(j-y0);
			else
			{
				pair < int, pair < int, int > > bb = b ( x0, y0, i, j, depth+1 );
				sum += bb.ft; A = bb.sd;
			}
			
			if ( mushrooms ( x0, j, i, y1 ) >= l && tomatos ( x0, j, i, y1 ) >= l && (i-x0)*(y1-j) <= h )
				sum += (i-x0)*(y1-j);
			else
			{
				pair < int, pair < int, int > > bb = b ( x0, j, i, y1, depth+1 ); 
				sum += bb.ft, B = bb.sd;
			}

			if ( mushrooms ( i, y0, x1, j ) >= l && tomatos ( i, y0, x1, j ) >= l && (x1-i)*(j-y0) <= h )
				sum += (x1-i)*(j-y0);
			else
			{
				pair < int, pair < int, int > > bb = b ( i, y0, x1, j, depth+1 );
				sum += bb.ft, C = bb.sd;
			}

			if ( mushrooms ( i, j, x1, y1 ) >= l && tomatos ( i, j, x1, y1 ) >= l && (x1-i)*(y1-j) <= h )
				sum += (x1-i)*(y1-j);
			else
			{
				pair < int, pair < int, int > > bb = b ( i, j, x1, y1, depth+1 );
				sum += bb.ft, D = bb.sd;
			}

			if ( sum > ans.ft )
			{
				cout<<"Recording new sum in ("<<i<<","<<j<<"): "<<sum<<endl;
				cout<<"Old sum: "<<ans.ft<<endl;
				ans.ft = sum; ans.sd = { i, j };
				p[i][j][0] = A;
				p[i][j][1] = B;
				p[i][j][2] = C;
				p[i][j][3] = D;		
			}
		}
	}

	return ans;
}

void output ( int x0, int y0, int x1, int y1, int x, int y )
{
	cout << "In the range ["<<x0 << "-" << y0 << "][" << x1 << "-" << y1 << "] with leap point : (" << x << "," << y <<")"<< endl;
	cout<< "Leap point ("<<x<<","<<y<<") Surrounding information:"<<endl;
	cout << "A " << p[x][y][0].ft << " " << p[x][y][0].sd << endl;
	cout << "B " << p[x][y][1].ft << " " << p[x][y][1].sd << endl;
	cout << "C " << p[x][y][2].ft << " " << p[x][y][2].sd << endl;
	cout << "D " << p[x][y][3].ft << " " << p[x][y][3].sd << endl;
	cout << endl << endl;

	if ( x0 == x1 || y0 == y1 ) return;
	if ( p[x][y][0].ft == -1 ) rec.push_back ( make_tuple(x0, y0, x, y ) );
	else output ( x0, y0, x, y, p[x][y][0].ft, p[x][y][0].sd );

	if ( p[x][y][1].ft == -1 ) rec.push_back ( make_tuple(x0, y, x, y1 ) );
	else output ( x0, y, x, y1, p[x][y][1].ft, p[x][y][1].sd );
	
	if ( p[x][y][2].ft == -1 ) rec.push_back ( make_tuple(x, y0, x1, y ) );
	else output ( x, y0, x1, y, p[x][y][2].ft, p[x][y][2].sd );

        if ( p[x][y][3].ft == -1 ) rec.push_back ( make_tuple( x, y, x1, y1 ) );
	else output ( x, y, x1, y1, p[x][y][3].ft, p[x][y][3].sd );
}


int main ()
{
	freopen ( "input", "r", stdin );
	ios_base::sync_with_stdio ( 0 );
	
	cin >> n >> m >> l >> h;
	for ( int i = 0; i < n; ++ i )
		for ( int j = 0; j < m; ++ j ) cin >> s[i][j];

	sm[1][1] = (s[0][0]=='M'); st[1][1] = (s[0][0]=='T');

	// Prefix sum for tomatos and mushrooms
	for ( int i = 1; i <= n; ++ i )
	{
		for ( int j = 1; j <= m; ++ j )
		{
			if ( i == 1 && j == 1 ) continue;
			sm[i][j] = sm[i-1][j] + sm[i][j-1] - sm[i-1][j-1] + (s[i-1][j-1]=='M');
			st[i][j] = st[i-1][j] + st[i][j-1] - st[i-1][j-1] + (s[i-1][j-1]=='T');	
		}
	}

	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++)
			cout<<st[i][j]<<" ";
		cout<<endl;
	}

	//....
	pair < int, pair < int, int > > bb = b ( 0, 0, n, m, 0 );
	cout << bb.ft << "  " << bb.sd.ft << " " << bb.sd.sd << endl;
	//...output of search
	
	output ( 0, 0, n, m, bb.sd.ft, bb.sd.sd );
	
	cout << rec.size () << endl;
	for ( int i = 0; i < (int)rec.size (); ++ i )
		cout << get<0>(rec[i]) << " " << get<1>(rec[i]) << " " <<
			 get<2>(rec[i]) << " " << get<3>(rec[i]) << "\n";

	return 0;
}
