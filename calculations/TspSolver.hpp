#ifndef TSPSOLVER_HPP
#define TSPSOLVER_HPP

#include <iostream>
#include <boost/thread.hpp>
#include "CityGraph.hpp"


class TspSolver
{
    public:
        TspSolver(int id, const CityList &city_list) :
            taskId_(id), taskCityList_(city_list)
        {}
        
        void operator()()
        {
            std::cout << "threadFunc start" << std::endl;
            CityGraph cg(taskCityList_);
            PCityList pcl = cg.tspApprox();            
            std::cout << "threadFunc stop" << std::endl;
        }
        
        

    private:
        int taskId_;
        const CityList &taskCityList_;
        
};

#endif
