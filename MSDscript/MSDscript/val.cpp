//
// Created by Randi Prince on 3/14/23.
//

#include "val.hpp"
#include "expr.hpp"

NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(PTR(Val) e) {
    PTR(NumVal) other = CAST(NumVal)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

PTR(Val) NumVal::add_to(PTR(Val) other) {
    PTR(NumVal) other_num = CAST(NumVal)(other);
    if (other_num == NULL){
        throw std::runtime_error("add of non-number");
    }
    return NEW(NumVal)((unsigned)this->val + (unsigned)other_num->val);
}

PTR(Val) NumVal::mult_with(PTR(Val) other) {
    PTR(NumVal) other_num = CAST(NumVal)(other);
    if (other_num == NULL){
        throw std::runtime_error("mult of non-number");
    }
    return NEW(NumVal)((unsigned)this->val * (unsigned)other_num->val);
}

void NumVal::print(std::ostream &stream) {
    stream << this->val;
}

bool NumVal::is_true() {
    throw std::runtime_error("num val is not a boolean");
}

PTR(Val) NumVal::call(PTR(Val) actual_arg) {
    throw std::runtime_error("cannot call on numvals");
}

BoolVal::BoolVal(bool val) {
    this->val = val;
}

bool BoolVal::equals(PTR(Val) e) {
    PTR(BoolVal) other = CAST(BoolVal)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

PTR(Val) BoolVal::add_to(PTR(Val) other) {
    throw std::runtime_error("addition of non number");
}

PTR(Val) BoolVal::mult_with(PTR(Val) other) {
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

PTR(Val) BoolVal::call(PTR(Val) actual_arg) {
    throw std::runtime_error("cannot call on boolvals");
}

FunVal::FunVal(std::string formal_val, PTR(Expr) body, PTR(Env) env) {
    this->formal_val = formal_val;
    this->body = body;
    this->env = env;
}

bool FunVal::equals(PTR(Val) e) {
    PTR(FunVal) other = CAST(FunVal)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->formal_val == other->formal_val) &&
               (this->body)->equals(other->body);
    }
}


PTR(Val) FunVal::add_to(PTR(Val) other) {
    throw std::runtime_error("addition of non number");
}

PTR(Val) FunVal::mult_with(PTR(Val) other) {
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

PTR(Val) FunVal::call(PTR(Val) actual_arg) {
    return body->interp(NEW(ExtendedEnv)(formal_val, actual_arg, env));
}

std::string Val::to_string() {
    std::stringstream stringstream;
    this->print(stringstream);
    return stringstream.str();
}