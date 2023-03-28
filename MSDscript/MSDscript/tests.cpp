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
        CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
        CHECK((new NumExpr(0))->equals(new NumExpr(0)) == true);
        CHECK((new NumExpr(-10))->equals(new NumExpr(-10)) == true);
    }
    
    SECTION("NUMExpr should be FALSE") {
        CHECK((new NumExpr(15))->equals(new NumExpr(-15)) == false);
        CHECK((new NumExpr(0))->equals(new NumExpr(-1)) == false);
        CHECK((new NumExpr(3))->equals(new NumExpr(4)) == false);
        CHECK((new NumExpr(3))->equals(NULL) == false);
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
        CHECK((new AddExpr(new NumExpr(1234), new NumExpr(4321)))->equals(NULL) == false);
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
        CHECK((new MultExpr(new NumExpr(98765), new NumExpr(98765)))->equals(NULL) == false);
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
        CHECK((new VarExpr("codingisfun"))->equals(NULL) == false);
    }
    
}

/**
* \@brief Test LetExpr equals
* Tests of LetExpr equals function
*/
TEST_CASE("Test BoolExpr equals") {

    SECTION("BoolExpr should be TRUE") {
        CHECK((new BoolExpr(true))->equals(new BoolExpr(true)) == true);
        CHECK((new BoolExpr(false))->equals(new BoolExpr(false)) == true);
    }

    SECTION("BoolExpr should be FALSE") {
        CHECK((new BoolExpr(true))->equals(new BoolExpr(false)) == false);
        CHECK((new BoolExpr(false))->equals(new BoolExpr(true)) == false);
    }

}

TEST_CASE("Test IfExpr equals") {

    SECTION("IfExpr should be TRUE") {
        CHECK((new IfExpr (new BoolExpr(true), new NumExpr(3), new NumExpr(2)))->equals(new IfExpr (new BoolExpr(true), new NumExpr(3), new NumExpr(2))) == true);
        CHECK((new IfExpr (new BoolExpr(false), new NumExpr(0), new NumExpr(-1)))->equals(new IfExpr (new BoolExpr(false), new NumExpr(0), new NumExpr(-1))) == true);
    }

    SECTION("IfExpr should be FALSE") {
        CHECK((new IfExpr (new BoolExpr(true), new NumExpr(3), new NumExpr(2)))
        ->equals(new IfExpr (new BoolExpr(false), new NumExpr(3), new NumExpr(2))) == false);
        CHECK((new IfExpr (new BoolExpr(true), new NumExpr(3), new NumExpr(2)))
        ->equals(new IfExpr (new BoolExpr(true), new NumExpr(-3), new NumExpr(2))) == false);
    }
}

TEST_CASE("Test EqExpr equals") {

    SECTION("EqExpr should be TRUE") {
        CHECK((new EqExpr(new NumExpr(1), new NumExpr(2)))
                      ->equals(new EqExpr(new NumExpr(1), new NumExpr(2))) == true);
        CHECK((new EqExpr(new NumExpr(1000), new NumExpr(2001)))
                      ->equals(new EqExpr(new NumExpr(1000), new NumExpr(2001))) == true);
    }

    SECTION("EqExpr should be FALSE") {
        CHECK((new EqExpr(new NumExpr(1), new NumExpr(2)))
        ->equals(new EqExpr(new NumExpr(0), new NumExpr(2))) == false);
        CHECK((new EqExpr(new NumExpr(1), new NumExpr(2)))
        ->equals(new EqExpr(new NumExpr(-1), new NumExpr(2))) == false);
    }

}

TEST_CASE("Test FunExpr equals") {

    SECTION("FunExpr should be TRUE") {
        CHECK((new FunExpr("x", new NumExpr(2)))
                      ->equals(new FunExpr("x", new NumExpr(2))) == true);
        CHECK((new FunExpr("y", new NumExpr(2001)))
                      ->equals(new FunExpr("y", new NumExpr(2001))) == true);
    }

    SECTION("FunExpr should be FALSE") {
        CHECK((new FunExpr("x", new NumExpr(2)))
                      ->equals(new FunExpr("x", new NumExpr(-2))) == false);
        CHECK((new FunExpr("y", new NumExpr(2001)))
                      ->equals(new FunExpr("y", new NumExpr(2002))) == false);
    }
}

