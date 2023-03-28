//
//  expr.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#include "expr.hpp"
#include <stdexcept>
#include "tests.cpp"
#include "val.hpp"

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

Val* NumExpr::interp() {
    return new NumVal((unsigned)this->val);
}


Expr* NumExpr::subst(std::string s, Expr *e) {
    return this;
}

void NumExpr::print(std::ostream &stream) {
    stream << this->val;
}

void NumExpr::pretty_print(std::ostream &stream) {
    pretty_print_at(stream, prec_none, 0);
}

void NumExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
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

Val* AddExpr::interp() {
    return ((this->lhs->interp())->add_to(this->rhs->interp()));
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
    long pos = stream.tellp();
    this->lhs->pretty_print_at(stream, prec_add, &pos);
    stream << " + ";
    this->rhs->pretty_print_at(stream, prec_none, &pos);
}

void AddExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    if (ptype >= prec_add) {
        stream << "(";
    }
    this->lhs->pretty_print_at(stream, prec_add, pos);
    stream << " + ";
    this->rhs->pretty_print_at(stream, prec_none, pos);
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

Val* MultExpr::interp() {
    return ((this->lhs->interp())->mult_with(this->rhs->interp()));
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
    long pos = stream.tellp();
    this->lhs->pretty_print_at(stream, prec_mult, &pos);
    stream << " * ";
    this->rhs->pretty_print_at(stream, prec_add, &pos);
}

void MultExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    if (ptype >= prec_mult) {
        stream << "(";
    }
    this->lhs->pretty_print_at(stream, prec_mult, pos);
    stream << " * ";
    this->rhs->pretty_print_at(stream, prec_add, pos);
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

Val* VarExpr::interp() {
    throw std::runtime_error("VarExpr has no value!");
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
    pretty_print_at(stream, prec_none, 0);
}

void VarExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    stream << this->val;
}

LetExpr::LetExpr(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;

}

bool LetExpr::equals(Expr *e) {
    LetExpr *other = dynamic_cast<LetExpr*>(e);
    if (other == NULL){
        return false;
    } else {
        return ((this->lhs == other->lhs)
        && (this->rhs->equals(other->rhs))
        && (this->body->equals(other->body)));
    }
}

Val* LetExpr::interp() {
    std::string lhsNew = this->lhs;
    Expr* rhsNew = this->rhs;
    Expr* bodyNew = this->body;
    Val* rhsVal = rhsNew->interp();
    return bodyNew->subst(lhsNew, rhsVal->to_expr())->interp();
}

Expr* LetExpr::subst(std::string s, Expr *replace) {
    this->rhs->subst(s, replace);
    Expr* subBody = this->body;
    if (this->lhs != s) { // if lhs not the same, we sub the body
        subBody = subBody->subst(s, replace);
    }
    return new LetExpr(this->lhs, this->rhs->subst(s, replace), subBody);
}

void LetExpr::print(std::ostream &stream) {
    stream << "(_let ";
    stream << this->lhs;
    stream << "=";
    this->rhs->print(stream);
    stream << " _in " ;
    this->body->print(stream);
    stream << ")";
}

void LetExpr::pretty_print(std::ostream &stream) {
    stream << "_let ";
    stream << this->lhs;
    stream << " = ";
    long pos = 0;
    this->rhs->pretty_print_at(stream, prec_none, &pos);
    stream << "\n";
    pos = stream.tellp();
    stream << "_in  ";
    this->body->pretty_print_at(stream, prec_none, &pos);
}

void LetExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    if (ptype >= prec_let) {
        stream << "(";
    }
    long currentPos = stream.tellp();
    long spaces = currentPos - *pos;
    stream << "_let " << this->lhs << " = ";
    this->rhs->pretty_print_at(stream, prec_none, pos);
    stream << "\n";
    *pos = stream.tellp();
    int space_count = 0;
    while (space_count < spaces){
        stream << " ";
        space_count++;
    }
    stream << "_in  ";
    this->body->pretty_print_at(stream, prec_none, pos);
    if (ptype >= prec_let) {
        stream << ")";
    }
}

/***************************************************
* BoolExpr method definitions                       *
****************************************************/
BoolExpr::BoolExpr(bool val){
    this->val = val;
}

bool BoolExpr::equals(Expr *e) {
    BoolExpr *other = dynamic_cast<BoolExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

Val* BoolExpr::interp() {
    return new BoolVal(this->val);
}

Expr* BoolExpr::subst(std::string s, Expr *e) {
    return this;
}

void BoolExpr::print(std::ostream &stream) {
    if (this->val == true) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

void BoolExpr::pretty_print(std::ostream &stream) {
    pretty_print_at(stream, prec_none, 0);
}

void BoolExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    print(stream);
}

/***************************************************
* IfExpr method definitions                       *
****************************************************/
IfExpr::IfExpr(Expr *ifCondition, Expr *thenCondition, Expr *elseCondition) {
    this->ifCondition = ifCondition;
    this->thenCondition = thenCondition;
    this->elseConditon = elseCondition;
}

bool IfExpr::equals(Expr *e) {
    IfExpr *other = dynamic_cast<IfExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->ifCondition)->equals(other->ifCondition)
        && (this->thenCondition)->equals(other->thenCondition)
        && (this->elseConditon)->equals(other->elseConditon);
    }
}

Val* IfExpr::interp() {
    if ((this->ifCondition->interp())->is_true()) {
        return this->thenCondition->interp();
    } else {
        return this->elseConditon->interp();
    }
}


