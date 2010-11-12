#include <boost/graph/adjacency_matrix.hpp>
#include <map>

using namespace boost;

class CityGraph
{
    public:
        typedef double Distance;
        
        CityGraph(int size) : g_(size){}
        
        void addEdge(int city1_id, int city2_id, Distance dist)
        {
            add_edge(city1_id, city2_id, EdgeProperty(dist), g_);
        }
        
        Distance getDistance(int city1_id, int city2_id) const
        {        
            property_map<Graph, edge_weight_t>::const_type index = get(edge_weight, g_);
            graph_traits<Graph>::edge_descriptor e = edge(city1_id, city2_id, g_).first;        

            return get(index, e);
        }
        
    
    private:

        typedef property<edge_weight_t, Distance> EdgeProperty;
        typedef adjacency_matrix<undirectedS, no_property, EdgeProperty> Graph;
        
        Graph g_;         
        
};


