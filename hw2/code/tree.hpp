#ifndef TREE_H__
#define TREE_H__

#include <list>
#include <iostream>
#include <cmath>
#include <functional> //less<T> <-> operator<
//you can #include <queue> and #include <stack> but no other STL

using std::list;
using std::cout;
using std::endl;
using std::less;
using std::cin;
            //function object used for comparison, default value is less
template <typename Comparable, typename Comparator=less<Comparable> >
class Tree
{
public:
  Tree( );  //construct an empty tree
  Tree( const list<Comparable> & ); //construct complete BST with min height based on list vals
  ~Tree( ); //release all dynamically allocated memory
  
  void construct( const list<Comparable> & ); //release own sources and get values from list

  const Comparable * findMin( ) const; //pointer to element that is minimal wrt Comparator, implemented
  const Comparable * findMax( ) const; //pointer to element that is maximal wrt Comparator, implemented

  const Comparable * getAddress( const Comparable & ) const; //find pointer to element with given values

  bool contains( const Comparable * ) const; //does this element with data exists in tree, implemented
  bool isEmpty( ) const; //is the tree empty, implemented
    
  void insert( const Comparable * ); //insert if dereferenced argument's data is not present, update heights of those affected
  void remove( const Comparable * ); //delete if dereferenced argument's data is present, update heights of those affected
  /* DO NOT FORGET TO CHECK BALANCE AND REBALANCE TREE IF NOT BALANCED AFTER INSERTION AND DELETION */

  size_t getSize( ) const; //accessor to size, implemented
  int getHeight( ) const; //accessor  to height, implemented
  bool isBalanced( ) const; //accessor to balanced, implemented

  void print( ) const; //inorder print of dereferenced pointers held in nodes, implemented

  friend class MusicList; //MusicList class can access private parts of Tree

private:
  struct TreeNode  //scope Tree::TreeNode, thus is only public to Tree structure, no non-friend outsiders can see
  {
    const Comparable * element; //adress of the item
    TreeNode * left; //pointer to the root of left subtree
    TreeNode * right; //pointer to the root of right subtree
    TreeNode * parent; //pointer to parent node, pay attention to this!
    size_t height; //height >= 0
    size_t level;
    

    //constructor
    TreeNode( const Comparable * el,
              TreeNode * l, TreeNode * r, 
              TreeNode * p )
      : element( el ), 
        left( l ), right( r ),
        parent( p )
    {
    }
    //you should separately set height values, no constructor is defined for them
  };

  TreeNode * root; //designated root
 
  /* isLessThan( const Comparable & lhs, const Comparable & rhs )
   * returns true if lhs<rhs and false otherwise */
  Comparator isLessThan;
  
  size_t size; //number of nodes
  bool balanced;

  /* uncopiable */
  Tree( const Tree & ); //disabled, provide no implementation
  Tree & operator=( const Tree & ); //disabled, provide no implementation

  /* private utility functions */
  TreeNode * findMin( TreeNode * ) const; //recursively find min in (leftward) subtrees
  TreeNode * findMax( TreeNode * ) const; //recursively find max in (rightward) subtrees
  bool contains( const Comparable *, TreeNode * ) const; //recursively search for an item
  
  bool isLeaf( TreeNode * ) const; //isLeaf
  bool isFull( TreeNode * ) const; //isFull
  void print( TreeNode * ) const; //recursive print
  //define and use more as you may need
  void build(const list<Comparable> &);
  void reduceTreeLevels( TreeNode *);
  int maxHeight(TreeNode *);
  void setHeights(TreeNode *);
  void clear(TreeNode *);
  const Comparable * findValuePtr(const Comparable * , TreeNode * t ) const;
  void insertHelper( const Comparable *,TreeNode *t,TreeNode *p);

  template <typename T>  //templated max
  T max( T x, T y ) { return x > y ? x : y; }
}; //Do not modify method prototypes and data member names

//Below this point you should begin implementing the missing parts
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::Tree( )
{
   root = NULL;
   size = 0;
   balanced = true;
}