TEST_CASE("Test CallExpr equals") {

    SECTION("CallExpr should be TRUE") {
        CHECK((new CallExpr(new NumExpr(1), new NumExpr(2)))
                      ->equals(new CallExpr(new NumExpr(1), new NumExpr(2))) == true);
        CHECK((new CallExpr(new NumExpr(1000), new NumExpr(2001)))
                      ->equals(new CallExpr(new NumExpr(1000), new NumExpr(2001))) == true);
    }

    SECTION("CallExpr should be FALSE") {
        CHECK((new CallExpr(new NumExpr(1), new NumExpr(2)))
                      ->equals(new CallExpr(new NumExpr(0), new NumExpr(2))) == false);
        CHECK((new CallExpr(new NumExpr(1), new NumExpr(2)))
                      ->equals(new CallExpr(new NumExpr(-1), new NumExpr(2))) == false);
    }

}

TEST_CASE("Test FunVal equals") {

    SECTION("FunVal should be TRUE") {
        CHECK((new FunVal("x", new NumExpr(2)))
                      ->equals(new FunVal("x", new NumExpr(2))) == true);
        CHECK((new FunVal("y", new NumExpr(2001)))
                      ->equals(new FunVal("y", new NumExpr(2001))) == true);
    }

    SECTION("FunVal should be FALSE") {
        CHECK((new FunVal("x", new NumExpr(2)))
                      ->equals(new FunVal("x", new NumExpr(-2))) == false);
        CHECK((new FunVal("y", new NumExpr(2001)))
                      ->equals(new FunVal("y", new NumExpr(2002))) == false);
    }
}

TEST_CASE("Test BoolVal equals") {

    SECTION("BoolVal should be TRUE") {
        CHECK((new BoolVal(true))->equals(new BoolVal(true)) == true);
        CHECK((new BoolVal(false))->equals(new BoolVal(false)) == true);
    }

    SECTION("BoolVal should be FALSE") {
        CHECK((new BoolVal(true))->equals(new BoolVal(false)) == false);
        CHECK((new BoolVal(false))->equals(new BoolVal(true)) == false);
    }

}

TEST_CASE("Test NumVal equals") {

    SECTION("NumVal should be TRUE") {
        CHECK((new NumVal(5))->equals(new NumVal(5)) == true);
        CHECK((new NumVal(-10))->equals(new NumVal(-10)) == true);
    }

    SECTION("NumVal should be FALSE") {
        CHECK((new NumVal(0))->equals(new NumVal(1)) == false);
        CHECK((new NumVal(-505))->equals(new NumVal(505)) == false);
    }

}

