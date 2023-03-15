//
// Created by Randi Prince on 3/14/23.
//

#ifndef MSDSCRIPT_VAL_HPP
#define MSDSCRIPT_VAL_HPP


#include <ostream>

class Expr;

class Val {
public:
    virtual Expr* to_expr() = 0;
    virtual Val* add_to(Val *other) = 0;
    virtual Val* mult_with(Val *other) = 0;
    virtual bool equals(Val *other) = 0;
    virtual void print(std::ostream &stream) = 0;
};

class NumVal : public Val {
public:
    int val;
    NumVal(int val);
    Expr* to_expr();
    Val* add_to(Val *other);
    Val* mult_with(Val *other);
    bool equals(Val *other);
    void print(std::ostream &stream);
};


#endif //MSDSCRIPT_VAL_HPP
