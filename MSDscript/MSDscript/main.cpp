//
//  main.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/15/23.
//


#include <iostream>
#include "commandLine.hpp"
//#include "tests.cpp"

/**
* \mainpage MSDScript
* \author Randi Prince
* \date 02-02-2023
*/
int main(int argc, char * argv[]) {
    try {
        use_arguments(argc, argv);
        return 0;
    } catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

}