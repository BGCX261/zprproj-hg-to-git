#ifndef CALC_TSP_MANAGER_PY_HPP
#define CALC_TSP_MANAGER_PY_HPP

#include "TspPy.hpp"
#include "TspManager.hpp"

namespace calc
{
    class TspManagerPy
    {
        public:          
            
            void solve(const TspPy &tsp_py)
            {
                TspManager::getInstance().solve(tsp_py.getTsp());
            }          
    };
    
} // namespace calc

#endif CALC_TSP_MANAGER_PY_HPP
