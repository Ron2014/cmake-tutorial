// A simple program that computes the square root of a number
#include <iostream>
#include <string>

#include "TutorialConfig.h"
// #ifdef USE_MYMATH
// for #cmakedefine01 USE_MYMATH
#if defined(USE_MYMATH) && (USE_MYMATH == 1) 
#include "MathFunctions.h"
#else
#include <cmath>
#endif

int main(int argc, char* argv[])
{
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // calculate square root
    // const double outputValue = sqrt(inputValue);
    
// #ifdef USE_MYMATH
// for #cmakedefine01 USE_MYMATH
#if defined(USE_MYMATH) && (USE_MYMATH == 1) 
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif

    std::cout << "The square root of " << inputValue << " is " << outputValue
                << std::endl;
    return 0;
}