template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::Tree( const list<Comparable> & data )
{
  build(data);
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::reduceTreeLevels( TreeNode * t )
{
   if(t==NULL)
      return;
   else
  {
    reduceTreeLevels(t->left);
    t->level -=1;
    reduceTreeLevels(t->right);
  }

  
}

template <typename Comparable, typename Comparator>
int
Tree<Comparable,Comparator>::maxHeight( TreeNode * t )
{
  if(t==NULL)
    return -1;
  else
  {
    int leftHeight =maxHeight(t->left);
    int rightHeight=maxHeight(t->right);

    if(leftHeight > rightHeight)
      return(leftHeight +1);
    else
      return(rightHeight +1);
  }
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::setHeights( TreeNode * t )
{
   if(t==NULL)
      return;
   else
  {
    setHeights(t->left);
    t->height = maxHeight(t);
    setHeights(t->right);
  }

  
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::build( const list<Comparable> & data )
{
   //In here, I must traverse the list thoroughly while creating an inorder traversal of it as a BST.
  if(!data.empty())
  {
    size = data.size(); //assign the size of list to the tree.
    int h=floor(log2(size+1));
    int leaves = size+1 - (1<<h);   
    //cout<<"nodes :"<<size<<" leaves :"<<leaves<<endl<<endl;
    TreeNode * imagNode = new TreeNode(NULL,NULL,NULL,NULL); //construct the imaginary root.
    imagNode->level = 1+ ceil(log2(size));
  
    bool flag = false;
    bool reduced_flag = false;
    list<int>::const_iterator it = data.begin( );
    TreeNode * currentNode = imagNode;
    for(;it!=data.end();++it)
    {
      TreeNode * newNode = new TreeNode(&*it,NULL,NULL,NULL); //new node created
      
      int hold_level;
      if((!currentNode->right && currentNode->left) || (!currentNode->right && currentNode->level!=0))//this means the currentNode is a leaf node. Therefore its right child is level 0(NULL).
        hold_level = 0;//null node
      else if(!currentNode->right && !currentNode->left)
        hold_level = -1; //null nodes' level reduced after last leave.*/
      else 
        hold_level = currentNode->right->level;

      
      
      /*-----------Climb up the tree as long as the height difference between parent and child equals to 1-------------------------*/
      int compare_level = currentNode->level- hold_level;
      //cout<<"compare_level : "<<compare_level<<endl;
      while(compare_level == 1)
      {
        hold_level = currentNode->level;
      currentNode = currentNode->parent;
        compare_level = currentNode->level - currentNode->right->level;
      }
      /*---------------------------------------------------------------------------------------------------------------------------*/
      //cout<<"hold level : "<<hold_level<<endl;
      //Make the substitutions for the new node.
      if(currentNode->right)
        currentNode->right->parent = newNode;
      else if(leaves!=0)
      {
        leaves--;
        //cout<<*it<<" is a leaf, "<<leaves<<" left"<<endl;
        if(!leaves)
        {
          //STEP ALL LEVELS DOWN BY 1
          reduceTreeLevels(imagNode);
          flag = true;
        }
      }
      
      newNode->left = currentNode->right;
      
      currentNode->right = newNode;
      newNode->parent = currentNode;
    if(flag)
      {
        newNode->level = 0;
        
        //happens only once
        flag = false;
        reduced_flag = true;
      }
      else if(reduced_flag)
      {
        newNode->level = hold_level+1;
      }
    else
    {
    newNode->level = hold_level+1;
    
    }
      //End the substitutions for the new node.
      /*cout<<"currentNode->level :"<<currentNode->level<<endl;
      cout<<"currentNode->height :"<<currentNode->height<<endl;
      cout<<"currentNode->address :"<<currentNode<<endl;
      cout<<"currentNode->right :"<<currentNode->right<<endl;
      cout<<"currentNode->left :"<<currentNode->left<<endl;
      cout<<"currentNode->parent :"<<currentNode->parent<<endl<<endl;
      cout<<"newNode->level :"<<newNode->level<<endl;
      cout<<"newNode->height :"<<newNode->height<<endl;
      cout<<"newNode->value :"<<*(newNode->element)<<endl;
      cout<<"newNode->address :"<<newNode<<endl;
      cout<<"newNode->right :"<<newNode->right<<endl;
      cout<<"newNode->left :"<<newNode->left<<endl;
      cout<<"newNode->parent:"<<newNode->parent<<endl;*/

      currentNode = newNode;
      //cin.get();
    }
    root = imagNode->right;
    balanced = true;
  /*Set heights accordingly*/
  setHeights(root);
  }
  
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::construct( const list<Comparable> & data )
{
   clear(root);
   build(data);
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::clear( TreeNode * t )
{
   if(t==NULL)
    return;
   else
   {
    clear(t->left);
    clear(t->right);
    delete t;
   
   }
}
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::~Tree( )
{
  //Implement
  
  clear(root);  
  root = NULL;

}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::insert( const Comparable * data )
{
  //Implement
  insertHelper(data,NULL,root);
  size++;
  //Take the data from tree inorder.
  list<Comparable>* newData = new list<Comparable>();
  TreeNode * tmp = root;
  create_list(newData,tmp);
  
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::create_list(list<Comparable>* newList,TreeNode *t)
{
  create_list(newList,root->left);
  newList.push_back(*(root->element))
  create_list(newList,root->right);
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::insertHelper(const Comparable * data,TreeNode *parent,TreeNode* child)
{
  if(child==NULL)
  {  
    child = new TreeNode(data,NULL,NULL,NULL);
    child->parent = parent;
    child->height = 0;
    child->level = 1;
    /*  cout<<"currentNode->level :"<<child->level<<endl;
      cout<<"currentNode->height :"<<child->height<<endl;
      cout<<"currentNode->value :"<<*(child->element)<<endl;
      cout<<"currentNode->address :"<<child<<endl;
      cout<<"currentNode->right :"<<child->right<<endl;
      cout<<"currentNode->left :"<<child->left<<endl;
      cout<<"currentNode->parent :"<<child->parent<<endl<<endl;

      cout<<"parentNode->level :"<<parent->level<<endl;
      cout<<"parentNode->height :"<<parent->height<<endl;
      cout<<"parentNode->value :"<<*(parent->element)<<endl;
      cout<<"parentNode->address :"<<parent<<endl;
      cout<<"parentNode->right :"<<parent->right<<endl;
      cout<<"parentNode->left :"<<parent->left<<endl;
      cout<<"parentNode->parent:"<<parent->parent<<endl;*/
  }
  else if( *data < *(child->element))
    insertHelper(data,child,child->left);
  else if( *data > *(child->element))
    insertHelper(data,child,child->right);
  else
    ;
}
template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::remove( const Comparable * data )
{
  //Implement

}

template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::findMin( ) const
{
  if( isEmpty( ) )
    return NULL;
  
  return findMin( root )->element; //call in to recursive utility function
}

template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::findMax( ) const
{
  if( isEmpty( ) )
    return NULL;
  
  return findMax( root )->element;
}

template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::getAddress( const Comparable & item ) const
{ 
  const Comparable * itemPtr = &item;
  //cout<<*itemPtr<<" is in the list"<<endl;
  const Comparable * tmp = findValuePtr(itemPtr,root);
  return tmp;

}


template <typename Comparable, typename Comparator>
const Comparable *
Tree<Comparable,Comparator>::findValuePtr( const Comparable * item, 
                                           TreeNode * t ) const
{
  if( t == NULL )
    return NULL;
  else if( isLessThan( *item, *(t->element) ) )
    return findValuePtr( item, t->left );
  else if( isLessThan( *(t->element), *item ) )
    return findValuePtr( item, t->right );
  else
    return t->element;
}


template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::contains( const Comparable * item ) const
{  
  return contains( item, root );
}

template <typename Comparable, typename Comparator>
size_t
Tree<Comparable,Comparator>::getSize( ) const
{
  return size;
}

template <typename Comparable, typename Comparator>
int
Tree<Comparable,Comparator>::getHeight( ) const
{
  if( isEmpty( ) )
    return -1;  //convention: empty tree has height -1
  else
    return root->height; //>= 0
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isEmpty( ) const
{
  return ( root == NULL );
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::print( ) const
{
  print( root );
  cout << endl;  
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isBalanced( ) const
{
  return balanced;
}

/* private utility functions 
 * define and use as many as you deem required
 * some are provided for the already implemented 
 * part of the public interface
 */
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode *
Tree<Comparable,Comparator>::findMin( TreeNode * t ) const
{
  if( t == NULL )
    return NULL;

  if( t->left == NULL )
    return t;

  return findMin( t->left );
}

template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode *
Tree<Comparable,Comparator>::findMax( TreeNode * t ) const
{
  if( t != NULL )
    while( t->right != NULL )
      t = t->right;
  return t;
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::contains( const Comparable * item, 
                                           TreeNode * t ) const
{
  if( t == NULL )
    return false;
  else if( isLessThan( *item, *(t->element) ) )
    return contains( item, t->left );
  else if( isLessThan( *(t->element), *item ) )
    return contains( item, t->right );
  else
    return true;
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isLeaf( TreeNode * t ) const
{
  return ( ( t->left == NULL ) && ( t->right == NULL ) );
}

template <typename Comparable, typename Comparator>
bool
Tree<Comparable,Comparator>::isFull( TreeNode * t ) const
{
  return ( ( t->left != NULL ) && ( t->right != NULL ) );
}

template <typename Comparable, typename Comparator>
void
Tree<Comparable,Comparator>::print( TreeNode * t ) const
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
      cout << '(' << *( t->element ) << ')';
    }
    else if( !isLeaf( t ) )
    {
      cout << *( t->element );
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

#endif