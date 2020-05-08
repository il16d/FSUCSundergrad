/*

*/

#ifndef _MOVIEMATCH_H
#define _MOVIEMATCH_H


#include <genalg.h>
#include <gbsearch.h>
#include <list.h>
#include <graph_util.h>
#include <survey_util.h>
#include <xstring.h>
#include <fstream>
#include <iostream>
#include <vector.h>
#include <deque.h>
#include <xstring.h>
#include <list.h>
#include <hashclasses.h>
#include <graph.h>
#include <bfsurvey.h>
#include <dfsurvey.h>
#include <hashtbl.h>
#include <gheap.h>


// types used
typedef uint32_t                           Vertex;
typedef fsu::String                        Name;
typedef fsu::ALUGraph <Vertex>             Graph;
typedef fsu::BFSurvey <Graph>              BFS;
typedef hashclass::KISS<Name>              Hash;
typedef fsu::HashTable<Name,Vertex,Hash>   AA; // associative array
typedef fsu::List<Vertex>                  List; 
typedef fsu::Vector<Name>                  Vector;

class MovieMatch
{
public:
  MovieMatch         ();
  bool Load          (const char* filename);
  bool Init          (const char* actor);
  void Shuffle       ();
  long MovieDistance (const char* actor);
  void ShowPath      (std::ostream& os) const;
  void ShowStar      (Name name, std::ostream& os) const;
  void Hint          (Name name, std::ostream& os, size_t size) const;
  void Dump          (std::ostream& os) const;
  
private:
  static void  Line     (std::istream& is, Vector& movie);
  bool         Movie    (Vertex);

  Graph              g_;
  Vector             name_;
  Vector             hint_;
  AA                 vrtx_;
  BFS                bfs_;
  fsu::List <Vertex> path_;
  Name               baseActor_;
};

  MovieMatch::MovieMatch(): g_(), name_(), hint_(), vrtx_(), bfs_(g_), baseActor_()
  {}

  bool MovieMatch::Movie(Vertex v)
  {
    fsu::String s(name_[v]); 
    size_t sSize = s.Length();
  
    if (s[sSize -1] != ')')
       return 0; 
    else if (   isdigit(s[sSize-2]) && isdigit(s[sSize-3]) && isdigit(s[sSize-4]) && isdigit(s[sSize-5]) && (s[sSize-6] == '(') )
      return 1; 
    else
      return 0;   
  }

  bool MovieMatch::Load ( const char* filename)
  {

    std::cout << " Loading database " << filename << " (first read) ...";    

    Vertex v1 = 0;
    size_t vertex_count = 0; 
    size_t movies = 0; //movie counter
    size_t actors = 0; //actor counter
    size_t buckets = 100;

    fsu::Vector<Name> iVec;
    
    std::ifstream ifs;
    ifs.open(filename); //open file
    
    //check for bad file
    if(ifs.fail())
      return 0; //failure

    ifs.seekg(0);

    while( !(ifs.eof()) ) //while not end of file
    {
      Line(ifs, iVec); //read movie and actor

      if( iVec.Size() > 0 )
        ++movies;
 
      for (size_t i = 0; i < iVec.Size(); ++i)
      {
        if ( !(vrtx_.Retrieve(iVec[i],v1)) ) //if doesnt exist insert it
        {
          vrtx_.Insert(iVec[i],vertex_count++);
          name_.PushBack(iVec[i]);
          hint_.PushBack(iVec[i]);

          ++actors;
        }
      }

      if (actors > (2*buckets))
      {
        buckets *= 4;
        vrtx_.Rehash(buckets);
      }
    }

    vrtx_.Rehash(actors);
    
    ifs.clear();
    ifs.seekg(0);

    std::cout << "(second read) ... "; 

    g_.SetVrtxSize(vrtx_.Size());

    while( !(ifs.eof()) ) //while not end of file
    {
      Line(ifs, iVec);
      for(size_t j = 1; j < iVec.Size(); ++j)
        g_.AddEdge( vrtx_[iVec[0]], vrtx_[iVec[j]] );
    }  

    ifs.close(); //close file

      std::cout << "done." << std::endl;  
      std::cout << " " << movies << " movies and "<<(actors-movies) << " actors read from " << filename << std::endl;      
   
    return 1; //success
  }

  bool MovieMatch::Init (const char* actor)
  {
    Vertex v;

    fsu::LessThan<Name> pred_;
    fsu::g_heap_sort(hint_.Begin(),hint_.End(),pred_);

    if( !(vrtx_.Retrieve(actor,v)) )
      {
        std::cerr << " ** Init: " << actor << " is not in the database" << std::endl;
        return 0;
      }
    else if (Movie(v))
      {
        std::cerr << "** Init: " << actor << " is a movie " << std::endl;
        return 0;
      }
    else
      {
        baseActor_ = actor;
        bfs_.Reset();
        bfs_.Search(v);
        return 1;
      }  
  }
  
  void MovieMatch::Shuffle ()
  {
    g_.Shuffle();
    bfs_.Reset();
    bfs_.Search( vrtx_[baseActor_] ); 
  }
 
  long MovieMatch::MovieDistance (const char* actor)
  {
    Vertex v;
    
    if ( !(vrtx_.Retrieve(actor, v)) )
      return -3;
    else if ( bfs_.Color()[v] != 'b' )     
      return -2;
    else if ( Movie(v) )
      return -1;
    else 
    {
      long MovieDis = bfs_.Distance()[v] / 2;
      
      path_.Clear();
      path_.PushBack(v);
      
      while( bfs_.Parent()[v] != bfs_.NullVertex() )  
      {
        path_.PushBack(bfs_.Parent()[v]);
        v = bfs_.Parent()[v];
      } 
      
      return MovieDis;
    } //end else
          
  }

  void MovieMatch::ShowPath (std::ostream& os) const
  {
    size_t cnt = 0;

    os << std::endl;  

    for(List::ConstIterator i = path_.Begin(); i != path_.End(); ++i)
    {
      if( (cnt % 2) == 1)
        os << "   | ";
      else
        os << " ";
      os << name_[*i] << std::endl;
      ++cnt;
    }

    os << std::endl;
  }

  void MovieMatch::ShowStar (Name name, std::ostream& os) const
  {
    Vertex v = vrtx_[name];

    os << std::endl;
    os << name << std::endl;

    for (Graph::AdjIterator g = g_.Begin(v); g != g_.End(v); ++g)
      os << "   | " << name_[*g] << std::endl;

    os << std::endl;
    os << std::endl;
  }
  
