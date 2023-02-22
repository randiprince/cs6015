//
//  commandLine.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/15/23.
//
#define CATCH_CONFIG_RUNNER
#include "commandLine.hpp"
#include "catch.h"
#include "parse.hpp"
#include <iostream>
#include <cstdlib>

/**
* \file commandLine.cpp
* \brief contains use_argument function definition
* \author Randi Prince
*/

void use_arguments(int argc, char * argv[]) {
    bool testSeen = false;
    if (argc == 1) { // if there is no command, exit
        exit(0);
    }
    // loop through the arguments to separate and handle each command
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];
        if (argument == "--help") {
            std::cout << "The following arguments are allowed: " << std::endl;
            std::cout << "--help" << std::endl;
            std::cout << "--test" << std::endl;
            std::cout << "--interp" << std::endl;
            std::cout << "--pretty-print" << std::endl;
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
        } else if (argument == "--interp") {
            Expr* input = parse_expr(std::cin);
            std::cout << input->interp();
            exit(0);
        } else if (argument == "--pretty-print") {
            Expr* input = parse_expr(std::cin);
            std::cout << input->to_string_pretty();
            exit(0);
        } else {
            std::cerr << "Command not found" << std::endl;
            exit(1);
        }
    }
}
