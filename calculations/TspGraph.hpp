#ifndef TSP_GRAPH_HPP
#define TSP_GRAPH_HPP

#include <utility>
#include <vector>
#include <iterator>

#include <boost/shared_ptr.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/metric_tsp_approx.hpp>

#include "Route.hpp"
#include "Tsp.hpp"



using namespace boost;
using namespace std;

class TspGraph
{
    public:
        TspGraph(const Route::Cities &cities) :
            cities_(cities),
            graph_(cities.size())
        {
            buildGraph();      
        }
        
        Tsp::PResult optimizeRoute()
        {                
            typedef vector<Vertex> Container;
            
            Container c;
            metric_tsp_approx_tour(graph_, back_inserter(c));
            
            Tsp::PResult result(new Tsp::Result);
            for (Container::iterator ci = c.begin(); ci != c.end() - 1; ++ci)
               result->push_back(cities_[*ci].getId());

            return result;
        }        
    
    private:
    
        typedef property<edge_weight_t, double> EdgeProperty;
        typedef adjacency_matrix<undirectedS, no_property, EdgeProperty> Graph;
        
        typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename graph_traits<Graph>::edge_descriptor Edge;  
        
        typedef typename property_map<Graph, vertex_index_t>::type VertexMap; 
        typedef typename property_map<Graph, edge_weight_t>::type WeightMap; 
        
        void buildGraph()
        {
            typedef typename graph_traits<Graph>::vertex_iterator VItr;                          
            
            WeightMap wmap = get(edge_weight, graph_);
            VertexMap vmap = get(vertex_index, graph_);
            
            Edge e;
            bool inserted;

            pair<VItr, VItr> verts = vertices(graph_);
            for (VItr src = verts.first; src != verts.second; ++src)
            {
                for (VItr dst(src); dst != verts.second; ++dst)
                {
                    if (dst != src)
                    {                                
                        const City &src_city = cities_[vmap[*src]];
                        const City &dst_city = cities_[vmap[*dst]];
                        
                        tie(e, inserted) = add_edge(*src, *dst, graph_);
                        wmap[e] = src_city.distance(dst_city);
                    }

                }

            }
        }         
        

        
        

         
        const Route::Cities &cities_;
        Graph graph_;       
};

#endif //TSPGRAPH_HPP
