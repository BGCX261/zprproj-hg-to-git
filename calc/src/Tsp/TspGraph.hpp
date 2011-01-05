#ifndef CALC_TSP_GRAPH_HPP
#define CALC_TSP_GRAPH_HPP

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/metric_tsp_approx.hpp>

#include "Route.hpp"
#include "Tsp.hpp"

namespace calc
{
    using namespace boost;          

    class TspGraph
    {
        public:
            TspGraph(const Route::Cities &cities);
            
            Tsp::PResult optimizeRoute();    
        
        private:    
            typedef property<edge_weight_t, double> EdgeProperty;
            typedef adjacency_matrix<undirectedS, no_property, EdgeProperty> Graph; 
            typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
            typedef typename graph_traits<Graph>::edge_descriptor Edge;                              
            
            const Route::Cities &cities_;
            
            Graph graph_; 
            
            void buildGraph();                  
    };
        
} // namespace calc          

#endif // CALC_TSP_GRAPH_HPP
