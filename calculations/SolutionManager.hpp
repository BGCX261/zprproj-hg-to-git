#ifndef SOLUTIONMANAGER_HPP
#define SOLUTIONMANAGER_HPP

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include "TspSolver.hpp"


class Task
{
    public:
        enum State {NOT_STARTED, IN_PROGRESS, FINISHED};
            
        Task(int id, PCityList city_list) :
            id_(id), cityList_(city_list), state_(NOT_STARTED)
        {}
        
        State getState() const
        {
            return state_;
        }
        
        void executeAsynchronously()
        {
            boost::thread worker(boost::bind(&Task::workerFunc, this));
        }
        
        void executeSynchronously()
        {
            workerFunc();
        }
        
    private:
        PCityList workerFunc()
        {
            state_ = IN_PROGRESS;
            
            CityGraph graph(*cityList_);
            resultList_ = graph.tspApprox(); 
            
            state_ = FINISHED;
            
            return resultList_;
        }
        
        int id_;
        PCityList cityList_;
        PCityList resultList_;       
        State state_;
};


class SolutionManager
{
    public:
        enum State {UNKNOWN, FINISHED, BUSY};
        
        static SolutionManager& getInstance()
        {
            static SolutionManager sm;
            return sm;
        }
        
        int solve(const CityList &list)
        {
            TspSolver tsp_solver(1, list);
            boost::thread solving_thread(tsp_solver);
            solving_thread.join();
            
            return 1;
        }
        
        State getTaskState(int task_id)
        {
            return UNKNOWN;
        }
        
        PCityList getSolution(int task_id)
        {
            return PCityList();
        }
        
        void insertSolution(PCityList){}        
        
    private:
        SolutionManager(){}
        SolutionManager(const SolutionManager&);        
        
        

        
        std::map<int, Task> solutions_;

};

#endif
