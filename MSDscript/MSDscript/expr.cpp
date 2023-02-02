//
//  expr.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#include "expr.hpp"
#include <stdexcept>

Num::Num(int val){
    this->val = val;
}

bool Num::equals(Expr *e) {
    Num *other = dynamic_cast<Num*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

int Num::interp() {
    return this->val;
}

bool Num::has_variable() {
    return false;
}

Expr* Num::subst(std::string s, Expr *e) {
    return this;
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *e) {
    Add *other = dynamic_cast<Add*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

int Add::interp() {
    return (this->lhs->interp() + this->rhs->interp());
}

bool Add::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* Add::subst(std::string s, Expr *e) {
    return new Add(lhs->subst(s, e), rhs->subst(s, e));
}

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e) {
    Mult *other = dynamic_cast<Mult*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

int Mult::interp() {
    return (this->lhs->interp() * this->rhs->interp());
}

bool Mult::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* Mult::subst(std::string s, Expr *e) {
    return new Mult(lhs->subst(s, e), rhs->subst(s, e));
}

Variable::Variable(std::string val) {
    this->val = val;
}

bool Variable::equals(Expr *e) {
    Variable *other = dynamic_cast<Variable*>(e);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other->val);
    }
}

int Variable::interp() {
    throw std::runtime_error("Variable has no value!");
}

bool Variable::has_variable() {
    return true;
}

Expr* Variable::subst(std::string s, Expr *e) {
    if (this->val == s) {
        return e;
    }
    return this;
}
