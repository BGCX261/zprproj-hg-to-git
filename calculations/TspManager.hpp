#ifndef TSPMANAGER_HPP
#define TSPMANAGER_HPP


#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "TspRoute.hpp"

typedef boost::shared_ptr<TspRoute> PTspRoute;

class TspManager
{
    public:       

        
        static TspManager& getInstance()
        {
            static TspManager manager;
            return manager;
        }
        
        int addTsp(PTspRoute tsp)
        {
            tspc_.push_back(tsp);
            
            boost::thread optimizing_thread(boost::bind(&TspRoute::optimize, tsp));
            
            return tspc_.size() - 1;
        }
        
        PTspRoute getTsp(int tsp_id)
        {
            return tspc_[tsp_id];
        }
        
           
    private:
        TspManager(){}
        TspManager(const TspManager&);       
        
        std::vector<PTspRoute> tspc_;        
};

#endif
