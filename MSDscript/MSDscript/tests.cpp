//
//  tests.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/31/23.
//

#include "catch.h"
#include "expr.hpp"

/**
* \file tests.cpp
* \brief contains tests for msdscript program
* \author Randi Prince
*/


/**
* \@brief Test NumExpr equals
* Tests of numExpr equals function
*/
TEST_CASE("Test NumExpr equals") {
    
    SECTION("AddExpr should be TRUE") {
        CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
        CHECK((new NumExpr(0))->equals(new NumExpr(0)) == true);
        CHECK((new NumExpr(-10))->equals(new NumExpr(-10)) == true);
    }
    
    SECTION("AddExpr should be FALSE") {
        CHECK((new NumExpr(15))->equals(new NumExpr(-15)) == false);
        CHECK((new NumExpr(0))->equals(new NumExpr(-1)) == false);
        CHECK((new NumExpr(3))->equals(new NumExpr(4)) == false);
    }
}

/**
* \@brief Test AddExpr equals
* Tests of AddExpr equals function
*/
TEST_CASE("Test AddExpr equals") {
    
    SECTION("AddExpr should be TRUE") {
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == true);
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(0)))->equals(new AddExpr(new NumExpr(0), new NumExpr(0))) == true);
        CHECK((new AddExpr(new NumExpr(-10), new NumExpr(-100)))->equals(new AddExpr(new NumExpr(-10), new NumExpr(-100))) == true);
    }
    
    SECTION("AddExpr should be FALSE") {
        CHECK((new AddExpr(new NumExpr(-100), new NumExpr(-10)))->equals(new AddExpr(new NumExpr(-10), new NumExpr(-100))) == false);
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(1)))->equals(new AddExpr(new NumExpr(50), new NumExpr(1))) == false);
        CHECK((new AddExpr(new NumExpr(1234), new NumExpr(4321)))->equals(new AddExpr(new NumExpr(-1234), new NumExpr(-4321))) == false);
    }
    
}

/**
* \@brief Test MultExpr equals
* Tests of MultExpr equals function
*/
TEST_CASE("Test MultExpr equals") {
    
    SECTION("MultExpr should be TRUE") {
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->equals(new MultExpr(new NumExpr(1), new NumExpr(2))) == true);
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->equals(new MultExpr(new NumExpr(0), new NumExpr(0))) == true);
        CHECK((new MultExpr(new NumExpr(-10), new NumExpr(-100)))->equals(new MultExpr(new NumExpr(-10), new NumExpr(-100))) == true);
    }
    
    SECTION("MultExpr should be FALSE") {
        CHECK((new MultExpr(new NumExpr(-100), new NumExpr(-10)))->equals(new MultExpr(new NumExpr(-10), new NumExpr(-100))) == false);
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->equals(new MultExpr(new NumExpr(0), new NumExpr(1))) == false);
        CHECK((new MultExpr(new NumExpr(98765), new NumExpr(98765)))->equals(new MultExpr(new NumExpr(98765), new NumExpr(-98765))) == false);
    }
    
}

/**
* \@brief Test VarExpr equals
* Tests of VarExpr equals function
*/
TEST_CASE("Test VarExpr equals") {
    
    SECTION("Var should be TRUE") {
        CHECK((new VarExpr("hi"))->equals(new VarExpr("hi")) == true);
        CHECK((new VarExpr("HELLOworld"))->equals(new VarExpr("HELLOworld")) == true);
        CHECK((new VarExpr("codingisfun"))->equals(new VarExpr("codingisfun")) == true);
    }
    
    SECTION("Var should be FALSE") {
        CHECK((new VarExpr("hi"))->equals(new VarExpr("bye")) == false);
        CHECK((new VarExpr("HELLOworld"))->equals(new VarExpr("worldHELLO")) == false);
        CHECK((new VarExpr("codingisfun"))->equals(new VarExpr("codingisfun!")) == false);
    }
    
}

/**
* \@brief Test Interp function
* Tests of interp function for each class
*/
TEST_CASE("Interp Function") {
    
    SECTION("NUM Expr Interp") {
        CHECK((new NumExpr(1))->interp() == 1);
        CHECK((new NumExpr(0))->interp() == 0);
        CHECK((new NumExpr(-432))->interp() == -432);
    }
    
    SECTION("ADD Expr Interp") {
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->interp() == 3);
        CHECK((new AddExpr(new NumExpr(-10), new NumExpr(2)))->interp() == -8);
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(0)))->interp() == 0);
    }
    
    SECTION("MULT Expr Interp") {
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->interp() == 2);
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->interp() == 0);
        CHECK((new MultExpr(new NumExpr(-50), new NumExpr(4)))->interp() == -200);
    }
    
    SECTION("VARIABLE Expr Interp") {
        CHECK_THROWS_WITH((new VarExpr("R"))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr("codingisfun"))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr(""))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr(" "))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new AddExpr(new VarExpr("m"), new NumExpr(21)))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new MultExpr(new VarExpr("s"), new NumExpr(23)))->interp(), "VarExpr has no value!");
    }
}

