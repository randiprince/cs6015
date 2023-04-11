//
//  tests.cpp
//  MSDscript
//
//  Created by Randi Prince on 1/31/23.
//

#include "catch.h"
#include "expr.hpp"
#include "parse.hpp"
#include "val.hpp"
#include "pointer.hpp"

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
    
    SECTION("NUMExpr should be TRUE") {
        CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(1)) == true);
        CHECK((NEW(NumExpr)(0))->equals(NEW(NumExpr)(0)) == true);
        CHECK((NEW(NumExpr)(-10))->equals(NEW(NumExpr)(-10)) == true);
    }
    
    SECTION("NUMExpr should be FALSE") {
        CHECK((NEW(NumExpr)(15))->equals(NEW(NumExpr)(-15)) == false);
        CHECK((NEW(NumExpr)(0))->equals(NEW(NumExpr)(-1)) == false);
        CHECK((NEW(NumExpr)(3))->equals(NEW(NumExpr)(4)) == false);
        CHECK((NEW(NumExpr)(3))->equals(NULL) == false);
    }
}

/**
* \@brief Test AddExpr equals
* Tests of AddExpr equals function
*/
TEST_CASE("Test AddExpr equals") {
    
    SECTION("AddExpr should be TRUE") {
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
        CHECK((NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->equals(NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0))) == true);
        CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100)))->equals(NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100))) == true);
    }
    
    SECTION("AddExpr should be FALSE") {
        CHECK((NEW(AddExpr)(NEW(NumExpr)(-100), NEW(NumExpr)(-10)))->equals(NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100))) == false);
        CHECK((NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(1)))->equals(NEW(AddExpr)(NEW(NumExpr)(50), NEW(NumExpr)(1))) == false);
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1234), NEW(NumExpr)(4321)))->equals(NEW(AddExpr)(NEW(NumExpr)(-1234), NEW(NumExpr)(-4321))) == false);
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1234), NEW(NumExpr)(4321)))->equals(NULL) == false);
    }
    
}

/**
* \@brief Test MultExpr equals
* Tests of MultExpr equals function
*/
TEST_CASE("Test MultExpr equals") {
    
    SECTION("MultExpr should be TRUE") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
        CHECK((NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->equals(NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0))) == true);
        CHECK((NEW(MultExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100)))->equals(NEW(MultExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100))) == true);
    }
    
    SECTION("MultExpr should be FALSE") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(-100), NEW(NumExpr)(-10)))->equals(NEW(MultExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-100))) == false);
        CHECK((NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->equals(NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(1))) == false);
        CHECK((NEW(MultExpr)(NEW(NumExpr)(98765), NEW(NumExpr)(98765)))->equals(NEW(MultExpr)(NEW(NumExpr)(98765), NEW(NumExpr)(-98765))) == false);
        CHECK((NEW(MultExpr)(NEW(NumExpr)(98765), NEW(NumExpr)(98765)))->equals(NULL) == false);
    }
    
}

/**
* \@brief Test VarExpr equals
* Tests of VarExpr equals function
*/
TEST_CASE("Test VarExpr equals") {
    
    SECTION("Var should be TRUE") {
        CHECK((NEW(VarExpr)("hi"))->equals(NEW(VarExpr)("hi")) == true);
        CHECK((NEW(VarExpr)("HELLOworld"))->equals(NEW(VarExpr)("HELLOworld")) == true);
        CHECK((NEW(VarExpr)("codingisfun"))->equals(NEW(VarExpr)("codingisfun")) == true);
    }
    
    SECTION("Var should be FALSE") {
        CHECK((NEW(VarExpr)("hi"))->equals(NEW(VarExpr)("bye")) == false);
        CHECK((NEW(VarExpr)("HELLOworld"))->equals(NEW(VarExpr)("worldHELLO")) == false);
        CHECK((NEW(VarExpr)("codingisfun"))->equals(NEW(VarExpr)("codingisfun!")) == false);
        CHECK((NEW(VarExpr)("codingisfun"))->equals(NULL) == false);
    }
    
}

/**
* \@brief Test LetExpr equals
* Tests of LetExpr equals function
*/
TEST_CASE("Test BoolExpr equals") {

    SECTION("BoolExpr should be TRUE") {
        CHECK((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(true)) == true);
        CHECK((NEW(BoolExpr)(false))->equals(NEW(BoolExpr)(false)) == true);
    }

    SECTION("BoolExpr should be FALSE") {
        CHECK((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(false)) == false);
        CHECK((NEW(BoolExpr)(false))->equals(NEW(BoolExpr)(true)) == false);
    }

}