/**
* \@brief Test Interp function
* Tests of interp function for each class
*/
TEST_CASE("Interp Function") {
    
    SECTION("NUM Expr Interp") {
        CHECK((new NumExpr(1))->interp()->equals(new NumVal(1)));
        CHECK((new NumExpr(0))->interp()->equals(new NumVal(0)));
        CHECK((new NumExpr(-432))->interp()->equals(new NumVal(-432)));
    }
    
    SECTION("ADD Expr Interp") {
        CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->interp()->equals(new NumVal(3)));
        CHECK((new AddExpr(new NumExpr(-10), new NumExpr(2)))->interp()->equals(new NumVal(-8)));
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(0)))->interp()->equals(new NumVal(0)));
    }
    
    SECTION("MULT Expr Interp") {
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->interp()->equals(new NumVal(2)));
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->interp()->equals(new NumVal(0)));
        CHECK((new MultExpr(new NumExpr(-50), new NumExpr(4)))->interp()->equals(new NumVal(-200)));
    }
    
    SECTION("VARIABLE Expr Interp") {
        CHECK_THROWS_WITH((new VarExpr("R"))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr("codingisfun"))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr(""))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new VarExpr(" "))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new AddExpr(new VarExpr("m"), new NumExpr(21)))->interp(), "VarExpr has no value!");
        CHECK_THROWS_WITH((new MultExpr(new VarExpr("s"), new NumExpr(23)))->interp(), "VarExpr has no value!");
    }

    SECTION("LetExpr Interp") {
//        CHECK_THROWS_WITH((new LetExpr("R", new NumExpr(5), new AddExpr(new VarExpr("R"), new NumExpr(3))))
//                      -> interp(), "VarExpr has no value!");
//        CHECK_THROWS_WITH((new LetExpr("R", new NumExpr(5), new MultExpr(new VarExpr("R"), new NumExpr(3))))
//                      -> interp(), "VarExpr has no value!");
        CHECK((new LetExpr("x", new AddExpr( new NumExpr(5), new NumExpr (2)), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp()->equals(new NumVal(8)));
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
    
    SECTION("ADD Expr subst") {
        CHECK((new AddExpr(new VarExpr("R"), new NumExpr(1)))->subst("R", new VarExpr("P"))->equals(new AddExpr(new VarExpr("P"), new NumExpr(1))) == true);
        CHECK((new AddExpr(new VarExpr("M"), new NumExpr(0)))->subst("M", new VarExpr("S"))->equals(new AddExpr(new VarExpr("S"), new NumExpr(0))) == true);
        CHECK((new AddExpr(new VarExpr("R"), new NumExpr(1)))->subst("R", new VarExpr("P"))->equals(new AddExpr(new VarExpr("R"), new NumExpr(1))) == false);
        CHECK((new AddExpr(new VarExpr("h"), new NumExpr(-8764)))->subst("h", new VarExpr("u"))->equals(new AddExpr(new VarExpr("u"), new NumExpr(1))) == false);
    }
    
    SECTION("MULT Expr subst") {
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
        CHECK( (new VarExpr("x"))
                       ->subst("Y", new AddExpr(new VarExpr("y"), new NumExpr(7)))
                       ->equals(new VarExpr("x")) );
    }

    SECTION("LetExpr subst") {
        Expr *LetTest1 = new LetExpr("R", new NumExpr(5), new AddExpr(new VarExpr("R"), new NumExpr(3)));
        CHECK((LetTest1)->subst("R", new AddExpr(new VarExpr("M"), new NumExpr(3)))->equals(LetTest1));
        Expr *LetTest2 = new LetExpr("R",new VarExpr("R"), new AddExpr(new VarExpr("R"), new NumExpr(2)));
        CHECK((LetTest2->subst("R", new NumExpr(5))
                ->equals(new LetExpr("R",new NumExpr(5),new AddExpr(new VarExpr("R"), new NumExpr(2))))));
    }
}

TEST_CASE("to string function") {

    SECTION("NUM Expr to string") {
        CHECK( (new NumExpr(10))->to_string() == "10" );
        CHECK( (new NumExpr(0))->to_string() == "0" );
        CHECK( (new NumExpr(-10))->to_string() == "-10" );
        CHECK( (new NumExpr(12345))->to_string() == "12345" );
    }

    SECTION("AddExpr to string") {
        CHECK((new AddExpr(new NumExpr(10), new NumExpr(15)))->to_string() == "(10+15)" );
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(0)))->to_string() == "(0+0)" );
        CHECK((new AddExpr(new NumExpr(-10), new NumExpr(15)))->to_string() == "(-10+15)" );
        CHECK((new AddExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->to_string() == "(1+(2+3))");
        CHECK((new AddExpr(new VarExpr("hello"), new VarExpr("world!")))->to_string() == "(hello+world!)");
    }

    SECTION("MultExpr to string") {
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(5)))->to_string() == "(1*5)" );
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->to_string() == "(0*0)" );
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(-5)))->to_string() == "(1*-5)" );
        CHECK((new MultExpr(new NumExpr(-1), new NumExpr(-5)))->to_string() == "(-1*-5)" );
        CHECK((new MultExpr(new VarExpr("hello"), new VarExpr("world!")))->to_string() == "(hello*world!)");

    }

    SECTION("VARIABLE Expr to string") {
        CHECK((new VarExpr("x"))->to_string() == "x" );
        CHECK((new VarExpr("R"))->to_string() == "R" );
        CHECK((new VarExpr("mSd"))->to_string() == "mSd" );
        CHECK((new VarExpr("hello"))->to_string() == "hello" );
    }

    SECTION("LetExpr to string") {
        CHECK((new LetExpr(
                "x",
                new NumExpr(21),
                new AddExpr(
                        new LetExpr(
                                "y",
                                new NumExpr(0),
                                new AddExpr(
                                        new VarExpr("y"),
                                        new NumExpr(33))),
                        new VarExpr("x"))))->to_string() == "(_let x=21 _in ((_let y=0 _in (y+33))+x))");
        CHECK((new LetExpr(
                "x",
                new NumExpr(5),
                new MultExpr(
                        new LetExpr(
                                "y",
                                new NumExpr(3),
                                new MultExpr(
                                        new VarExpr("y"),
                                        new NumExpr(2))),
                        new VarExpr("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y*2))*x))");
    }
}

TEST_CASE("to string PRETTY function") {

    SECTION("NUM Expr to string pretty") {
        CHECK( (new NumExpr(10))->to_string_pretty() == "10" );
        CHECK( (new NumExpr(0))->to_string_pretty() == "0" );
        CHECK( (new NumExpr(-10))->to_string_pretty() == "-10" );
        CHECK( (new NumExpr(12345))->to_string_pretty() == "12345" );
    }

    SECTION("AddExpr to string pretty") {
        CHECK((new AddExpr(new NumExpr(10), new NumExpr(15)))->to_string_pretty() == "10 + 15");
        CHECK((new AddExpr(new NumExpr(0), new NumExpr(0)))->to_string_pretty() == "0 + 0");
        CHECK((new AddExpr(new NumExpr(-10), new NumExpr(15)))->to_string_pretty() == "-10 + 15");
        CHECK((new AddExpr(new VarExpr("hello"), new VarExpr("world!")))->to_string_pretty() == "hello + world!");
        CHECK((new AddExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->to_string_pretty() == "1 + 2 + 3");
        CHECK((new AddExpr(
                new AddExpr(
                        new NumExpr(10),
                        new AddExpr(
                                new AddExpr(
                                        new NumExpr(10),
                                        new NumExpr(10)),
                                new NumExpr(10))),
                new AddExpr(
                        new NumExpr(10),
                        new NumExpr(10))))
                      ->to_string_pretty()  == "(10 + (10 + 10) + 10) + 10 + 10");
    }

    SECTION("MultExpr to string pretty") {
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(5)))->to_string_pretty() == "1 * 5");
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(0)))->to_string_pretty() == "0 * 0");
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(-5)))->to_string_pretty() == "1 * -5");
        CHECK((new MultExpr(new NumExpr(-1), new NumExpr(-5)))->to_string_pretty() == "-1 * -5");
        CHECK((new MultExpr(new VarExpr("hello"), new VarExpr("world!")))->to_string_pretty() == "hello * world!");
        CHECK((new MultExpr(
                new MultExpr(
                    new NumExpr(10),
                    new MultExpr(
                        new MultExpr(
                                new NumExpr(10),
                                new NumExpr(10)),
                        new NumExpr(10))),
                new MultExpr(
                        new NumExpr(10),
                        new NumExpr(10))))
                      ->to_string_pretty()  == "(10 * (10 * 10) * 10) * 10 * 10");
    }

    SECTION("VARIABLE Expr to string pretty") {
        CHECK((new VarExpr("x"))->to_string_pretty() == "x" );
        CHECK((new VarExpr("R"))->to_string_pretty() == "R" );
        CHECK((new VarExpr("mSd"))->to_string_pretty() == "mSd" );
        CHECK((new VarExpr("hello"))->to_string_pretty() == "hello" );
        CHECK((new MultExpr(new MultExpr(new NumExpr(1), new NumExpr(2)), new AddExpr(new NumExpr(3), new NumExpr(4))))->to_string_pretty() == "(1 * 2) * (3 + 4)");
    }

    SECTION("to string pretty for combo Expr including LetExpr") {
        CHECK((new MultExpr(new AddExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(3)))->to_string_pretty() == "(1 + 2) * 3");
        CHECK((new MultExpr(
                new MultExpr(
                        new AddExpr(
                                new NumExpr(9),
                                new NumExpr(9)),
                        new AddExpr(
                                new MultExpr(
                                        new NumExpr(10),
                                        new NumExpr(10)),
                                new NumExpr(10))),
                new MultExpr(
                        new NumExpr(10),
                        new NumExpr(10))))
                      ->to_string_pretty()  == "((9 + 9) * (10 * 10 + 10)) * 10 * 10");
        CHECK((new AddExpr(
                new AddExpr(
                        new AddExpr(
                                new NumExpr(9),
                                new NumExpr(9)),
                        new AddExpr(
                                new MultExpr(
                                        new NumExpr(10),
                                        new NumExpr(10)),
                                new NumExpr(10))),
                new MultExpr(
                        new NumExpr(10),
                        new NumExpr(10))))
                      ->to_string_pretty()  == "((9 + 9) + 10 * 10 + 10) + 10 * 10");
        CHECK((new LetExpr(
                "x",
                new NumExpr(5),
                new AddExpr(
                        new LetExpr(
                                "y",
                                new NumExpr(3),
                                new AddExpr(
                                        new VarExpr("y"),
                                        new NumExpr(2))),
                        new VarExpr("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new MultExpr(
                new MultExpr(
                        new NumExpr (2),
                        new LetExpr(
                                "x",
                                new NumExpr(5),
                                new AddExpr(
                                        new VarExpr("x"),
                                        new NumExpr(1)))),
                new NumExpr(3)))
                ->to_string_pretty() == "(2 * (_let x = 5\n"
                                        "      _in  x + 1)) * 3");
        CHECK((new LetExpr(
                "x",
                new NumExpr(5),
                new AddExpr(
                        new LetExpr(
                                "y",
                                new NumExpr(3),
                                new AddExpr(
                                        new VarExpr("y"),
                                        new NumExpr(2))),
                        new VarExpr("x"))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");
        CHECK((new LetExpr(
                "x",
                new NumExpr(5),
                new AddExpr(
                        new LetExpr(
                                "y",
                                new NumExpr(3),
                                new AddExpr(
                                        new VarExpr("y"),
                                        new NumExpr(2))),
                        new VarExpr("x"))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");


        CHECK((new LetExpr(
                "x",
                new NumExpr(5),
                new AddExpr(
                        new VarExpr("x"),
                        new NumExpr(1))))->to_string_pretty()
                        == "_let x = 5\n"
                           "_in  x + 1");

    }
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(new NumExpr(1)) );
    CHECK( parse_str("(((1)))")->equals(new NumExpr(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(new NumExpr(1)) );
    CHECK( parse_str("10")->equals(new NumExpr(10)) );
    CHECK( parse_str("-3")->equals(new NumExpr(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new NumExpr(5)) );

    CHECK( parse_str("x")->equals(new VarExpr("x")) == true);
    CHECK( parse_str("xyz")->equals(new VarExpr("xyz")) == true);
    CHECK( parse_str("xYz")->equals(new VarExpr("xYz")) == true);

    CHECK( parse_str("x + y")->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))) );
    CHECK( parse_str("x * y")->equals(new MultExpr(new VarExpr("x"), new VarExpr("y"))) );
    CHECK( parse_str("z * x + y")
                   ->equals(new AddExpr(new MultExpr(new VarExpr("z"), new VarExpr("x")),
                                    new VarExpr("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new MultExpr(new VarExpr("z"),
                                     new AddExpr(new VarExpr("x"), new VarExpr("y"))) ));
}

TEST_CASE("Val tests for thrown error") {
    CHECK_THROWS_WITH((new BoolVal(true))->call(0), "cannot call on boolvals");
    CHECK_THROWS_WITH((new NumVal(true))->call(0), "cannot call on numvals");
    CHECK_THROWS_WITH((new NumVal(true))->is_true(), "num val is not a boolean");
    CHECK_THROWS_WITH((new BoolVal(true))->add_to(0), "addition of non number");
    CHECK_THROWS_WITH((new BoolVal(true))->mult_with(0), "mult of non number");
    CHECK_THROWS_WITH((new FunVal("x", new NumExpr(1)))->add_to(0), "addition of non number");
    CHECK_THROWS_WITH((new FunVal("x", new NumExpr(1)))->mult_with(0), "mult of non number");
    CHECK_THROWS_WITH((new FunVal("x", new NumExpr(1)))->is_true(), "Fun Val is not a boolean");
}