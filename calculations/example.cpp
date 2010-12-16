/* Compilation: g++ -o example example.cpp TspRoute.cpp -pthread -lboost_thread */

#include <iostream>
#include <map>

#include "TspManager.hpp"


int main(int argc, char *argv[])
{

            
    PTspRoute route(new TspRoute);
    
    for(int i = 0; i < 2000; i++)
        route->addCity(PCity(new City(i, i*2, i*3)));  
        
    TspManager::getInstance().addTsp(route);
    TspRoute::State s;
    

    const char symb[] = "|\\-/";
    const char *state[] = {"NONE", "OPTIMIZING", "OPTIMIZED"};
    
    int i = 0;
    do
    {
        s = route->getState();
        usleep(200000);
        std::cout << "\rState: " << state[s] << " " << symb[i] << " " << std::flush;
               
        ++i;
        i %= 4;
            
    }while(s != TspRoute::OPTIMIZED);
    
    std::cout << std::endl;
        

    return 0;
    
}
