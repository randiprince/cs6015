//
// Created by Randi Prince on 3/14/23.
//

#include "val.hpp"
#include "expr.hpp"

NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(Val *e) {
    NumVal *other = dynamic_cast<NumVal*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

Expr* NumVal::to_expr() {
    return new NumExpr(this->val);
}

Val* NumVal::add_to(Val *other) {
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL){
        throw std::runtime_error("add of non-number");
    }
    return new NumVal(this->val + other_num->val);
}

Val* NumVal::mult_with(Val *other) {
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL){
        throw std::runtime_error("mult of non-number");
    }
    return new NumVal(this->val * other_num->val);
}

void NumVal::print(std::ostream &stream) {
    stream << this->val;
}

bool NumVal::is_true() {
    throw std::runtime_error("num val is not a boolean");
}

BoolVal::BoolVal(bool val) {
    this->val = val;
}

bool BoolVal::equals(Val *e) {
    BoolVal *other = dynamic_cast<BoolVal*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

Expr* BoolVal::to_expr() {
    return new BoolExpr(this->val);
}

Val* BoolVal::add_to(Val *other) {
    throw std::runtime_error("addition of non number");
}

Val* BoolVal::mult_with(Val *other) {
    throw std::runtime_error("mult of non number");
}

void BoolVal::print(std::ostream &stream) {
    stream << this->val;
}

bool BoolVal::is_true() {
    return this->val;
}