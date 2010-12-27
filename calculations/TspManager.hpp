#ifndef TSP_MANAGER_HPP
#define TSP_MANAGER_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Tsp.hpp"
#include "TspQueue.hpp"


class TspManager
{
    public:          
        static TspManager& getInstance();
        
        Tsp::TspId solve(PTsp tsp);
           
    private:    
        TspManager(int threads_num);
        TspManager(const TspManager&);
		
		void threadFunc();
		
        TspQueue tspQueue_;
		boost::thread_group pool_;
};

#endif
