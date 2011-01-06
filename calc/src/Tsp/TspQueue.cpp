#include "TspQueue.hpp"

namespace calc
{
                   
    /* get tsp and remove from queue, blocks if no tsp available */                                            
    PTsp TspQueue::pop()
    {
        boost::mutex::scoped_lock lock(mutex_);
	    while(queue_.empty())
		    emptyCond_.wait(lock);

	    PTsp tsp = queue_.front();
	    queue_.pop();
	    return tsp;
    }
    
    /* insert tsp at end of queue, sets the tsp state to QUEUED */    
    void TspQueue::push(PTsp tsp)
    {
	    boost::mutex::scoped_lock lock(mutex_);

        tsp->setQueued();        
	    queue_.push(tsp);            
	    emptyCond_.notify_one();
    }            
        
} // namespace calc

