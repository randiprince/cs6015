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

bool NumExpr::equals(PTR(Expr) e) {
    PTR(NumExpr) other = CAST(NumExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

PTR(Val) NumExpr::interp() {
    return NEW(NumVal)((unsigned)this->val);
}


PTR(Expr) NumExpr::subst(std::string s, PTR(Expr) e) {
    return THIS;
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

AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(PTR(Expr) e) {
    PTR(AddExpr)other = CAST(AddExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

PTR(Val) AddExpr::interp() {
    return ((this->lhs->interp())->add_to(this->rhs->interp()));
}


PTR(Expr) AddExpr::subst(std::string s, PTR(Expr) e) {
    return NEW(AddExpr)(lhs->subst(s, e), rhs->subst(s, e));
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
MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(PTR(Expr) e) {
    PTR(MultExpr) other = CAST(MultExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs->equals(other->lhs) && this->rhs->equals(other->rhs));
    }
}

PTR(Val) MultExpr::interp() {
    return ((this->lhs->interp())->mult_with(this->rhs->interp()));
}


PTR(Expr) MultExpr::subst(std::string s, PTR(Expr) e) {
    return NEW(MultExpr)(lhs->subst(s, e), rhs->subst(s, e));
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

bool VarExpr::equals(PTR(Expr) e) {
    PTR(VarExpr )other = CAST(VarExpr)(e);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other->val);
    }
}

PTR(Val) VarExpr::interp() {
    throw std::runtime_error("VarExpr has no value!");
}


PTR(Expr) VarExpr::subst(std::string s, PTR(Expr) e) {
    if (this->val == s) {
        return e;
    }
    return THIS;
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

LetExpr::LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;

}

bool LetExpr::equals(PTR(Expr) e) {
    PTR(LetExpr) other = CAST(LetExpr)(e);
    if (other == NULL){
        return false;
    } else {
        return ((this->lhs == other->lhs)
        && (this->rhs->equals(other->rhs))
        && (this->body->equals(other->body)));
    }
}

PTR(Val) LetExpr::interp() {
    std::string lhsNew = this->lhs;
    PTR(Expr) rhsNew = this->rhs;
    PTR(Expr) bodyNew = this->body;
    PTR(Val) rhsVal = rhsNew->interp();
    return bodyNew->subst(lhsNew, rhsVal->to_expr())->interp();
}

PTR(Expr) LetExpr::subst(std::string s, PTR(Expr) replace) {
    this->rhs->subst(s, replace);
    PTR(Expr) subBody = this->body;
    if (this->lhs != s) { // if lhs not the same, we sub the body
        subBody = subBody->subst(s, replace);
    }
    return NEW(LetExpr)(this->lhs, this->rhs->subst(s, replace), subBody);
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

bool BoolExpr::equals(PTR(Expr) e) {
    PTR(BoolExpr) other = CAST(BoolExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->val == other->val);
    }
}

PTR(Val) BoolExpr::interp() {
    return NEW(BoolVal)(this->val);
}

PTR(Expr) BoolExpr::subst(std::string s, PTR(Expr) e) {
    return THIS;
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
IfExpr::IfExpr(PTR(Expr) ifCondition, PTR(Expr) thenCondition, PTR(Expr) elseCondition) {
    this->ifCondition = ifCondition;
    this->thenCondition = thenCondition;
    this->elseConditon = elseCondition;
}

bool IfExpr::equals(PTR(Expr) e) {
    PTR(IfExpr) other = CAST(IfExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->ifCondition)->equals(other->ifCondition)
        && (this->thenCondition)->equals(other->thenCondition)
        && (this->elseConditon)->equals(other->elseConditon);
    }
}

PTR(Val) IfExpr::interp() {
    if ((this->ifCondition->interp())->is_true()) {
        return this->thenCondition->interp();
    } else {
        return this->elseConditon->interp();
    }
}


PTR(Expr) IfExpr::subst(std::string s, PTR(Expr) e) {
    PTR(Expr) ifConditionNew = ifCondition->subst(s, e);
    PTR(Expr) thenConditionNew = thenCondition->subst(s, e);
    PTR(Expr) elseConditionNew = elseConditon->subst(s, e);
    return NEW(IfExpr)(ifConditionNew, thenConditionNew, elseConditionNew);
}

void IfExpr::print(std::ostream &stream) {
    PTR(Expr) ifConditionNew = ifCondition;
    PTR(Expr) thenConditionNew = thenCondition;
    PTR(Expr) elseConditionNew = elseConditon;
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
EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(PTR(Expr) e) {
    PTR(EqExpr) other = CAST(EqExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->lhs)->equals(other->lhs)
        && (this->rhs)->equals(other->rhs);
    }
}

PTR(Val) EqExpr::interp() {
    return NEW(BoolVal)((this->lhs->interp())->equals(this->rhs->interp()));
}


PTR(Expr) EqExpr::subst(std::string s, PTR(Expr) e) {
    PTR(Expr) lhsNew = lhs->subst(s, e);
    PTR(Expr) rhsNew = rhs->subst(s, e);
    return NEW(EqExpr)(lhsNew, rhsNew);
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

FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body) {
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr) e) {
    PTR(FunExpr) other = CAST(FunExpr)(e);
    if (other == NULL) {
        return false;
    } else {
        return (this->formal_arg == other->formal_arg) &&
                (this->body)->equals(other->body);
    }
}

PTR(Val) FunExpr::interp() {
    return NEW(FunVal)(this->formal_arg, this->body);
}

PTR(Expr) FunExpr::subst(std::string s, PTR(Expr) e) {
    if (s == formal_arg) {
        return NEW(FunExpr)(formal_arg, body);
    }
    return NEW(FunExpr)(formal_arg, body->subst(s, e));
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

CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg) {
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;

}

bool CallExpr::equals(PTR(Expr) e) {
    PTR(CallExpr) other = CAST(CallExpr) (e);
    if (other == NULL) {
        return false;
    } else {
        return (this->to_be_called)->equals(other->to_be_called) &&
               (this->actual_arg)->equals(other->actual_arg);
    }
}

PTR(Val) CallExpr::interp() {
    return to_be_called->interp()->call(actual_arg->interp());
}

PTR(Expr) CallExpr::subst(std::string s, PTR(Expr) e) {
    PTR(Expr) to_be_called_new = to_be_called->subst(s, e);
    PTR(Expr) actual_arg_new = actual_arg->subst(s, e);
    return NEW(CallExpr)(to_be_called_new, actual_arg_new);
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