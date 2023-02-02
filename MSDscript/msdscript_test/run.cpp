//
//  run.cpp
//  msdscript_test
//
//  Created by Randi Prince on 2/2/23.
//

//#include "run.hpp"

extern "C" {
    #include "run.hpp"
};

#define CATCH_CONFIG_RUNNER
#include "../MSDscript/catch.h"

bool run_tests() {
    const char *argv[] = { "msdscript_test" };
    return (Catch::Session().run(1, argv) == 0);
}
