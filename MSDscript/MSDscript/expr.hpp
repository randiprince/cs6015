//
//  expr.hpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

/**
* \file expr.hpp
* \brief contains expression class
declarations for all the sub classes of Expr class
* \author Randi Prince
*/
#ifndef expr_hpp
#define expr_hpp

#include <string>
#include <ostream>
#include <sstream>
#include "pointer.hpp"
#include "env.hpp"

class Val;
/**
* \@brief Expr class
* This is a parent class called Expr.
* It has virtual methods used by sub classes.
*/
CLASS(Expr) {
public:
    typedef enum { //PEMDAS
        prec_none, // Num and VarExpr = 0
        prec_eq,
        prec_let, // = 1
        prec_add,  // add = 2
        prec_mult // mult = 3
    } precedence_t;

    virtual ~Expr() {};

    /**
* \brief determines if one Expr is equal to another Expr
* \param e to compare the value of
* \return boolean
*/
    virtual bool equals(PTR(Expr) e) = 0;

    /**
* \brief returns an int for the value of an expression.
* \return int
*/
    virtual PTR(Val) interp(PTR(Env) env) = 0;


    /**
* \brief Everywhere that the expression (whose subst method is called) contains a variable matching the string,
 * the result PTR(Expr should have the given replacement, instead.
* \param s
* \param e pointer
* \return Expr
*/
//    virtual PTR(Expr) subst(std::string s, PTR(Expr) e) = 0;

    virtual void print(std::ostream& stream) = 0;
    //print in a nicer way
    virtual void pretty_print(std::ostream& stream) = 0;
    // pretty print based on precedence type
    virtual void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos) = 0;
    //call in print
    std::string to_string();
    //call in pretty print
    std::string to_string_pretty();

};

/**
* \@brief NumExpr class
* This is a sub class that implements Expr. It is an expr that is an integer
* It implements all virtual methods of expr.
*/
class NumExpr : public Expr {
public:
    int val;  /**< integer value member variable of NumExpr class */

    NumExpr(int val);
    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

/**
* \@brief AddExpr class
* This is a sub class that implements Expr. It adds two expr together
* It implements all virtual methods of expr.
*/
class AddExpr : public Expr {
public:
    PTR(Expr) lhs; /**< left hand side expr of AddExpr   */
    PTR(Expr) rhs; /**< right hand side expr of AddExpr   */

    AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

/**
* \@brief MultExpr class
* This is a sub class that implements Expr. It multiplies two expr together
* It implements all virtual methods of expr.
*/
class MultExpr : public Expr {
public:
    PTR(Expr) lhs; /**< left hand side expr of MultExpr   */
    PTR(Expr) rhs; /**< right hand side expr of MultExpr   */

    MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

/**
* \@brief VarExpr class
* This is a sub class that implements Expr. It is an expr that is a string.
* It implements all virtual methods of expr.
*/
class VarExpr : public Expr {
public:
    std::string val;/**< String called val, which is a member variable of VarExpr    */

    VarExpr(std::string val);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

/**
* \@brief LetExpr class
* This is a sub class that implements Expr. It is an expr that is a string.
* It implements all virtual methods of expr.
*/
class LetExpr : public Expr {
public:
    std::string lhs;
    PTR(Expr) rhs;
    PTR(Expr) body;

    LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class BoolExpr : public Expr {
public:
    bool val;/**< bool called val, which is a member variable of BoolExpr     */

    BoolExpr(bool val);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class IfExpr : public Expr {
public:
    PTR(Expr) ifCondition;
    PTR(Expr) thenCondition;
    PTR(Expr) elseConditon;

    IfExpr(PTR(Expr) ifCondition, PTR(Expr) thenCondition, PTR(Expr) elseCondition);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class EqExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class FunExpr : public Expr {
public:
    std::string formal_arg;
    PTR(Expr) body;

    FunExpr(std::string formal_arg, PTR(Expr) body);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class CallExpr : public Expr {
public:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;

    CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);

    bool equals(PTR(Expr) expr);
    PTR(Val) interp(PTR(Env) env);
//    PTR(Expr) subst(std::string s, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};
#endif /* expr_hpp */