/**
* \@brief Test has_variable function
* Tests of has_variable function for each class
*/
TEST_CASE("Has VarExpr Function") {
    
    SECTION("NUM has variable") {
        CHECK((new NumExpr(123))->has_variable() == false);
        CHECK((new NumExpr(-85))->has_variable() == false);
        CHECK((new NumExpr(0))->has_variable() == false);
    }
    
    SECTION("ADD has variable") { //add/fix
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->has_variable() == false);
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->has_variable() == false);
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->has_variable() == false);
        CHECK((new AddExpr(new VarExpr("x"), new NumExpr(2)))->has_variable() == true);

    }
    
    SECTION("MULT has variable") { //fix
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->has_variable() == false);
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->has_variable() == false);
        CHECK((new MultExpr(new NumExpr(-50), new NumExpr(4)))->has_variable() == false);
        CHECK((new MultExpr(new VarExpr("a"), new NumExpr(4)))->has_variable() == true);
    }
    
    SECTION("VARIABLE has variable") {
        CHECK((new VarExpr("R"))->has_variable() == true);
        CHECK((new VarExpr("codingisfun"))->has_variable() == true);
        CHECK((new VarExpr(""))->has_variable() == true);
        CHECK((new VarExpr(" "))->has_variable() == true);
        CHECK((new AddExpr(new VarExpr("m"), new NumExpr(21)))->has_variable() == true);
        CHECK((new MultExpr(new VarExpr("s"), new NumExpr(23)))->has_variable() == true);
    }
}

/**
* \@brief Test subst function
* Tests of subst function for each class
*/
TEST_CASE("Substitution (subst) function") {
    
    SECTION("NUM Expr subst") {
        CHECK((new NumExpr(1))->subst("R", new NumExpr(2))->equals(new NumExpr(1)) == true);
        CHECK((new NumExpr(-1))->subst("R", new NumExpr(2))->equals(new NumExpr(-1)) == true);
        CHECK((new NumExpr(0))->subst("R", new NumExpr(2))->equals(new NumExpr(0)) == true);
        CHECK((new NumExpr(1))->subst("R", new NumExpr(2))->equals(new NumExpr(2)) == false);
        CHECK((new NumExpr(1))->subst("1", new NumExpr(2))->equals(new NumExpr(2)) == false);
        CHECK((new NumExpr(1))->subst("0", new NumExpr(0))->equals(new NumExpr(0)) == false);
    }
    
    SECTION("ADD Expr subst") { //fix
        CHECK((new AddExpr(new VarExpr("R"), new NumExpr(1)))->subst("R", new VarExpr("P"))->equals(new AddExpr(new VarExpr("P"), new NumExpr(1))) == true);
        CHECK((new AddExpr(new VarExpr("M"), new NumExpr(0)))->subst("M", new VarExpr("S"))->equals(new AddExpr(new VarExpr("S"), new NumExpr(0))) == true);
        CHECK((new AddExpr(new VarExpr("R"), new NumExpr(1)))->subst("R", new VarExpr("P"))->equals(new AddExpr(new VarExpr("R"), new NumExpr(1))) == false);
        CHECK((new AddExpr(new VarExpr("h"), new NumExpr(-8764)))->subst("h", new VarExpr("u"))->equals(new AddExpr(new VarExpr("u"), new NumExpr(1))) == false);
    }
    
    SECTION("MULT Expr subst") { // fix
        CHECK((new MultExpr(new VarExpr("d"), new NumExpr(42)))->subst("d", new VarExpr("q"))->equals(new MultExpr(new VarExpr("q"), new NumExpr(42))) == true);
        CHECK((new MultExpr(new VarExpr("d"), new NumExpr(42)))->subst("d", new VarExpr("q"))->equals(new MultExpr(new VarExpr("q"), new NumExpr(42))) == true);
        CHECK((new MultExpr(new VarExpr("i"), new NumExpr(0)))->subst("i", new VarExpr("y"))->equals(new MultExpr(new VarExpr("y"), new NumExpr(0))) == true);
        CHECK((new MultExpr(new VarExpr("AH"), new NumExpr(-432)))->subst("AH", new VarExpr("hi"))->equals(new MultExpr(new VarExpr("hi"), new NumExpr(432))) == false);
        CHECK((new MultExpr(new VarExpr("whatisup"), new NumExpr(858585)))->subst("whatisup", new VarExpr("whatup"))->equals(new MultExpr(new VarExpr("whatsup"), new NumExpr(858585))) == false);
    }
    
    SECTION("VARIABLE Expr subst") {
        CHECK((new VarExpr("R"))->subst("R", new VarExpr("P"))->equals(new VarExpr("P")) == true);
        CHECK((new VarExpr("R"))->subst("R", new VarExpr("r"))->equals(new VarExpr("r")) == true);
        CHECK((new VarExpr("a"))->subst("a", new VarExpr("b"))->equals(new VarExpr("b")) == true);
        CHECK((new VarExpr("h"))->subst("h", new VarExpr("h"))->equals(new VarExpr("h")) == true);
        CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
               ->subst("x", new VarExpr("y"))
               ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );
        CHECK( (new VarExpr("x"))
               ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
               ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );
    }
}
