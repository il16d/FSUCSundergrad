/*
    map_adt.h
   
    March 5th, 2017
*/

#ifndef _MAP_ADT_H
#define _MAP_ADT_H

#include <cstddef>    // size_t
#include <iostream>
#include <iomanip>
#include <compare.h>  // LessThan
#include <queue.h>    // used in Dump()
#include <stack.h>
#include <list.h>
#include <vector.h>
#include <debug.h>
#include <ansicodes.h>
#include <entry.h>
#include <mapiter_adt.h>
#include <pair.h>

namespace fsu
{
  template < typename K , typename D , class P >
  class Map_ADT;

  template < typename K , typename D , class P > 
  bool operator == (const Map_ADT<K,D,P>& map1, const Map_ADT<K,D,P>& map2);

  template < typename K , typename D , class P > 
  bool operator != (const Map_ADT<K,D,P>& map1, const Map_ADT<K,D,P>& map2);

  template < typename K , typename D , class P >
  class Map_ADT;

  template < typename K , typename D , class P = LessThan<K> >
  class Map_ADT
  {
  public:

    // family ties
    friend class ConstInorderMapIterator < fsu::Map_ADT<K,D,P> >;
    friend class InorderMapIterator      < fsu::Map_ADT<K,D,P> >;
    friend class LevelorderMapIterator   < fsu::Map_ADT<K,D,P> >;

    // terminology support
    typedef K                                      KeyType;
    typedef D                                      DataType;
    typedef P                                      PredicateType;
    typedef fsu::Entry<K,D>                        EntryType;
    typedef InorderMapIterator < Map_ADT <K,D,P> > Iterator;
    typedef ConstInorderMapIterator < Map_ADT <K,D,P> > ConstIterator;

    // iterator support
    Iterator      Begin  ();
    Iterator      End    ();
    Iterator      rBegin ();
    Iterator      rEnd   ();
    Iterator      Includes(const KeyType& k);
    ConstIterator Includes(const KeyType& k) const;
    ConstIterator Begin  () const;
    ConstIterator End    () const;
    ConstIterator rBegin () const;
    ConstIterator rEnd   () const;

    // special iterators
    typedef LevelorderMapIterator   < Map_ADT <K,D,P> > LevelorderIterator;
    LevelorderIterator BeginLevelorder   () const;
    LevelorderIterator EndLevelorder     () const;

    // structural iterator support
    ConstIterator BeginStructuralInorder () const;

             Map_ADT  ();
    explicit Map_ADT  (P p);
             Map_ADT  (const Map_ADT& a);
             ~Map_ADT ();
    Map_ADT& operator=(const Map_ADT& a);

    DataType& operator [] (const KeyType& k)        { return Get(k); }

    void Put (const KeyType& k , const DataType& d) { Get(k) = d; }
    D&   Get (const KeyType& k);

    void Erase(const KeyType& k);
    void Clear();
    void Rehash();

    bool   Empty    () const { return root_ == nullptr; }
    size_t Size     () const { return RSize(root_); }     // counts alive nodes
    size_t NumNodes () const { return RNumNodes(root_); } // counts nodes
    int    Height   () const { return RHeight(root_); }

    void   DumpBW (std::ostream& os) const;
    void   Dump (std::ostream& os) const;
    void   Dump (std::ostream& os, int kw) const;
    void   Dump (std::ostream& os, int kw, char fill) const;

    // Checks
    bool CheckBST   (bool verboseFlag) const;
    bool CheckRBLLT (int verboseFlag) const;
   
  private: // definitions and relationships

    enum Flags { ZERO = 0x00 , DEAD = 0x01, RED = 0x02 , DEFAULT = RED }; // DEFAULT = alive,red
    static const char* ColorMap (unsigned char flags)
    {
      switch(flags)
      {
        case 0x00: return ANSI_BOLD_BLUE;        // bits 00
        case 0x01: return ANSI_BOLD_BLUE_SHADED; // bits 01
        case 0x02: return ANSI_BOLD_RED;         // bits 10
        case 0x03: return ANSI_BOLD_RED_SHADED;  // bits 11
        default: return "unknown color";   // unknown flags
      }
    }

