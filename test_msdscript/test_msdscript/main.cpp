#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "exec.h"

static std::string random_expr_string();

int main(int argc, char **argv) {
    srand(clock());
    const char * const interp_argv[] = { argv[1], "--interp" };
    const char * const print_argv[] = { argv[1], "--print" };
    const char * const pretty_print_argv[] = { argv[1], "--pretty-print" };
    for (int i = 0; i < 100; i++) {
        std::string in = random_expr_string();
        std::cout << "Trying " << in << "\n";
        ExecResult interp_result1 = exec_program(2, interp_argv, in);
        ExecResult print_result = exec_program(2, print_argv, in);
        if (argc == 2) {
            ExecResult interp_result2 = exec_program(2, interp_argv, print_result.out);
            if (interp_result1.out != interp_result2.out) {
                std::cout << "interp result 1: " << interp_result1.out << "\n";
                std::cout << "interp result 2: " << interp_result2.out << "\n";
                throw std::runtime_error("different results");
            }
        } else if (argc == 3) {
            const char * const interp_argv2[] = { argv[2], "--interp" };
            const char * const print_argv2[] = { argv[2], "--print" };
            const char * const pretty_print_argv2[] = { argv[2], "--pretty-print" };
            ExecResult interp_result3 = exec_program(2, interp_argv2, in);
            ExecResult print_result2 = exec_program(2, print_argv2, in);
            ExecResult pretty_print_result = exec_program(2, pretty_print_argv, in);
            ExecResult pretty_print_result2 = exec_program(2, pretty_print_argv2, in);
            if (interp_result1.out != interp_result3.out) {
                std::cout << "interp result 1: " << interp_result1.out << "\n";
                std::cout << "interp result 2: " << interp_result3.out << "\n";
                throw std::runtime_error("different interp results!");
            }
            if (print_result.out != print_result2.out) {
                std::cout << "print result 1: " << print_result.out << "\n";
                std::cout << "print result 2: " << print_result2.out << "\n";
                throw std::runtime_error("different print results!");
            }
            if (pretty_print_result.out != pretty_print_result2.out) {
                std::cout << "pretty print result 1: " << pretty_print_result.out << "\n";
                std::cout << "pretty print result 2: " << pretty_print_result2.out << "\n";
                throw std::runtime_error("different pretty print results!");
            }
        } else {
            throw std::runtime_error("too many arguments!!!!!");
        }

    }
    return 0;
}

std::string random_expr_string() {
    int random = (rand() % 15);
    if (random < 6) {
        return std::to_string(rand());
    } else if (random > 5 && random < 9){
        return random_expr_string() + "+" + random_expr_string();
    } else if (random > 8 && random < 12){
        return random_expr_string() + "*" + random_expr_string();
    } else {
        return "_let x = 5 _in x";
    }
}