// author: Rafal Witowski

#ifndef CALC_TSP_EXCEPTION_HPP
#define CALC_TSP_EXCEPTION_HPP

#include <string>
#include <exception>

namespace calc
{

    /**
     * Base exception class for exceptions thrown by other Tsp classes
     */
    class TspException : public std::exception
    {
        public:
            /** c-tor, sets exception's cause description text to what */
            TspException(const std::string &what) throw() : what_(what) {}
            
            /** d-tor */
            ~TspException() throw() {}
            
            /** Overriden method from std::exception, returns text desc. of exception cause */
            virtual const char* what() const throw()
            {
                return what_.c_str();
            }
            
        private:
            const std::string what_; // Cause of exception
    };

} // namespace cals

#endif // CALC_TSP_EXCEPTION_HPP