    static char BWMap (uint8_t flags)
    {
      switch(flags)
      {
        case 0x00: return 'B'; // bits 00 black alive
        case 0x01: return 'b'; // bits 01 black dead
        case 0x02: return 'R'; // bits 10 red alive
        case 0x03: return 'r'; // bits 11 red dead
        default:   return 'U'; // unknown flags
      }
    }

    class Node
    {
      friend class Map_ADT<K,D,P>;
      friend class ConstInorderMapIterator < fsu::Map_ADT<K,D,P> >;
      friend class InorderMapIterator      < fsu::Map_ADT<K,D,P> >;
      friend class LevelorderMapIterator   < fsu::Map_ADT<K,D,P> >;

      //const KeyType   key_;
      //      DataType  data_;
      
      fsu::Entry<K,D>   value_;

      Node * lchild_, * rchild_;
      unsigned char flags_;
      Node (const KeyType& k, const DataType& d, Flags flags = DEFAULT)
        : value_(k,d), lchild_(nullptr), rchild_(nullptr), flags_(flags)
      {}
      friend class Map_ADT<K,D,P>;

      bool HasLeftChild    () const  { return this != nullptr && this->lchild_ != nullptr; }
      bool HasRightChild   () const  { return this != nullptr && this->rchild_ != nullptr; }
      bool IsRed    () const { return 0 != (RED & flags_); }
      bool IsBlack  () const { return !IsRed(); }
      bool IsDead   () const { return 0 != (DEAD & flags_); }
      bool IsAlive  () const { return !IsDead(); }
      void SetRed   ()       { flags_ |= RED; }
      void SetBlack ()       { flags_ &= ~RED; }
      void SetDead  ()       { flags_ |= DEAD; }
      void SetAlive ()       { flags_ &= ~DEAD; }
    };

  private: // data
    Node *         root_;
    PredicateType  pred_;

  private: // methods
    static Node * NewNode     (const K& k, const D& d, Flags flags = DEFAULT);
    static void   RRelease    (Node* n); // deletes all descendants of n
    static Node * RClone      (const Node* n); // returns deep copy of n
    static size_t RSize       (Node * n);
    static size_t RNumNodes   (Node * n);
    static int    RHeight     (Node * n);

    // rotations
    static Node * RotateLeft  (Node * n);
    static Node * RotateRight (Node * n);

    template < class F >
    static void   RTraverse (Node * n, F f);

    // recursive left-leaning get
    Node * RGet(Node* nptr, const K& kval, Node*& location);

    // recursive left-leaning insert
    Node * RInsert(Node* nptr, const K& key, const D& data);

  }; // class Map_ADT<>


  // API

  template < typename K , typename D , class P >
  D& Map_ADT<K,D,P>::Get (const KeyType& k)
  {
    Node * location;
    root_ = RGet(root_,k,location);
    root_->SetBlack();
    return location -> value_.data_; 
  }

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Erase(const KeyType& k)
  {
    Node * n = root_;
    while(n)
    {
      if (pred_(k,n->value_.key_))       // k < n->key_ : go left
        n = n->lchild_;
      else if (pred_(n->value_.key_,k))  // k > n->key_ : go right
        n = n->rchild_;
      else                          // k == n->key_ : found
      {
        n->SetDead();
        return;
      }
    }
  }

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Clear()
  {
    RRelease(root_);
    delete root_;
    root_ = 0;
  }

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Rehash()
  { // this is complete!
    Node* newRoot = nullptr;
    for (ConstIterator i = this->Begin(); i != this->End(); ++i)
    {
      newRoot = RInsert(newRoot,(*i).key_,(*i).data_);
      newRoot->SetBlack();
    }
    this->Clear();
    this->root_ = newRoot;
  }