void MovieMatch::Hint (Name name, std::ostream& os, size_t size = 6) const
  {
    Name trunc;
    Name trunczz;
    size_t nSize = name.Size();
    size_t tSize = size;

    if (nSize < size)
      tSize = nSize;
  
    char cString[tSize+1];    

    for( size_t i = 0; i < tSize; ++i )
      cString[i] = name.Element(i);
    cString[tSize] = '\0'; //null
    
    trunc.Wrap(cString);

    char czString[tSize+3]; //zz + null
    
    for(size_t i = 0; i < tSize; ++i)
      czString[i] = name.Element(i);
    
    czString[tSize] = 'z';
    czString[tSize+1] = 'z';
    czString[tSize+2] = '\0';
 
    trunczz.Wrap(czString);


    fsu::LessThan<Name> pred_;
    Vector::ConstIterator fhBegin = hint_.Begin();
    Vector::ConstIterator fhEnd = hint_.End();

    Vector::ConstIterator hBegin = fsu::g_lower_bound(fhBegin,fhEnd,trunc,pred_);
    Vector::ConstIterator hEnd = fsu::g_lower_bound(fhBegin,fhEnd,trunczz,pred_);

    for (size_t i = 0; i < 2; ++i)
    {
      if (hBegin != fhBegin)
        --hBegin;
    }

    for (size_t i = 0; i < 2; ++i)
    {
      if(hEnd != fhEnd)
        --hEnd;
    }

    for (Vector::ConstIterator c = hBegin; c != hEnd; ++c)
    os << *c << std::endl;
 }
  
  void MovieMatch::Dump (std::ostream& os) const
  {
    ShowAL(g_,os);
    WriteData(bfs_,os);
    vrtx_.Dump(os);
    for (size_t i = 0; i < name_.Size(); ++i)
    {
     os << "name_[" << i << "] = " << name_[i] << '\t';
     os << "vrtx_[" << name_[i] << "] = " << vrtx_[name_[i]] << '\n';
    }
    vrtx_.Analysis(std::cout);
  }  

void MovieMatch::Line (std::istream& is, fsu::Vector<Name>& movie)
{
  movie.Clear();
  fsu::String line;
  char delim = '/';
  line.GetLine(is);
  char* name_buffer = new char [1+line.Size()];
  size_t pos = 0, next = 0;
  while (pos < line.Size())
  {
    next = line.Position(delim,pos);
    for (size_t i = pos; i < next; ++i)
    {
      name_buffer[i - pos]= line[i];
    }
    name_buffer[next-pos] = '\0';
    movie.PushBack(name_buffer);
    pos = ++next; // skip delimiter
  }
  delete [] name_buffer;
}

#endif
