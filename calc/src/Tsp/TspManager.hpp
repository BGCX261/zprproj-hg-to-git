#ifndef CALC_TSP_MANAGER_HPP
#define CALC_TSP_MANAGER_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Tsp.hpp"
#include "TspQueue.hpp"

namespace calc
{
    
    class TspManager
    {
        public:          
            static TspManager& getInstance();
            
            void solve(PTsp tsp);
               
        private:   
            TspQueue tspQueue_;
            
	        boost::thread_group pool_;
	                 
            TspManager(int threads_num);
            
            TspManager(const TspManager&);
	
	        void threadFunc();	
    };
        
} // namespace calc  

#endif // CALC_TSP_MANAGER_HPP
