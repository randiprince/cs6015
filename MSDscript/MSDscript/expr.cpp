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

std::string Expr::to_string() {
    std::stringstream stringstream;
    this->print(stringstream);
    return stringstream.str();
}

std::string Expr::to_string_pretty() {
    std::stringstream stringstream;
    this->pretty_print(stringstream);
    return stringstream.str();
}

/***************************************************
* NumExpr method definitions                       *
****************************************************/
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

void NumExpr::print(std::ostream &stream) {
    stream << this->val;
}

void NumExpr::pretty_print(std::ostream &stream) {
    pretty_print_at(stream, prec_none);
}

void NumExpr::pretty_print_at(std::ostream &stream, precedence_t ptype) {
    stream << this->val;
}

/********************************************
*  AddExpr method definitions               *
*********************************************/

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

void AddExpr::print(std::ostream &stream) {
    stream << "(";
    this->lhs->print(stream);
    stream << "+";
    this->rhs->print(stream);
    stream << ")";
}

void AddExpr::pretty_print(std::ostream &stream) {
    this->lhs->pretty_print_at(stream, prec_add);
    stream << " + ";
    this->rhs->pretty_print_at(stream, prec_none);
}

void AddExpr::pretty_print_at(std::ostream &stream, precedence_t ptype) {
    if (ptype >= prec_add) {
        stream << "(";
    }
    this->lhs->pretty_print_at(stream, prec_add);
    stream << " + ";
    this->rhs->pretty_print_at(stream, prec_none);
    if (ptype >= prec_add) {
        stream << ")";
    }
}

/*******************************************
*  MultExpr method definitions             *
********************************************/
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

void MultExpr::print(std::ostream &stream) {
    stream << "(";
    this->lhs->print(stream);
    stream << "*";
    this->rhs->print(stream);
    stream << ")";
}

void MultExpr::pretty_print(std::ostream &stream) {
    this->lhs->pretty_print_at(stream, prec_mult);
    stream << " * ";
    this->rhs->pretty_print_at(stream, prec_add);
}

void MultExpr::pretty_print_at(std::ostream &stream, precedence_t ptype) {
    if (ptype == prec_mult) {
        stream << "(";
    }
    this->lhs->pretty_print_at(stream, prec_mult);
    stream << " * ";
    this->rhs->pretty_print_at(stream, prec_add);
    if (ptype == prec_mult) {
        stream << ")";
    }
}

/********************************************
*  VarExpr Method Definitions               *
*********************************************/
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

void VarExpr::print(std::ostream &stream) {
    stream << this->val;
}

void VarExpr::pretty_print(std::ostream &stream) {
    pretty_print_at(stream, prec_none);
}

void VarExpr::pretty_print_at(std::ostream &stream, precedence_t ptype) {
    stream << this->val;
}
