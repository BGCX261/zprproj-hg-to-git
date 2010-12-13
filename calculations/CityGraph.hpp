#ifndef CITYGRAPH_HPP
#define CITYGRAPH_HPP

#include <utility>
#include <vector>
#include <iterator>

#include <boost/shared_ptr.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/metric_tsp_approx.hpp>

#include "CityList.hpp"

using namespace boost;
using namespace std;

typedef boost::shared_ptr<CityList> PCityList;

class CityGraph
{
    public:
        CityGraph(const CityList &city_list) :
            graph_(city_list.getSize()),
            origList_(city_list),
            builded_(false)
        {}
        
        void optimize()
        {
            if(!builded_)
            {
                buildGraph();
                builded_ = true;
            }
                
            tsp_solve();
        }
        
    
    private:
    
        typedef property<edge_weight_t, double> EdgeProperty;
        typedef adjacency_matrix<undirectedS, no_property, EdgeProperty> Graph;
        
        typedef graph_traits<Graph>::vertex_descriptor Vertex;
        typedef graph_traits<Graph>::edge_descriptor Edge;  
        
        typedef property_map<Graph, vertex_index_t>::type VertexMap; 
        typedef property_map<Graph, edge_weight_t>::type WeightMap;  
        
        PCityList tsp_solve()
        {
            typedef vector<Vertex> Container;
            
            Container c;
            metric_tsp_approx_tour(graph_, back_inserter(c));
            
            PCityList optimized_list(new CityList);
            for (Container::iterator ci = c.begin(); ci != c.end(); ++ci)
            {
               optimized_list->addCity(origList_.getCities()[*ci]);
            }

            return optimized_list;
        }
        
        
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
                        PCity src_city = origList_.getCities()[vmap[*src]];
                        PCity dst_city = origList_.getCities()[vmap[*dst]];
                        
                        tie(e, inserted) = add_edge(*src, *dst, graph_);
                        wmap[e] = src_city->distance(*dst_city);
                    }

                }

            }
        }
         
        
        Graph graph_;
        const CityList &origList_;  
        bool builded_;       
        
};

#endif //CITYGRAPH_HPP
