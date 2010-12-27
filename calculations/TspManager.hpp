#ifndef TSPMANAGER_HPP
#define TSPMANAGER_HPP


#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Tsp.hpp"

typedef boost::shared_ptr<Tsp> PTsp;

class TspManager
{
    public:          
        static TspManager& getInstance()
        {
            static TspManager manager;
            return manager;
        }
        
        int solve(PTsp tsp)
        {
            tspc_.push_back(tsp);
            
            boost::thread optimizing_thread(boost::bind(&Tsp::solve, tsp));
            
            return tspc_.size() - 1;
        }
        
        PTsp getTsp(int tsp_id)
        {
            return tspc_[tsp_id];
        }        
           
    private:
        TspManager(){}
        TspManager(const TspManager&);       
        
        std::vector<PTsp> tspc_;        
};

#endif
