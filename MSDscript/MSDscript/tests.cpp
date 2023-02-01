//
//  tests.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/31/23.
//

#include <stdio.h>
#include "catch.h"
#include "expr.hpp"

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

TEST_CASE("Test Variable equals") {
    
    SECTION("Var should be TRUE") {
        CHECK((new Variable("hi"))->equals(new Variable("hi")) == true);
        CHECK((new Variable("HELLOworld"))->equals(new Variable("HELLOworld")) == true);
        CHECK((new Variable("codingisfun"))->equals(new Variable("codingisfun")) == true);
    }
    
    SECTION("Var should be FALSE") {
        CHECK((new Variable("hi"))->equals(new Variable("bye")) == false);
        CHECK((new Variable("HELLOworld"))->equals(new Variable("worldHELLO")) == false);
        CHECK((new Variable("codingisfun"))->equals(new Variable("codingisfun!")) == false);
    }
    
}

TEST_CASE("Interp Function") {
    
    SECTION("NUM Expr Interp") {
        CHECK((new Num(1))->interp() == 1);
        CHECK((new Num(0))->interp() == 0);
        CHECK((new Num(-432))->interp() == -432);
    }
    
    SECTION("ADD Expr Interp") {
        CHECK((new Add(new Num(1),new Num(2)))->interp() == 3);
        CHECK((new Add(new Num(-10),new Num(2)))->interp() == -8);
        CHECK((new Add(new Num(0),new Num(0)))->interp() == 0);
    }
    
    SECTION("MULT Expr Interp") {
        CHECK((new Mult(new Num(1),new Num(2)))->interp() == 2);
        CHECK((new Mult(new Num(0),new Num(0)))->interp() == 0);
        CHECK((new Mult(new Num(-50),new Num(4)))->interp() == -200);
    }
    
    SECTION("VARIABLE Expr Interp") {
        CHECK_THROWS_WITH((new Variable("R"))->interp(), "Variable has no value!");
        CHECK_THROWS_WITH((new Variable("codingisfun"))->interp(), "Variable has no value!");
        CHECK_THROWS_WITH((new Variable(""))->interp(), "Variable has no value!");
        CHECK_THROWS_WITH((new Variable(" "))->interp(), "Variable has no value!");
        CHECK_THROWS_WITH((new Add(new Variable("m"), new Num(21)))->interp(), "Variable has no value!");
        CHECK_THROWS_WITH((new Mult(new Variable("s"), new Num(23)))->interp(), "Variable has no value!");
    }
}

TEST_CASE("Has Variable Function") {
    
    SECTION("NUM has variable") {
        CHECK((new Num(123))->has_variable() == false);
        CHECK((new Num(-85))->has_variable() == false);
        CHECK((new Num(0))->has_variable() == false);
    }
    
    SECTION("ADD has variable") {
        CHECK((new Add(new Num(1),new Num(2)))->has_variable() == false);
        CHECK((new Add(new Num(1),new Num(2)))->has_variable() == false);
        CHECK((new Add(new Num(1),new Num(2)))->has_variable() == false);
    }
    
    SECTION("MULT has variable") {
        CHECK((new Mult(new Num(1),new Num(2)))->has_variable() == false);
        CHECK((new Mult(new Num(0),new Num(0)))->has_variable() == false);
        CHECK((new Mult(new Num(-50),new Num(4)))->has_variable() == false);
    }
    
    SECTION("VARIABLE has variable") {
        CHECK((new Variable("R"))->has_variable() == true);
        CHECK((new Variable("codingisfun"))->has_variable() == true);
        CHECK((new Variable(""))->has_variable() == true);
        CHECK((new Variable(" "))->has_variable() == true);
        CHECK((new Add(new Variable("m"), new Num(21)))->has_variable() == false);
        CHECK((new Mult(new Variable("s"), new Num(23)))->has_variable() == false);
    }
}

TEST_CASE("Substitution (subst) function") {
    
    SECTION("NUM Expr subst") {
        CHECK((new Num(1))->subst("R", new Num(2))->equals(new Num(1)) == true);
        CHECK((new Num(-1))->subst("R", new Num(2))->equals(new Num(-1)) == true);
        CHECK((new Num(0))->subst("R", new Num(2))->equals(new Num(0)) == true);
        CHECK((new Num(1))->subst("R", new Num(2))->equals(new Num(2)) == false);
        CHECK((new Num(1))->subst("1", new Num(2))->equals(new Num(2)) == false);
        CHECK((new Num(1))->subst("0", new Num(0))->equals(new Num(0)) == false);
    }
    
    SECTION("ADD Expr subst") {
        CHECK((new Add(new Variable("R"), new Num(1)))->subst("R", new Variable("P"))->equals(new Add(new Variable("P"), new Num(1))) == true);
        CHECK((new Add(new Variable("M"), new Num(0)))->subst("M", new Variable("S"))->equals(new Add(new Variable("S"), new Num(0))) == true);
        CHECK((new Add(new Variable("R"), new Num(1)))->subst("R", new Variable("P"))->equals(new Add(new Variable("R"), new Num(1))) == false);
        CHECK((new Add(new Variable("h"), new Num(-8764)))->subst("h", new Variable("u"))->equals(new Add(new Variable("u"), new Num(1))) == false);
    }
    
    SECTION("MULT Expr subst") {
        CHECK((new Mult(new Variable("d"), new Num(42)))->subst("d", new Variable("q"))->equals(new Mult(new Variable("q"), new Num(42))) == true);
        CHECK((new Mult(new Variable("d"), new Num(42)))->subst("d", new Variable("q"))->equals(new Mult(new Variable("q"), new Num(42))) == true);
        CHECK((new Mult(new Variable("i"), new Num(0)))->subst("i", new Variable("y"))->equals(new Mult(new Variable("y"), new Num(0))) == true);
        CHECK((new Mult(new Variable("AH"), new Num(-432)))->subst("AH", new Variable("hi"))->equals(new Mult(new Variable("hi"), new Num(432))) == false);
        CHECK((new Mult(new Variable("whatisup"), new Num(858585)))->subst("whatisup", new Variable("whatup"))->equals(new Mult(new Variable("whatsup"), new Num(858585))) == false);
    }
    
    SECTION("VARIABLE Expr subst") {
        CHECK((new Variable("R"))->subst("R", new Variable("P"))->equals(new Variable("P")) == true);
        CHECK((new Variable("R"))->subst("R", new Variable("r"))->equals(new Variable("r")) == true);
        CHECK((new Variable("a"))->subst("a", new Variable("b"))->equals(new Variable("b")) == true);
        CHECK((new Variable("h"))->subst("h", new Variable("h"))->equals(new Variable("h")) == true);
    }
}
