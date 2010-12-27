#ifndef TSP_QUEUE_HPP
#define TSP_QUEUE_HPP

#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "Tsp.hpp"

typedef boost::shared_ptr<Tsp> PTsp;

class TspQueue
{
    public:
        TspQueue() : lastId_(0) {}
        
        PTsp pop()
        {
            boost::mutex::scoped_lock lock(mutex_);
			while(queue_.empty())
				emptyCond_.wait(lock);

			PTsp tsp = queue_.front();
			queue_.pop();
			return tsp;
        }
        
        Tsp::TspId push(PTsp tsp)
        {
			boost::mutex::scoped_lock lock(mutex_);

			tsp->setId(++lastId_);
            tsp->setState(Tsp::QUEUED);
            
			queue_.push(tsp);            

			emptyCond_.notify_all();
			return lastId_;        
        }
        
    private:
        typedef std::queue<PTsp> Queue;
        Queue queue_;
        Tsp::TspId lastId_;
        
        mutable boost::mutex mutex_;
        mutable boost::condition_variable emptyCond_;    
};

#endif