TEST_CASE("Test IfExpr equals") {

    SECTION("IfExpr should be TRUE") {
        CHECK((NEW(IfExpr) (NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(NumExpr)(2)))->equals(NEW(IfExpr) (NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(NumExpr)(2))) == true);
        CHECK((NEW(IfExpr) (NEW(BoolExpr)(false), NEW(NumExpr)(0), NEW(NumExpr)(-1)))->equals(NEW(IfExpr) (NEW(BoolExpr)(false), NEW(NumExpr)(0), NEW(NumExpr)(-1))) == true);
    }

    SECTION("IfExpr should be FALSE") {
        CHECK((NEW(IfExpr) (NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(NumExpr)(2)))
        ->equals(NEW(IfExpr) (NEW(BoolExpr)(false), NEW(NumExpr)(3), NEW(NumExpr)(2))) == false);
        CHECK((NEW(IfExpr) (NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(NumExpr)(2)))
        ->equals(NEW(IfExpr) (NEW(BoolExpr)(true), NEW(NumExpr)(-3), NEW(NumExpr)(2))) == false);
    }
}

TEST_CASE("Test EqExpr equals") {

    SECTION("EqExpr should be TRUE") {
        CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
                      ->equals(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
        CHECK((NEW(EqExpr)(NEW(NumExpr)(1000), NEW(NumExpr)(2001)))
                      ->equals(NEW(EqExpr)(NEW(NumExpr)(1000), NEW(NumExpr)(2001))) == true);
    }

    SECTION("EqExpr should be FALSE") {
        CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
        ->equals(NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(2))) == false);
        CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
        ->equals(NEW(EqExpr)(NEW(NumExpr)(-1), NEW(NumExpr)(2))) == false);
    }

}

TEST_CASE("Test FunExpr equals") {

    SECTION("FunExpr should be TRUE") {
        CHECK((NEW(FunExpr)("x", NEW(NumExpr)(2)))
                      ->equals(NEW(FunExpr)("x", NEW(NumExpr)(2))) == true);
        CHECK((NEW(FunExpr)("y", NEW(NumExpr)(2001)))
                      ->equals(NEW(FunExpr)("y", NEW(NumExpr)(2001))) == true);
    }

    SECTION("FunExpr should be FALSE") {
        CHECK((NEW(FunExpr)("x", NEW(NumExpr)(2)))
                      ->equals(NEW(FunExpr)("x", NEW(NumExpr)(-2))) == false);
        CHECK((NEW(FunExpr)("y", NEW(NumExpr)(2001)))
                      ->equals(NEW(FunExpr)("y", NEW(NumExpr)(2002))) == false);
    }
}

