//
//  commandLine.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/15/23.
//
#define CATCH_CONFIG_RUNNER
#include "commandLine.hpp"
#include "catch.h"
#include <iostream>
#include <cstdlib>

void use_arguments(int argc, char * argv[]) {
    bool testSeen = false;
    if (argc == 1) {
        exit(0);
    }
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];
        if (argument == "--help") {
            std::cout << "The following arguments are allowed: " << std::endl;
            std::cout << "--help" << std::endl;
            std::cout << "--test" << std::endl;
            std::cout << "or no arguments at all!" << std::endl;
            exit(0);
        } else if (argument == "--test") {
            if (!testSeen) {
                if (Catch::Session().run(1,argv) != 0){
                    exit(1);
                }
                std::cout << "Test passed!" << std::endl;
                testSeen = true;
            } else {
                std::cerr << "Test already seen..." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Command not found" << std::endl;
            exit(1);
        }
    }
}
