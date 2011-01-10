#ifndef CALC_TSP_MANAGER_HPP
#define CALC_TSP_MANAGER_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Tsp.hpp"
#include "TspQueue.hpp"

namespace calc
{
    /**
     * Manages tsp solving in separate threads
     */
    class TspManager
    {
        public:          
            /** Singleton */
            static TspManager& getInstance();
            
            /** Queues tsp for solving */
            void solve(PTsp tsp);
               
        private:   
            TspQueue tspQueue_; // Queue of tsps            

	        boost::thread_group pool_; // threads used for solving tsps
	                 
	        /**
	         * private c-tor - singleton
	         *
	         * starts threads_num solving threads
	         */         
            TspManager(int threads_num);
            
            /**
             * private cc-tor - singleton
             */
            TspManager(const TspManager&);
	
	        /**
	         * solving thread function, gets tsps from queue and solves them
	         */
	        void threadFunc();	
    };
        
} // namespace calc  

#endif // CALC_TSP_MANAGER_HPP
