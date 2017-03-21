#include "musiclist.hpp"

MusicList::MusicList( )
//complete the body

MusicList::MusicList( const list<Song> & s )
//Complete the body of the constructor

MusicList::~MusicList( )
//erase all nodes with deleted status before total destruction

void
MusicList::insert( const string & nm, const string & bd,
                   int year, size_t duration )
{
  //complete the body
}

void
MusicList::remove( const string & nm, const string & bd,
                   int year )
{
  //complete the body
}

int
MusicList::getNumberOfSongs( ) const
{
  //complete the body
}

void
MusicList::printAllNameSorted( ) const
{
  //complete the body
}

void
MusicList::printAllYearSorted( ) const
{
  //complete the body
}

void
MusicList::printNameRange( const string & lower,
                           const string & upper ) const
{
  //complete the body
}


void
MusicList::printYearRange( int lower, int upper ) const
{
  //complete the body
}