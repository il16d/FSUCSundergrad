/*
    dfsurvey.h
    
    COP4530
    4/10/17
*/

#ifndef _DFSURVEY_H_
#define _DFSURVEY_H_

#include <deque.h>

namespace fsu{

  template < class G>
  class DFSurvey
  {
  public:
    typedef G                           Graph;
    typedef typename Graph::Vertex      Vertex;
    typedef typename Graph::AdjIterator AdjIterator;

 private:
    const Graph&                  g_;
    Vertex                        start_;
    size_t                        forever_;
    Vertex                        null_; 
    size_t                        time_;     // global sequencing clock
    fsu::Vector < size_t >        dtime_;    // discovery time
    fsu::Vector < size_t >        ftime_;    // finishing time
    fsu::Vector < Vertex >        parent_;   // for DFS tree
    fsu::Vector < char >          color_;    // various uses
    fsu::Vector < bool >          visited_;
    fsu::Vector < AdjIterator >   neighbor_; // supports NextNeighbor
    fsu::Deque  < Vertex >        conQ_;
    AdjIterator  NextNeighbor(Vertex v);     // iterator to next unvisited nbr
                                             // of v
  public:
    DFSurvey    ( const Graph& g );
    DFSurvey    ( const Graph& g, Vertex start );
    void Search ( );
    void Search ( Vertex v );
    void Reset  ( );
    void Reset  ( Vertex start ); 

    const fsu::Vector<Vertex>& DTime  () const { return dtime_; } 
    const fsu::Vector<Vertex>& FTime  () const { return ftime_; }
    const fsu::Vector<Vertex>& Parent () const { return parent_; }
    const fsu::Vector<char>& Color    () const { return color_; }

    size_t VrtxSize () const { return g_.VrtxSize(); }
    size_t EdgeSize () const { return g_.EdgeSize(); }
    
    size_t InfiniteTime () const { return forever_; }
    Vertex NullVertex   () const { return null_; }
 
  public:
    bool traceQue;
    void ShowQueSetup (std::ostream& os) const;
    void ShowQue      (std::ostream& os) const;
  };

  template < class G >
  DFSurvey<G>::DFSurvey (const Graph& g)
    : g_(g), start_(0), time_(0), forever_(2*g_.VrtxSize()), null_((Vertex)g_.VrtxSize()),
      dtime_    (g_.VrtxSize(), forever_),
      ftime_    (g_.VrtxSize(), forever_),
      parent_   (g_.VrtxSize(), null_),
      color_    (g_.VrtxSize(), 'w'),   // 'w' = white
      neighbor_ (g_.VrtxSize()),
      conQ_()
  {
    for (Vertex x = 0; x < g_.VrtxSize(); ++x)
      neighbor_[x] = g_.Begin(x);
  }

  template < class G >
  DFSurvey<G>::DFSurvey (const Graph& g , Vertex start )
    : g_(g), start_(start), time_(0), forever_(2*g_.VrtxSize()), null_((Vertex)g_.VrtxSize()),
      dtime_    (g_.VrtxSize(), forever_),
      ftime_    (g_.VrtxSize(), forever_),
      parent_   (g_.VrtxSize(), null_),
      color_    (g_.VrtxSize(), 'w'),   // 'w' = white
      neighbor_ (g_.VrtxSize()),
      conQ_()
  {
    for (Vertex x = 0; x < g_.VrtxSize(); ++x)
      neighbor_[x] = g_.Begin(x);
  }

  template < class G >
  void DFSurvey<G>::Reset()
  {
    time_ = 0;
    conQ_.Clear();
    if (color_.Size() != g_.VrtxSize()) // g_ has changed vertex size
    {
      forever_ = 2*g_.VrtxSize();        // last time stamp is 2|V| -1
      null_    = (Vertex)g_.VrtxSize();  // |V| is not valid vertex number
      dtime_.SetSize   (g_.VrtxSize(), forever_);
      ftime_.SetSize   (g_.VrtxSize(), forever_);
      parent_.SetSize  (g_.VrtxSize(), null_);
      color_.SetSize   (g_.VrtxSize(), 'w');  // 'w' = white
      neighbor_.SetSize(g_.VrtxSize());
      for (Vertex x = 0; x < g_.VrtxSize(); ++x)
        neighbor_[x] = g_.Begin(x);
    }
    else
    {
      for (Vertex x = 0; x < g_.VrtxSize(); ++x)
      {
        dtime_[x]    = forever_;
        ftime_[x]    = forever_;
        parent_[x]   = null_;           
        color_[x]    = 'w';  // 'w' = white
        neighbor_[x] = g_.Begin(x);
      }
    }
  }

  template < class G >
  void DFSurvey<G>::Reset( Vertex start )
  {
    start_ = start;
    Reset();
  }

  template < class G >
  void DFSurvey<G>::Search( Vertex v )
  {
    dtime_[v] = time_++;
    conQ_.PushBack(v);
   
    if (traceQue) 
      ShowQue(std::cout); 

    color_[v] = 'g';         // 'g' = grey
    Vertex top;
    AdjIterator i; 
    while (!conQ_.Empty())
    {
      top = conQ_.Back();
      i = NextNeighbor(top); // an iterator!
      if (i != g_.End(top))
      {
        dtime_[*i] = time_++;
        conQ_.PushBack(*i);

        if (traceQue)
          ShowQue(std::cout); 
       
        parent_[*i] = top;
        color_[*i] = 'g';    // 'g' = grey
      }
      else
      {
        conQ_.PopBack();
        
        if (traceQue)
          ShowQue(std::cout);         
        
        color_[top] = 'b';   // 'b' = black
        ftime_[top] = time_++;
      }
    }
  }

  template < class G >
  void DFSurvey<G>::Search()
  {
    Reset();
    if (traceQue)
    {
      ShowQueSetup(std::cout); 
      ShowQue(std::cout);
    }

    for (Vertex v = start_; v < g_.VrtxSize(); ++v)
    {
      if (color_[v] == 'w') // white = unvisited
        Search(v);
    }
    for (Vertex v = 0; v < start_; ++v)
    {
      if (color_[v] == 'w') // white = unvisited
        Search(v);
    }
  }

  template < class G >
  typename DFSurvey<G>::AdjIterator DFSurvey<G>::NextNeighbor (Vertex x)
  {
    // Note: neighbor_[x] is already initialized and part way through a
    // traversal!
    // This loop just advances to the next unvisited (white) neighbor of x
    // Total cost for entire survey is a single traversal of each adjacency list
    // = Theta(|V|)
    while (neighbor_[x] != g_.End(x) && 'w' != color_[*neighbor_[x]])
      ++neighbor_[x];
    return neighbor_[x];
  }

  template < class G >
  void DFSurvey<G>::ShowQueSetup (std::ostream& os) const
  {
    os << "\n  conStack\n"
       << "  ------->\n";
  }

  template < class G >
  void DFSurvey<G>::ShowQue (std::ostream& os) const
  {
    os << "  ";
    if (conQ_.Empty())
      os << "NULL";
    else
      conQ_.Display(os, ' ');
    os << '\n';
  }



}

#endif
