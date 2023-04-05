//
// Created by Randi Prince on 3/14/23.
//

#ifndef MSDSCRIPT_VAL_HPP
#define MSDSCRIPT_VAL_HPP


#include <ostream>
#include "pointer.hpp"

class Expr;

class Val {
public:
    virtual PTR(Expr) to_expr() = 0;
    virtual PTR(Val) add_to(PTR(Val) other) = 0;
    virtual PTR(Val) mult_with(PTR(Val) other) = 0;
    virtual bool equals(PTR(Val) other) = 0;
    virtual void print(std::ostream &stream) = 0;
    virtual bool is_true() = 0;
    std::string to_string();
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
};

class NumVal : public Val {
public:
    int val;
    NumVal(int val);
    PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) other);
    PTR(Val) mult_with(PTR(Val) other);
    bool equals(PTR(Val) other);
    void print(std::ostream &stream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
};

class BoolVal : public Val {
public:
    bool val;
    BoolVal(bool val);
    PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) other);
    PTR(Val) mult_with(PTR(Val) other);
    bool equals(PTR(Val) other);
    void print(std::ostream &stream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
};

class FunVal : public Val {
public:
    std::string formal_val;
    Expr* body;

    FunVal(std::string formal_val, Expr* body);
    PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) other);
    PTR(Val) mult_with(PTR(Val) other);
    bool equals(PTR(Val) other);
    void print(std::ostream &stream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
};

#endif //MSDSCRIPT_VAL_HPP
