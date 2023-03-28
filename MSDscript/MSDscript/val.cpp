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
    return new NumVal((unsigned)this->val + (unsigned)other_num->val);
}

Val* NumVal::mult_with(Val *other) {
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL){
        throw std::runtime_error("mult of non-number");
    }
    return new NumVal((unsigned)this->val * (unsigned)other_num->val);
}

void NumVal::print(std::ostream &stream) {
    stream << this->val;
}

bool NumVal::is_true() {
    throw std::runtime_error("num val is not a boolean");
}

Val* NumVal::call(Val *actual_arg) {
    throw std::runtime_error("cannot call on numvals");
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
    if (this->val) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

bool BoolVal::is_true() {
    return this->val;
}

Val* BoolVal::call(Val *actual_arg) {
    throw std::runtime_error("cannot call on boolvals");
}

FunVal::FunVal(std::string formal_val, Expr *body) {
    this->formal_val = formal_val;
    this->body = body;
}

bool FunVal::equals(Val *e) {
    FunVal *other = dynamic_cast<FunVal*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->formal_val == other->formal_val) &&
               (this->body)->equals(other->body);
    }
}


Expr* FunVal::to_expr() {
    return new FunExpr(formal_val, body);
}

Val* FunVal::add_to(Val *other) {
    throw std::runtime_error("addition of non number");
}

Val* FunVal::mult_with(Val *other) {
    throw std::runtime_error("mult of non number");
}

void FunVal::print(std::ostream &stream) {
    stream << "(_fun (" << formal_val << ") ";
    body->print(stream);
    stream << ")";
}

bool FunVal::is_true() {
    throw std::runtime_error("Fun Val is not a boolean");
}

Val* FunVal::call(Val *actual_arg) {
    return (body->subst(formal_val, actual_arg->to_expr()))->interp();
}

std::string Val::to_string() {
    std::stringstream stringstream;
    this->print(stringstream);
    return stringstream.str();
}