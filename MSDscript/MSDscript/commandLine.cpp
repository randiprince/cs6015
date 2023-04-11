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
#include "val.hpp"
#include <iostream>
#include <cstdlib>
#include "pointer.hpp"
#include "env.hpp"

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
            PTR(Expr) input = parse_expr(std::cin);
            PTR(Val) val = input->interp(Env::empty);
            std::cout << val->to_string() << "\n";
        } else if (argument == "--print") {
            PTR(Expr) input = parse_expr(std::cin);
            input->print(std::cout);
        } else if (argument == "--pretty-print") {
            PTR(Expr) input = parse_expr(std::cin);
            std::cout << input->to_string_pretty();
        } else {
            std::cerr << "Command not found" << std::endl;
            exit(1);
        }
        std::cout << "\n";
    }
}