Expr* IfExpr::subst(std::string s, Expr *e) {
    Expr *ifConditionNew = ifCondition->subst(s, e);
    Expr *thenConditionNew = thenCondition->subst(s, e);
    Expr *elseConditionNew = elseConditon->subst(s, e);
    return new IfExpr(ifConditionNew, thenConditionNew, elseConditionNew);
}

void IfExpr::print(std::ostream &stream) {
    Expr *ifConditionNew = ifCondition;
    Expr *thenConditionNew = thenCondition;
    Expr *elseConditionNew = elseConditon;
    stream << "(_if ";
    ifConditionNew->print(stream);
    stream << " _then ";
    thenConditionNew->print(stream);
    stream << " _else ";
    elseConditionNew->print(stream);
    stream << ")";
}

void IfExpr::pretty_print(std::ostream &stream) {
    long pos = 0;
    stream << "_if ";
    this->ifCondition->pretty_print_at(stream, prec_none, &pos);
    stream << "\n";
    pos = stream.tellp();
    stream << "_then ";
    this->thenCondition->pretty_print_at(stream, prec_none, &pos);
    stream << "\n";
    pos = stream.tellp();
    stream << "_else ";
    this->elseConditon->pretty_print_at(stream, prec_none, &pos);
}

void IfExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    if (ptype >= prec_eq) {
        stream << "(";
    }
    long currentPos = stream.tellp();
    long spaces = currentPos - *pos;
    stream << "_if ";
    this->ifCondition->pretty_print_at(stream, prec_none, pos);
    stream << "\n";
    *pos = stream.tellp();
    int space_count = 0;
    while (space_count < spaces){
        stream << " ";
        space_count++;
    }
    stream << "_then ";
    this->thenCondition->pretty_print_at(stream, prec_none, pos);
    stream << "\n";
    space_count = 0;
    while (space_count < spaces){
        stream << " ";
        space_count++;
    }
    stream << "_else ";
    this->elseConditon->pretty_print_at(stream, prec_none, pos);
    if (ptype >= prec_eq) {
        stream << ")";
    }
}

/***************************************************
* EqExpr method definitions                       *
****************************************************/
EqExpr::EqExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(Expr *e) {
    EqExpr *other = dynamic_cast<EqExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs)->equals(other->lhs)
        && (this->rhs)->equals(other->rhs);
    }
}

Val* EqExpr::interp() {
    return new BoolVal((this->lhs->interp())->equals(this->rhs->interp()));
}


Expr* EqExpr::subst(std::string s, Expr *e) {
    Expr *lhsNew = lhs->subst(s, e);
    Expr *rhsNew = rhs->subst(s, e);
    return new EqExpr(lhsNew, rhsNew);
}

void EqExpr::print(std::ostream &stream) {
    stream << "(";
    lhs->print(stream);
    stream << "==";
    rhs->print(stream);
    stream << ")";
}

void EqExpr::pretty_print(std::ostream &stream) {
    long pos = 0;
    lhs->pretty_print_at(stream, prec_eq, &pos);
    stream << " == ";
    rhs->pretty_print_at(stream, prec_eq, &pos);
}

void EqExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {
    if (ptype > prec_none) {
        stream << "(";
        lhs->pretty_print_at(stream, prec_eq, pos);
        stream << " == ";
        rhs->pretty_print_at(stream, prec_eq, pos);
        stream << ")";
    } else {
        lhs->pretty_print_at(stream, prec_eq, pos);
        stream << " == ";
        rhs->pretty_print_at(stream, prec_eq, pos);
    }
}

FunExpr::FunExpr(std::string formal_arg, Expr *body) {
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(Expr *e) {
    FunExpr *other = dynamic_cast<FunExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->formal_arg == other->formal_arg) &&
                (this->body)->equals(other->body);
    }
}

Val* FunExpr::interp() {
    return new FunVal(this->formal_arg, this->body);
}

Expr* FunExpr::subst(std::string s, Expr *e) {
    if (s == formal_arg) {
        return new FunExpr(formal_arg, body);
    }
    return new FunExpr(formal_arg, body->subst(s, e));
}

void FunExpr::print(std::ostream &stream) {
    stream << "(_fun (" << formal_arg << ") ";
    body->print(stream);
    stream << ")";
}

void FunExpr::pretty_print(std::ostream &stream) {

}

void FunExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {

}

CallExpr::CallExpr(Expr *to_be_called, Expr *actual_arg) {
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;

}

bool CallExpr::equals(Expr *e) {
    CallExpr *other = dynamic_cast<CallExpr*>(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->to_be_called)->equals(other->to_be_called) &&
               (this->actual_arg)->equals(other->actual_arg);
    }
}

Val* CallExpr::interp() {
    return to_be_called->interp()->call(actual_arg->interp());
}

Expr* CallExpr::subst(std::string s, Expr *e) {
    Expr *to_be_called_new = to_be_called->subst(s, e);
    Expr *actual_arg_new = actual_arg->subst(s, e);
    return new CallExpr(to_be_called_new, actual_arg_new);
}

void CallExpr::print(std::ostream &stream) {
    to_be_called->print(stream);
    stream << "(";
    actual_arg->print(stream);
    stream << ")";
}

void CallExpr::pretty_print(std::ostream &stream) {

}

void CallExpr::pretty_print_at(std::ostream &stream, precedence_t ptype, long *pos) {

}