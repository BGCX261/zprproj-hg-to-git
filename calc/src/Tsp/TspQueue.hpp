// author: Rafał Witowski

#ifndef CALC_TSP_QUEUE_HPP
#define CALC_TSP_QUEUE_HPP

#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "Tsp.hpp"

/** Synchronized queue of tsps */
namespace calc
{

    class TspQueue
    {
        public:   
            /** get tsp and remove from queue, blocks if no tsp available */                     
            PTsp pop();            
            
            /** insert tsp at end of queue, sets the tsp state to QUEUED */
            void push(PTsp tsp);
            
        private:
            typedef std::queue<PTsp> Queue; // Queue type
            
            Queue queue_;
            
            // Mutex for synchronizing access to queue_
            mutable boost::mutex mutex_;
            
            // Variable to wait on when the queue is empty
            mutable boost::condition_variable emptyCond_;    
    };
    
} // namespace calc

#endif // CALC_TSP_QUEUE_HPP
