//
// Created by Randi Prince on 4/11/23.
//

#ifndef MSDSCRIPT_ENV_HPP
#define MSDSCRIPT_ENV_HPP
#include "pointer.hpp"
#include <string>

class Val;

CLASS(Env) {
public:
    static PTR(Env) empty;
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class EmptyEnv : public Env {
public:
    EmptyEnv();
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv : public Env {
public:
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;

    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    PTR(Val) lookup(std::string find_name);

};

#endif //MSDSCRIPT_ENV_HPP
