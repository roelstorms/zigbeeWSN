#include <boost/thread.hpp>
#include "CallableClass.cpp"
#include "inputhandler.h"

int main()
    {
    // Using a callable object as thread function
    int numberIterations = 20;
    InputHandler c(numberIterations);
    boost::thread t(c);
     
    for (int i=0; i<10; i++)
    {
    std::cout<< i <<" – Do something in main method." << std::endl;
    }
     
    return 0;
    }
     

