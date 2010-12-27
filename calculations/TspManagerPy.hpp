#ifndef TSP_MANAGER_PY_HPP
#define TSP_MANAGER_PY_HPP


#include <boost/python.hpp>
#include "TspPy.hpp"
#include "TspManager.hpp"

class TspManagerPy
{
    public:          
        
        int solve(const TspPy &tsp_py)
        {
            return TspManager::getInstance().solve(tsp_py.getTsp());
        }          
};

#endif
