// author: Rafał Witowski

#ifndef CALC_TSP_GRAPH_HPP
#define CALC_TSP_GRAPH_HPP

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/metric_tsp_approx.hpp>

#include "Route.hpp"
#include "Tsp.hpp"

namespace calc
{
    using namespace boost;          

    /**
     * Graph of cities connections and distances between them
     */
    class TspGraph
    {
        public:
            /** c-tor, builds graph using informations from cities collection */
            TspGraph(const Route::Cities &cities);
            
            /**
             * This method uses algorithm of finding approximated solution, and 
             * guarantes that that computed route will be in the worst case
             * twice as long as an optimal one
             *
             * Returns shared_ptr to created collection of cities id's.
             * Order of these id's in collection is the order which
             * was computed by the algorithm             
             */
            Tsp::PResult optimizeRoute();    
        
        private:    
            typedef property<edge_weight_t, double> EdgeProperty;
            
            // Undirected graph
            typedef adjacency_matrix<undirectedS, no_property, EdgeProperty> Graph; 
            typedef graph_traits<Graph>::vertex_descriptor Vertex; // Vertex type
            typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type                              
            
            // Cities collection used when building graph 
            const Route::Cities &cities_;
            
            // BGL's graph
            Graph graph_; 
            
            /* Builds graph by putting all cities from cities_ collection and
            setting edges weights */
            void buildGraph();                  
    };
        
} // namespace calc          

#endif // CALC_TSP_GRAPH_HPP
