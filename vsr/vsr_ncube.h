#ifndef VSR_NCUBE_H_INCLUDED
#define VSR_NCUBE_H_INCLUDED

#include "vsr_products.h"
#include <vector> 

namespace vsr{    
	
using namespace std;
	
//typedef EGAMV< typename Blade1<3>::VEC > Vec;

template<int DIM>
struct Proj{
   	typedef EGAMV< typename Blade1<DIM>::VEC > TVec;
	typedef EGAMV< typename Blade1<DIM-1>::VEC > OneDown; //Next Projection Down
  	 
	static auto Call( VT dist, const TVec& v ) RETURNS (
		( Proj<DIM-1>::Call( dist, v.template cast<OneDown>() * ( dist / (dist - v[DIM-1] ) ) ) )
	)  
	 
	
	static VT Val( VT dist, const TVec & v ) { return dist / (dist - v[DIM-1] )  * Proj<DIM-1>::Val(dist, OneDown(v) ); }
	// static VT Val( VT dist, const Vec& v) {
	// 	return Proj< DIM, 4, DIM==TARGET >::Call(dist, v);
	// } 
};    
     
template<>
struct Proj<3>{  
    typedef EGAMV< typename Blade1<3>::VEC > TVec;
	static TVec Call(VT dist, const TVec& v) { return v; }  
	static VT Val(VT dist, const TVec & v ) { return 1.0; }
}; 

 
struct Edge{                                            
  int a, b;  
  Edge(int _a, int _b) : a(_a), b(_b){}  

	void print() { printf("%d, %d\n", a, b);}
};

template<int DIM>
struct NCube{         
	
	typedef EGAMV< typename Blade1<DIM>::VEC > TVec;
   // typedef typename Blade1<DIM-1>::VEC Proj; //Projection Down  
	typedef EGAMV< typename Blade1<3>::VEC > Vec3;
	
	int NumVert = pow(2.f,DIM);
	
	vector<TVec> roots;
	vector<Edge> edges; 
	
    void init() {
		TVec va, vb;
		va[DIM-1] = -.5;
		vb[DIM-1] = .5;
		
		//int ix = 0;  
		auto next = NCube<DIM-1>();  
				
		for (auto i :  next.roots ){
		   
		 	roots.push_back( TVec(i+va) );
			roots.push_back( TVec(i+vb) ); 
	
		}   
		

		int d = pow(2.f, DIM-1); 
		for (auto i : next.edges ){        
  		
			edges.push_back(i); 
			edges.push_back( Edge(i.a + d, i.b + d));   

		}                                                
		
		for (int i = 0; i < next.NumVert; ++i ){
			edges.push_back( Edge(i, i + d) );
		}
		                      
	} 
	
	vector< Vec3 > project(VT dist){ 
		vector< Vec3 > res;
		 for (auto i : roots ){
			res.push_back( Proj<DIM>::Call(dist, i) );//i.cast<Proj>() * ( dist / (dist - i[DIM-1] ) ) ); 
		}  
		return res;
	}  
	
	NCube(){ init(); }
	
	void print() {
		for (auto i : roots ) { i.bprint(); i.vprint(); }
		for (auto i : edges) { i.print(); }
		
	} 
};

template<>
struct NCube<1>{
	typedef EGAMV< typename Blade1<1>::VEC > TVec; 
	int NumVert = 2;
	
	vector<TVec> roots;
	vector<Edge> edges; 
	
	NCube(){  init(); }  
		
	void init(){  	
		roots.push_back( TVec(-.5) );
		roots.push_back( TVec(.5) );  
		
		edges.push_back( Edge(0,1) );
	};    
	
	void print() {
		 for (auto i : roots) { i.bprint(); i.vprint(); }   
		 for (auto i : edges) { i.print(); } 
	}
  
};

}//vsr::  

#endif