 template < typename K , typename D , class P >
 typename  Map_ADT<K,D,P>::Iterator Map_ADT<K,D,P>:: Includes(const KeyType& k)
 {
   Iterator i;
   for( i = Begin(); i!= End(); ++i)
   {
     if (k == (*i).key_)
      return i;
   }
   return End();
 }


 template < typename K , typename D , class P >
 typename  Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>:: Includes(const KeyType& k) const
 {
   ConstIterator i;
   for( i = Begin(); i!= End(); ++i )
   {
     if (k == (*i).key_)
     return i;
   }

   return End();
 }
  
  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node * Map_ADT<K,D,P>::RGet(Node* nptr, const K& kval, Node*& location)
  // recursive left-leaning get
  {
    // add new node at bottom of tree
    if (nptr == 0)
    {
      location = NewNode(kval,D(), RED);
      return location;
    }
        
    // invariant 2: number of black nodes in root->null paths has not changed

    // insert recursively
    if (pred_(kval,nptr->value_.key_))
      // left subtree
    {
      nptr->lchild_ = RGet(nptr->lchild_, kval, location);
      // nptr->lchild_->parent_ = nptr;
    }
    else if (pred_(nptr->value_.key_,kval))
      // right subtree
    {
      nptr->rchild_ = RGet(nptr->rchild_, kval, location);
      // nptr->rchild_->parent_ = nptr;
    }
    else
      // equality: node exists - set location 
    {
      // nptr->value_ = tval;
      nptr->SetAlive();
      location = nptr;
    }

    if (nptr->rchild_ && nptr->rchild_->IsRed() && !(nptr->lchild_ && nptr->lchild_->IsRed()))
      nptr = RotateLeft(nptr);
    if (nptr->lchild_ && nptr->lchild_->IsRed() && nptr->lchild_->lchild_ && nptr->lchild_->lchild_->IsRed())
      nptr = RotateRight(nptr);
    if (nptr->lchild_ && nptr->lchild_->IsRed() && nptr->rchild_ && nptr->rchild_->IsRed())
    {
      nptr->lchild_->SetBlack();
      nptr->rchild_->SetBlack();
      nptr->SetRed();
    }

    return nptr;
  }  
  
  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node * Map_ADT<K,D,P>::RInsert(Node* nptr, const K& key, const D& data)
  // recursive left-leaning insert
  { 
    {
      Node * location;
      Node * rval = RGet(nptr,key,location);
      location->value_.data_ = data;
      return rval;
    } // Map_ADT<K,D,P> :: RInsert()
  }

  /* everyting below here is complete */

  // proper type
  
  template < typename K , typename D , class P >
  Map_ADT<K,D,P>::Map_ADT  () : root_(nullptr), pred_()
  {}

  template < typename K , typename D , class P >
  Map_ADT<K,D,P>::Map_ADT  (P p) : root_(nullptr), pred_(p)
  {}

  template < typename K , typename D , class P >
  Map_ADT<K,D,P>::~Map_ADT ()
  {
    Clear();
  }

  template < typename K , typename D , class P >
  Map_ADT<K,D,P>::Map_ADT( const Map_ADT& tree ) : root_(nullptr), pred_(tree.pred_)
  {
    root_ = RClone(tree.root_);
  }

  template < typename K , typename D , class P >
  Map_ADT<K,D,P>& Map_ADT<K,D,P>::operator=( const Map_ADT& that )
  {
    if (this != &that)
    {
      Clear();
      this->root_ = RClone(that.root_);
    }
    return *this;
  }

