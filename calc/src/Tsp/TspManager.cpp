#include "TspManager.hpp"


namespace calc
{

    TspManager& TspManager::getInstance()
    {
        static TspManager manager(3);
        return manager;
    }


    void TspManager::solve(PTsp tsp)
    {
        tspQueue_.push(tsp);
    }      
       

    TspManager::TspManager(int threads_num)
    {
        for(int i = 0; i < threads_num; ++i)
	        pool_.create_thread(boost::bind(&TspManager::threadFunc, this));
    }


    void TspManager::threadFunc()
    {
        while(1)
        {
	        PTsp tsp = tspQueue_.pop();
	        tsp->solve();
        }
    }
        
} // namespace calc  