TEST_CASE("Test CallExpr equals") {

    SECTION("CallExpr should be TRUE") {
        CHECK((NEW(CallExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
                      ->equals(NEW(CallExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
        CHECK((NEW(CallExpr)(NEW(NumExpr)(1000), NEW(NumExpr)(2001)))
                      ->equals(NEW(CallExpr)(NEW(NumExpr)(1000), NEW(NumExpr)(2001))) == true);
    }

    SECTION("CallExpr should be FALSE") {
        CHECK((NEW(CallExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
                      ->equals(NEW(CallExpr)(NEW(NumExpr)(0), NEW(NumExpr)(2))) == false);
        CHECK((NEW(CallExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
                      ->equals(NEW(CallExpr)(NEW(NumExpr)(-1), NEW(NumExpr)(2))) == false);
    }

}

TEST_CASE("Test FunVal equals") {

    SECTION("FunVal should be TRUE") {
        CHECK((NEW(FunVal)("x", NEW(NumExpr)(2), Env::empty))
                      ->equals(NEW(FunVal)("x", NEW(NumExpr)(2), Env::empty)) == true);
        CHECK((NEW(FunVal)("y", NEW(NumExpr)(2001), Env::empty))
                      ->equals(NEW(FunVal)("y", NEW(NumExpr)(2001), Env::empty)) == true);
    }

    SECTION("FunVal should be FALSE") {
        CHECK((NEW(FunVal)("x", NEW(NumExpr)(2), Env::empty))
                      ->equals(NEW(FunVal)("x", NEW(NumExpr)(-2), Env::empty)) == false);
        CHECK((NEW(FunVal)("y", NEW(NumExpr)(2001), Env::empty))
                      ->equals(NEW(FunVal)("y", NEW(NumExpr)(2002), Env::empty)) == false);
    }
}

TEST_CASE("Test BoolVal equals") {

    SECTION("BoolVal should be TRUE") {
        CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(true)) == true);
        CHECK((NEW(BoolVal)(false))->equals(NEW(BoolVal)(false)) == true);
    }

    SECTION("BoolVal should be FALSE") {
        CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(false)) == false);
        CHECK((NEW(BoolVal)(false))->equals(NEW(BoolVal)(true)) == false);
    }

}

TEST_CASE("Test NumVal equals") {

    SECTION("NumVal should be TRUE") {
        CHECK((NEW(NumVal)(5))->equals(NEW(NumVal)(5)) == true);
        CHECK((NEW(NumVal)(-10))->equals(NEW(NumVal)(-10)) == true);
    }

    SECTION("NumVal should be FALSE") {
        CHECK((NEW(NumVal)(0))->equals(NEW(NumVal)(1)) == false);
        CHECK((NEW(NumVal)(-505))->equals(NEW(NumVal)(505)) == false);
    }

}

/**
* \@brief Test Interp function
* Tests of interp function for each class
*/
TEST_CASE("Interp Function") {
    
    SECTION("NUM Expr Interp") {
        CHECK((NEW(NumExpr)(1))->interp(Env::empty)->equals(NEW(NumVal)(1)));
        CHECK((NEW(NumExpr)(0))->interp(Env::empty)->equals(NEW(NumVal)(0)));
        CHECK((NEW(NumExpr)(-432))->interp(Env::empty)->equals(NEW(NumVal)(-432)));
    }
    
    SECTION("ADD Expr Interp") {
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->interp(Env::empty)->equals(NEW(NumVal)(3)));
        CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(2)))->interp(Env::empty)->equals(NEW(NumVal)(-8)));
        CHECK((NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->interp(Env::empty)->equals(NEW(NumVal)(0)));
    }
    
    SECTION("MULT Expr Interp") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->interp(Env::empty)->equals(NEW(NumVal)(2)));
        CHECK((NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->interp(Env::empty)->equals(NEW(NumVal)(0)));
        CHECK((NEW(MultExpr)(NEW(NumExpr)(-50), NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(NumVal)(-200)));
    }
    
    SECTION("VARIABLE Expr Interp") {
        CHECK_THROWS_WITH((NEW(VarExpr)("R"))->interp(Env::empty), "free variable: R");
        CHECK_THROWS_WITH((NEW(VarExpr)("codingisfun"))->interp(Env::empty), "free variable: codingisfun");
        CHECK_THROWS_WITH((NEW(VarExpr)(""))->interp(Env::empty), "free variable: ");
        CHECK_THROWS_WITH((NEW(VarExpr)(" "))->interp(Env::empty), "free variable:  ");
        CHECK_THROWS_WITH((NEW(AddExpr)(NEW(VarExpr)("m"), NEW(NumExpr)(21)))->interp(Env::empty), "free variable: m");
        CHECK_THROWS_WITH((NEW(MultExpr)(NEW(VarExpr)("s"), NEW(NumExpr)(23)))->interp(Env::empty), "free variable: s");
    }

    SECTION("LetExpr Interp") {
        CHECK((NEW(LetExpr)("x", NEW(AddExpr)( NEW(NumExpr)(5), NEW(NumExpr) (2)), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty)->equals(NEW(NumVal)(8)));
    }
}

TEST_CASE("to string function") {

    SECTION("NUM Expr to string") {
        CHECK( (NEW(NumExpr)(10))->to_string() == "10" );
        CHECK( (NEW(NumExpr)(0))->to_string() == "0" );
        CHECK( (NEW(NumExpr)(-10))->to_string() == "-10" );
        CHECK( (NEW(NumExpr)(12345))->to_string() == "12345" );
    }

    SECTION("AddExpr to string") {
        CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)))->to_string() == "(10+15)" );
        CHECK((NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->to_string() == "(0+0)" );
        CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(15)))->to_string() == "(-10+15)" );
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))->to_string() == "(1+(2+3))");
        CHECK((NEW(AddExpr)(NEW(VarExpr)("hello"), NEW(VarExpr)("world!")))->to_string() == "(hello+world!)");
    }

    SECTION("MultExpr to string") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(5)))->to_string() == "(1*5)" );
        CHECK((NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->to_string() == "(0*0)" );
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(-5)))->to_string() == "(1*-5)" );
        CHECK((NEW(MultExpr)(NEW(NumExpr)(-1), NEW(NumExpr)(-5)))->to_string() == "(-1*-5)" );
        CHECK((NEW(MultExpr)(NEW(VarExpr)("hello"), NEW(VarExpr)("world!")))->to_string() == "(hello*world!)");

    }

    SECTION("VARIABLE Expr to string") {
        CHECK((NEW(VarExpr)("x"))->to_string() == "x" );
        CHECK((NEW(VarExpr)("R"))->to_string() == "R" );
        CHECK((NEW(VarExpr)("mSd"))->to_string() == "mSd" );
        CHECK((NEW(VarExpr)("hello"))->to_string() == "hello" );
    }

    SECTION("LetExpr to string") {
        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(21),
                NEW(AddExpr)(
                        NEW(LetExpr)(
                                "y",
                                NEW(NumExpr)(0),
                                NEW(AddExpr)(
                                        NEW(VarExpr)("y"),
                                        NEW(NumExpr)(33))),
                        NEW(VarExpr)("x"))))->to_string() == "(_let x=21 _in ((_let y=0 _in (y+33))+x))");
        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(5),
                NEW(MultExpr)(
                        NEW(LetExpr)(
                                "y",
                                NEW(NumExpr)(3),
                                NEW(MultExpr)(
                                        NEW(VarExpr)("y"),
                                        NEW(NumExpr)(2))),
                        NEW(VarExpr)("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y*2))*x))");
    }
}

