// author: Rafał Witowski

#include "TspGraph.hpp"

#include <vector>
#include <utility>
#include <iterator>
#include <cassert>

namespace calc
{

    /** c-tor, builds graph using informations from cities collection */
    TspGraph::TspGraph(const Route::Cities &cities) :
        cities_(cities),
        graph_(cities.size())
    {
        assert(!cities_.empty());            
        buildGraph();      
    }

    /** Finds approximated tsp solution */
    Tsp::PResult TspGraph::optimizeRoute()
    {                
        typedef std::vector<Vertex> Container; // Container for vertexes
        
        Container c;
        
        // Gets approximated solution of tsp, puts vertexes in computed order to the container
        metric_tsp_approx_tour(graph_, std::back_inserter(c));
        
        // Creates collection of cities id's from collection of vertexes
        Tsp::PResult result(new Tsp::Result);
        for (Container::iterator ci = c.begin(); ci != c.end() - 1; ++ci)
           result->push_back(cities_[*ci].getId());

        return result;
    }        


    /* Builds graph by putting all cities from cities_ collection and
    setting edges weights */
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

                    tie(e, inserted) = add_edge(*src, *dst, graph_); // insert edge
                    wmap[e] = src_city.distance(dst_city); // set edge weight (distance between cities
                }

            }

        }
    } 

} // namespace calc          

