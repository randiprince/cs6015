//
//  expr.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#include "expr.hpp"
#include <stdexcept>

/**
* \file expr.cpp
* \brief contains expression class
definitions for all the sub classes of Expr class
* \author Randi Prince
*/

NumExpr::NumExpr(int val){
    this->val = val;
}

bool NumExpr::equals(Expr *e) {
    NumExpr *other = dynamic_cast<NumExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

int NumExpr::interp() {
    return this->val;
}

bool NumExpr::has_variable() {
    return false;
}

Expr* NumExpr::subst(std::string s, Expr *e) {
    return this;
}

// constructor for AddExpr
AddExpr::AddExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(Expr *e) {
    AddExpr *other = dynamic_cast<AddExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

int AddExpr::interp() {
    return (this->lhs->interp() + this->rhs->interp());
}

bool AddExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* AddExpr::subst(std::string s, Expr *e) {
    return new AddExpr(lhs->subst(s, e), rhs->subst(s, e));
}

// constructor for MultExpr
MultExpr::MultExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(Expr *e) {
    MultExpr *other = dynamic_cast<MultExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

int MultExpr::interp() {
    return (this->lhs->interp() * this->rhs->interp());
}

bool MultExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* MultExpr::subst(std::string s, Expr *e) {
    return new MultExpr(lhs->subst(s, e), rhs->subst(s, e));
}

// constructor for VarExpr
VarExpr::VarExpr(std::string val) {
    this->val = val;
}

bool VarExpr::equals(Expr *e) {
    VarExpr *other = dynamic_cast<VarExpr*>(e);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other->val);
    }
}

int VarExpr::interp() {
    throw std::runtime_error("VarExpr has no value!");
}

bool VarExpr::has_variable() {
    return true;
}

Expr* VarExpr::subst(std::string s, Expr *e) {
    if (this->val == s) {
        return e;
    }
    return this;
}