TEST_CASE("to string PRETTY function") {

    SECTION("NUM Expr to string pretty") {
        CHECK( (NEW(NumExpr)(10))->to_string_pretty() == "10" );
        CHECK( (NEW(NumExpr)(0))->to_string_pretty() == "0" );
        CHECK( (NEW(NumExpr)(-10))->to_string_pretty() == "-10" );
        CHECK( (NEW(NumExpr)(12345))->to_string_pretty() == "12345" );
    }

    SECTION("AddExpr to string pretty") {
        CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)))->to_string_pretty() == "10 + 15");
        CHECK((NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->to_string_pretty() == "0 + 0");
        CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(15)))->to_string_pretty() == "-10 + 15");
        CHECK((NEW(AddExpr)(NEW(VarExpr)("hello"), NEW(VarExpr)("world!")))->to_string_pretty() == "hello + world!");
        CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))->to_string_pretty() == "1 + 2 + 3");
        CHECK((NEW(AddExpr)(
                NEW(AddExpr)(
                        NEW(NumExpr)(10),
                        NEW(AddExpr)(
                                NEW(AddExpr)(
                                        NEW(NumExpr)(10),
                                        NEW(NumExpr)(10)),
                                NEW(NumExpr)(10))),
                NEW(AddExpr)(
                        NEW(NumExpr)(10),
                        NEW(NumExpr)(10))))
                      ->to_string_pretty()  == "(10 + (10 + 10) + 10) + 10 + 10");
    }

    SECTION("MultExpr to string pretty") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(5)))->to_string_pretty() == "1 * 5");
        CHECK((NEW(MultExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0)))->to_string_pretty() == "0 * 0");
        CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(-5)))->to_string_pretty() == "1 * -5");
        CHECK((NEW(MultExpr)(NEW(NumExpr)(-1), NEW(NumExpr)(-5)))->to_string_pretty() == "-1 * -5");
        CHECK((NEW(MultExpr)(NEW(VarExpr)("hello"), NEW(VarExpr)("world!")))->to_string_pretty() == "hello * world!");
        CHECK((NEW(MultExpr)(
                NEW(MultExpr)(
                    NEW(NumExpr)(10),
                    NEW(MultExpr)(
                        NEW(MultExpr)(
                                NEW(NumExpr)(10),
                                NEW(NumExpr)(10)),
                        NEW(NumExpr)(10))),
                NEW(MultExpr)(
                        NEW(NumExpr)(10),
                        NEW(NumExpr)(10))))
                      ->to_string_pretty()  == "(10 * (10 * 10) * 10) * 10 * 10");
    }

    SECTION("VARIABLE Expr to string pretty") {
        CHECK((NEW(VarExpr)("x"))->to_string_pretty() == "x" );
        CHECK((NEW(VarExpr)("R"))->to_string_pretty() == "R" );
        CHECK((NEW(VarExpr)("mSd"))->to_string_pretty() == "mSd" );
        CHECK((NEW(VarExpr)("hello"))->to_string_pretty() == "hello" );
        CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->to_string_pretty() == "(1 * 2) * (3 + 4)");
    }

    SECTION("to string pretty for combo Expr including LetExpr") {
        CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(3)))->to_string_pretty() == "(1 + 2) * 3");
        CHECK((NEW(MultExpr)(
                NEW(MultExpr)(
                        NEW(AddExpr)(
                                NEW(NumExpr)(9),
                                NEW(NumExpr)(9)),
                        NEW(AddExpr)(
                                NEW(MultExpr)(
                                        NEW(NumExpr)(10),
                                        NEW(NumExpr)(10)),
                                NEW(NumExpr)(10))),
                NEW(MultExpr)(
                        NEW(NumExpr)(10),
                        NEW(NumExpr)(10))))
                      ->to_string_pretty()  == "((9 + 9) * (10 * 10 + 10)) * 10 * 10");
        CHECK((NEW(AddExpr)(
                NEW(AddExpr)(
                        NEW(AddExpr)(
                                NEW(NumExpr)(9),
                                NEW(NumExpr)(9)),
                        NEW(AddExpr)(
                                NEW(MultExpr)(
                                        NEW(NumExpr)(10),
                                        NEW(NumExpr)(10)),
                                NEW(NumExpr)(10))),
                NEW(MultExpr)(
                        NEW(NumExpr)(10),
                        NEW(NumExpr)(10))))
                      ->to_string_pretty()  == "((9 + 9) + 10 * 10 + 10) + 10 * 10");
        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(5),
                NEW(AddExpr)(
                        NEW(LetExpr)(
                                "y",
                                NEW(NumExpr)(3),
                                NEW(AddExpr)(
                                        NEW(VarExpr)("y"),
                                        NEW(NumExpr)(2))),
                        NEW(VarExpr)("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((NEW(MultExpr)(
                NEW(MultExpr)(
                        NEW(NumExpr) (2),
                        NEW(LetExpr)(
                                "x",
                                NEW(NumExpr)(5),
                                NEW(AddExpr)(
                                        NEW(VarExpr)("x"),
                                        NEW(NumExpr)(1)))),
                NEW(NumExpr)(3)))
                ->to_string_pretty() == "(2 * (_let x = 5\n"
                                        "      _in  x + 1)) * 3");
        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(5),
                NEW(AddExpr)(
                        NEW(LetExpr)(
                                "y",
                                NEW(NumExpr)(3),
                                NEW(AddExpr)(
                                        NEW(VarExpr)("y"),
                                        NEW(NumExpr)(2))),
                        NEW(VarExpr)("x"))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");
        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(5),
                NEW(AddExpr)(
                        NEW(LetExpr)(
                                "y",
                                NEW(NumExpr)(3),
                                NEW(AddExpr)(
                                        NEW(VarExpr)("y"),
                                        NEW(NumExpr)(2))),
                        NEW(VarExpr)("x"))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");


        CHECK((NEW(LetExpr)(
                "x",
                NEW(NumExpr)(5),
                NEW(AddExpr)(
                        NEW(VarExpr)("x"),
                        NEW(NumExpr)(1))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  x + 1");

    }
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(NEW(NumExpr)(1)) );
    CHECK( parse_str("(((1)))")->equals(NEW(NumExpr)(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(NEW(NumExpr)(1)) );
    CHECK( parse_str("10")->equals(NEW(NumExpr)(10)) );
    CHECK( parse_str("-3")->equals(NEW(NumExpr)(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(NEW(NumExpr)(5)) );

    CHECK( parse_str("x")->equals(NEW(VarExpr)("x")) == true);
    CHECK( parse_str("xyz")->equals(NEW(VarExpr)("xyz")) == true);
    CHECK( parse_str("xYz")->equals(NEW(VarExpr)("xYz")) == true);

    CHECK( parse_str("x + y")->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) );
    CHECK( parse_str("x * y")->equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) );
    CHECK( parse_str("z * x + y")
                   ->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("z"), NEW(VarExpr)("x")),
                                    NEW(VarExpr)("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(NEW(MultExpr)(NEW(VarExpr)("z"),
                                     NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) ));
}

TEST_CASE("Val tests for thrown error") {
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->call(0), "cannot call on boolvals");
    CHECK_THROWS_WITH((NEW(NumVal)(true))->call(0), "cannot call on numvals");
    CHECK_THROWS_WITH((NEW(NumVal)(true))->is_true(), "num val is not a boolean");
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->add_to(0), "addition of non number");
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->mult_with(0), "mult of non number");
    CHECK_THROWS_WITH((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->add_to(0), "addition of non number");
    CHECK_THROWS_WITH((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->mult_with(0), "mult of non number");
    CHECK_THROWS_WITH((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->is_true(), "Fun Val is not a boolean");
}