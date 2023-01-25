//
//  expr.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#include "expr.hpp"
#include "catch.h"

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

TEST_CASE("Test Num equals") {
    
    SECTION("Add should be TRUE") {
        CHECK((new Num(1))->equals(new Num(1)) == true);
        CHECK((new Num(0))->equals(new Num(0)) == true);
        CHECK((new Num(-10))->equals(new Num(-10)) == true);
    }
    
    SECTION("Add should be FALSE") {
        CHECK((new Num(15))->equals(new Num(-15)) == false);
        CHECK((new Num(0))->equals(new Num(-1)) == false);
        CHECK((new Num(3))->equals(new Num(4)) == false);
    }
}

TEST_CASE("Test Add equals") {
    
    SECTION("Add should be TRUE") {
        CHECK((new Add(new Num(1),new Num(2)))->equals(new Add(new Num(1),new Num(2))) == true);
        CHECK((new Add(new Num(0),new Num(0)))->equals(new Add(new Num(0),new Num(0))) == true);
        CHECK((new Add(new Num(-10),new Num(-100)))->equals(new Add(new Num(-10),new Num(-100))) == true);
    }
    
    SECTION("Add should be FALSE") {
        CHECK((new Add(new Num(-100),new Num(-10)))->equals(new Add(new Num(-10),new Num(-100))) == false);
        CHECK((new Add(new Num(0),new Num(1)))->equals(new Add(new Num(50),new Num(1))) == false);
        CHECK((new Add(new Num(1234),new Num(4321)))->equals(new Add(new Num(-1234),new Num(-4321))) == false);
    }
    
}

TEST_CASE("Test Mult equals") {
    
    SECTION("Mult should be TRUE") {
        CHECK((new Mult(new Num(1),new Num(2)))->equals(new Mult(new Num(1),new Num(2))) == true);
        CHECK((new Mult(new Num(0),new Num(0)))->equals(new Mult(new Num(0),new Num(0))) == true);
        CHECK((new Mult(new Num(-10),new Num(-100)))->equals(new Mult(new Num(-10),new Num(-100))) == true);
    }
    
    SECTION("Mult should be FALSE") {
        CHECK((new Mult(new Num(-100),new Num(-10)))->equals(new Mult(new Num(-10),new Num(-100))) == false);
        CHECK((new Mult(new Num(0),new Num(0)))->equals(new Mult(new Num(0),new Num(1))) == false);
        CHECK((new Mult(new Num(98765),new Num(98765)))->equals(new Mult(new Num(98765),new Num(-98765))) == false);
    }
    
    
}
