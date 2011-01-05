#ifndef CALC_TSP_MANAGER_PY_HPP
#define CALC_TSP_MANAGER_PY_HPP

#include "../Tsp/TspManager.hpp"
#include "TspPy.hpp"

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

#endif // CALC_TSP_MANAGER_PY_HPP
