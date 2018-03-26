#include <iostream>
#include "tree.hpp"

using namespace std;

/* Compile using
 * 
 *  g++ -o p1ex01 main_tree_ex01.cpp -ansi -pedantic -Wall
 *
 * Run
 *
 *  ./p1ex01 >p1ex01.out
 *
 * Compare your p1ex01.out with the given one.
 *
 */  

template <> //specialized for int Tree on less<int> comparison
void
Tree<int,less<int> >::print( TreeNode * t ) const
{
  if( t->left != NULL )
  {
    cout << '[';
    print( t->left );
  }
  else if( t->left == NULL && t->right != NULL )
  {
    cout << "[";
  }

  if( t != NULL )
  {
    if( isLeaf( t ) )
    {
      cout << "({";
      if( t->element == NULL )
        cout << '-';
      else
        cout << *(t->element);
      cout << ",P";
      if( t->element == NULL )
        cout << '-';
      else if( t->parent->element == NULL )
        cout << '-';
      else
        cout << *(t->parent->element);
      cout << "}H" << t->height;
      cout << ')';
    }
    else
    {
      cout << "({";
      if( t->element == NULL )
        cout << '-';
      else
        cout << *(t->element);
      cout << ",P";
      if( t->parent == NULL )
        cout << '-';
      else if( t->parent->element == NULL )
        cout << '-';
      else
        cout << *(t->parent->element);
      cout << ",L";
      if( t->left == NULL )
        cout << '-';
      else if( t->left->element == NULL )
        cout << '-';
      else
        cout << *(t->left->element);
      cout << ",R";
      if( t->right == NULL ) 
        cout << '-';
      else if( t->right->element == NULL )
        cout << '-';
      else
        cout << *(t->right->element);
      cout << "}H" << t->height;
      cout << ')';
    }
  }

  if( t->right != NULL )
  {
    print( t->right );
    cout << ']';
  }
  else if( t->left != NULL && t->right == NULL )
  {
    cout << "]";
  }
}

void printInfo( const Tree<int> & tr )
{
  int idealHeight = log2( tr.getSize( ) );
  cout << "Current height is " << tr.getHeight( ) 
       << "; ideal height is " << idealHeight 
       << " since size is " << tr.getSize( ) 
       << " and the tree content is as follows: " << endl;
}

int main( void )
{
  list<int> v;
 
  for(int i=1;i<=7;i++)
  {
    v.push_back(i);
  }

  Tree<int> tDat( v );
  
  list<int>::const_iterator itr = v.end( );
  
  printInfo( tDat );

  tDat.print( );
  
  --itr;
  cin.get();
  /*const int * p;
  p = tDat.getAddress(26);
  cout<<"address is :"<<p<<endl;
  cout<<"value is :"<<*p<<endl;*/
  v.push_back( 9 );
  v.push_back( -10 );
  v.push_back( 11 );
  v.push_back( -12 );
  v.push_back( 14 );
  v.push_back( 50 );
  v.push_back( 60 );
  v.push_back( 70 );
  
  
  for( int i = 0; i < 8; ++i )
  {
    ++itr;
    tDat.insert( &(*itr) );
    printInfo( tDat );
    tDat.print( );
    cin.get();
  }

  int toRemove[ 4 ] = { 6, 50, 4, 5 };

  for( int i = 0; i < 4; ++i )
  {
    tDat.remove( toRemove + i );
    printInfo( tDat );
    tDat.print( );
  }

  return 0;
}
