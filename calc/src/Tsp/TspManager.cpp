#include "TspManager.hpp"


namespace calc
{

    /* Singleton */
    TspManager& TspManager::getInstance()
    {
        static TspManager manager(3);
        return manager;
    }

    /* Queues tsp for solving */
    void TspManager::solve(PTsp tsp)
    {
        tspQueue_.push(tsp);
    }      

    /* starts threads_num solving threads */  
    TspManager::TspManager(int threads_num)
    {
        for(int i = 0; i < threads_num; ++i)
	        pool_.create_thread(boost::bind(&TspManager::threadFunc, this));
    }

    /** solving thread function, gets tsps from queue and solves them */
    void TspManager::threadFunc()
    {
        while(1)
        {
	        PTsp tsp = tspQueue_.pop();
	        tsp->solve();
        }
    }
        
} // namespace calc  

