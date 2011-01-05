#ifndef CALC_TSP_EXCEPTION_HPP
#define CALC_TSP_EXCEPTION_HPP

#include <string>
#include <exception>

namespace calc
{

    class TspException : public std::exception
    {
        public:
            TspException(const std::string &what) throw() {}
            ~TspException() throw() {}
            
            virtual const char* what() const throw()
            {
                return what_.c_str();
            }
            
        private:
            const std::string what_;
    };

}

#endif // CALC_TSP_EXCEPTION_HPP
