#include "TspGraph.hpp"

#include <vector>
#include <utility>
#include <iterator>
#include <cassert>

namespace calc
{

    TspGraph::TspGraph(const Route::Cities &cities) :
        cities_(cities),
        graph_(cities.size())
    {
        assert(!cities_.empty());            
        buildGraph();      
    }


    Tsp::PResult TspGraph::optimizeRoute()
    {                
        typedef std::vector<Vertex> Container;
        
        Container c;
        metric_tsp_approx_tour(graph_, std::back_inserter(c));
        
        Tsp::PResult result(new Tsp::Result);
        for (Container::iterator ci = c.begin(); ci != c.end() - 1; ++ci)
           result->push_back(cities_[*ci].getId());

        return result;
    }        


    void TspGraph::buildGraph()
    {
        typedef graph_traits<Graph>::vertex_iterator VIt;   
        
        typedef property_map<Graph, vertex_index_t>::type VertexMap;
        typedef property_map<Graph, edge_weight_t>::type WeightMap;
        
        WeightMap wmap = get(edge_weight, graph_);
        VertexMap vmap = get(vertex_index, graph_);
        
        Edge e;
        bool inserted;

        std::pair<VIt, VIt> verts = vertices(graph_);
        for (VIt src = verts.first; src != verts.second; ++src)
        {
            for (VIt dst(src); dst != verts.second; ++dst)
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

} // namespace calc          

