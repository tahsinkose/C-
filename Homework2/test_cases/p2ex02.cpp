#include <iostream>
#include "tree.hpp"

using namespace std;

/*
 * > g++ p2ex02.cpp -pedantic -ansi -Wall
 *
 * > ./a.out >p2.out
 */

const double scaleFactor = 1.0;

template <>
void
Tree<double,greater<double> >::print( TreeNode * t ) const
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

void printInfo( const Tree<double,greater<double> > & tr )
{
  int idealHeight = log2( tr.getSize( ) );
  cout << "Current height is " << tr.getHeight( ) 
       << "; ideal height is " << idealHeight 
       << " since size is " << tr.getSize( ) 
       << " and the tree content is as follows: " << endl;
}

int main( void )
{
  list<double> v;
  v.push_back( 1 / scaleFactor );
  v.push_back( 2 / scaleFactor );
  v.push_back( 3 / scaleFactor );
  v.push_back( 4 / scaleFactor );
  v.push_back( 5 / scaleFactor );
  v.push_back( 6 / scaleFactor );
  v.push_back( 7 / scaleFactor );

  v.sort( greater<double>( ) );

  Tree<double,greater<double> > tDat( v );
  list<double>::const_iterator itr = v.end( );

  printInfo( tDat );
  tDat.print( );

  --itr;

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
  }

  double toRemove[ 4 ] = { 6, 50, 4, 5 };

  for( int i = 0; i < 4; ++i )
  {
    tDat.remove( toRemove + i );
    printInfo( tDat );
    tDat.print( );
  }

  double toInsert[ 16 ] = {32, 43, 443, -35, 435, 41, 7664, 465436, 5765,
                          -246523, -4562, -4564, 546, -546, -353, -4365426};

  itr = v.end( );

  --itr;

  for( int i = 0; i < 16; ++i )
    v.push_back( toInsert[ i ] ); 

  for( int i = 0; i < 16; ++i )
  {
    ++itr;
    tDat.insert( &(*itr) );
    printInfo( tDat );
    tDat.print( );
  }

  for( int i = 15; i > 7; --i )
  {
    tDat.remove( toInsert + i );
    printInfo( tDat );
    tDat.print( );
  }

  for( int i = 0; i < 8; ++i )
  {
    tDat.remove( toInsert + i );
    printInfo( tDat );
    tDat.print( );
  }

  return 0;
}