  // rotations
  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node * Map_ADT<K,D,P>::RotateLeft(Node * n)
  {
    if (nullptr == n || n->rchild_ == nullptr) return n;
    if (!n->rchild_->IsRed())
    {
      std::cerr << " ** RotateLeft called with black right child\n";
      return n;
    }
    Node * p = n->rchild_;
    n->rchild_ = p->lchild_;
    p->lchild_ = n;  

    n->IsRed()? p->SetRed() : p->SetBlack();
    n->SetRed();
    return p;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node * Map_ADT<K,D,P>::RotateRight(Node * n)
  {
    if (n == nullptr || n->lchild_ == nullptr) return n;
    if (!n->lchild_->IsRed())
    {
      std::cerr << " ** RotateRight called with black left child\n";
      return n;
    }

    Node * p = n->lchild_;
    n->lchild_ = p->rchild_;
    p->rchild_ = n;  

    n->IsRed()? p->SetRed() : p->SetBlack();
    n->SetRed();
    return p;
  }

  // private static recursive methods

  template < typename K , typename D , class P >
  size_t Map_ADT<K,D,P>::RSize(Node * n)
  {
    if (n == nullptr) return 0;
    return (size_t)(n->IsAlive()) + RSize(n->lchild_) + RSize(n->rchild_);
  }

  template < typename K , typename D , class P >
  size_t Map_ADT<K,D,P>::RNumNodes(Node * n)
  {
    if (n == nullptr) return 0;
    return 1 + RNumNodes(n->lchild_) + RNumNodes(n->rchild_);
  }

  template < typename K , typename D , class P >
  int Map_ADT<K,D,P>::RHeight(Node * n)
  {
    if (n == nullptr) return -1;
    int lh = RHeight(n->lchild_);
    int rh = RHeight(n->rchild_);
    if (lh < rh) return 1 + rh;
    return 1 + lh;
  }

  template < typename K , typename D , class P >
  template < class F >
  void Map_ADT<K,D,P>::RTraverse (Node * n, F f)
  {
    if (n == nullptr) return;
    RTraverse(n->lchild_,f);
    f(n);
    RTraverse(n->rchild_,f);
  }

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::RRelease(Node* n)
  // post:  all descendants of n have been deleted
  {
    if (n != nullptr)
    {
      if (n->lchild_ != nullptr)
      {
        Map_ADT<K,D,P>::RRelease(n->lchild_);
        delete n->lchild_;
        n->lchild_ = nullptr;
      }
      if (n->rchild_ != nullptr)
      {
        Map_ADT<K,D,P>::RRelease(n->rchild_);
        delete n->rchild_;
        n->rchild_ = nullptr;
      }
    }
  } // Map_ADT<K,D,P>::RRelease()

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node* Map_ADT<K,D,P>::RClone(const Map_ADT<K,D,P>::Node* n)
  // returns a pointer to a deep copy of n
  {
    if (n == nullptr)
      return 0;
    typename Map_ADT<K,D,P>::Node* newN = NewNode (n->value_.key_,n->value_.data_);
    newN->flags_ = n->flags_;
    newN->lchild_ = Map_ADT<K,D,P>::RClone(n->lchild_);
    newN->rchild_ = Map_ADT<K,D,P>::RClone(n->rchild_);
    return newN;
  } // end Map_ADT<K,D,P>::RClone() */


  // private node allocator
  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Node * Map_ADT<K,D,P>::NewNode(const K& k, const D& d, Flags flags) 
  {
    Node * nPtr = new(std::nothrow) Node(k,d,flags);
    if (nPtr == nullptr)
    {
      std::cerr << "** Map_ADT memory allocation failure\n";
      // handle exception in-class here
    }
    return nPtr;
  }

  // development assistants

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::DumpBW (std::ostream& os) const
  {
    // fsu::debug ("DumpBW(1)");
    // This is the same as "Dump(1)" except it uses a character map instead of a
    // color map for the display: B/b = black_alive/black_dead, R/r = red_alive/red_dead

    if (root_ == nullptr)
      return;

    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    Node * fillNode = root_;
    Node * current;
  
    size_t currLayerSize, nextLayerSize, j, k;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << BWMap(current->flags_);
    if (current->lchild_ != nullptr)
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->rchild_ != nullptr)
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';
    currLayerSize = nextLayerSize;
    k *= 2;

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << BWMap(current->flags_);
        if (current != fillNode && current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
  } // DumpBW(os)

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Dump (std::ostream& os) const
  {
    // fsu::debug ("Dump(1)");

    // This implementation is very like that for Dump(os, kw, fill), except that
    // there is no supplied fill object or output format character. The trick is
    // to use the root of a non-empty tree as the fill. To make that work, we have
    // to take care of the real root case before entering the main loop. 

    if (root_ == nullptr)
      return;

    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    char nodeFill = '*';
    Node * fillNode = root_;
    Node * current;
  
    size_t currLayerSize, nextLayerSize, j, k;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
    if (current->lchild_ != nullptr)
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->rchild_ != nullptr)
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';
    currLayerSize = nextLayerSize;
    k *= 2;

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
        if (current != fillNode && current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
  } // Dump(os)

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Dump (std::ostream& os, int kw) const
  {
    // fsu::debug ("Dump(2)");
    if (root_ == nullptr)
      return;
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j;
    Que.Push(root_);
    currLayerSize = 1;
    while (!Que.Empty())
    {
      nextLayerSize = 0;
      if (kw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < currLayerSize; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (kw > 1) os << ' '; // indent each column 1 space
        os << ColorMap(current->flags_) << std::setw(kw) << current->value_.key_<< ANSI_RESET_ALL;
        if (current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        if (current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
      }
      os << '\n';
      currLayerSize = nextLayerSize;
    } // end while
    if (currLayerSize > 0)
      std::cerr << "** Map_ADT<K,D,P>::Dump() inconsistency\n";
  } // Dump(os, kw)

  template < typename K , typename D , class P >
  void Map_ADT<K,D,P>::Dump (std::ostream& os, int kw, char fill) const
  {
    // fsu::debug ("Dump(3)");
    if (root_ == nullptr)
      return;

    Node* fillNode = NewNode(K(),D());
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j, k;
    Que.Push(root_);
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      if (kw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (kw > 1) os << ' '; // indent each column 1 space
        if (current == fillNode)
        {
          os <<std::setw(kw) << fill;
        }
        else
        {
          os << ColorMap(current->flags_) << std::setw(kw) << current->value_.key_<< ANSI_RESET_ALL;
        }

        if (current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      }
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
    delete fillNode;
  } // Dump(os, kw, fill) */

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Iterator Map_ADT<K,D,P>::Begin()
  {
    Iterator i;
    i.Init(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Iterator Map_ADT<K,D,P>::rEnd()
  {
    Iterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Iterator Map_ADT<K,D,P>::End()
  {
    Iterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::Iterator Map_ADT<K,D,P>:: rBegin()
  {
    Iterator i;
    i.rInit(root_);
    return i;
  }
   

  //const version


  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>::Begin() const
  {
    ConstIterator i;
    i.Init(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>::rEnd() const
  {
    ConstIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>::End() const
  {
    ConstIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>:: rBegin() const
  {
    ConstIterator i;
    i.rInit(root_);
    return i;
  }



  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::LevelorderIterator Map_ADT<K,D,P>::BeginLevelorder()
  const
  {
    LevelorderIterator i;
    i.Init(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::LevelorderIterator Map_ADT<K,D,P>::EndLevelorder() const
  {
    LevelorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_ADT<K,D,P>::ConstIterator Map_ADT<K,D,P>::BeginStructuralInorder() const
  {
    ConstIterator i;
    i.sInit(root_);
    return i;
  }

  template < typename K , typename D , class P > 
  bool operator == (const Map_ADT<K,D,P>& map1, const Map_ADT<K,D,P>& map2)
  {
    typename Map_ADT<K,D,P>::ConstIterator i,j;
    for (i = map1.Begin(), j = map2.Begin(); i != map1.End() && j != map2.End(); ++i, ++j)
    {
      if ( (*i).key_ != (*j).key_ || (*i).data_ != (*j).data_ ) return 0;
    } 
    if (i != map1.End() || j != map2.End()) return 0;
    return 1;
  }

  template < typename K , typename D , class P > 
  bool operator != (const Map_ADT<K,D,P>& map1, const Map_ADT<K,D,P>& map2)
  {
    return !(map1 == map2);
  }

#include <map_tools.cpp>

} // namespace fsu 

#endif

