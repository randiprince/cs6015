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
class Val;
/**
* \@brief Expr class
* This is a parent class called Expr.
* It has virtual methods used by sub classes.
*/
class Expr {
public:
    typedef enum { //PEMDAS
        prec_none, // Num and VarExpr = 0
        prec_eq,
        prec_let, // = 1
        prec_add,  // add = 2
        prec_mult // mult = 3
    } precedence_t;

    /**
* \brief determines if one Expr is equal to another Expr
* \param e to compare the value of
* \return boolean
*/
    virtual bool equals(Expr *e) = 0;

    /**
* \brief returns an int for the value of an expression.
* \return int
*/
    virtual Val* interp() = 0;
    /**
* \brief function to determine if the expr has a varExpr
* \return boolean
*/
    virtual bool has_variable() = 0;

    /**
* \brief Everywhere that the expression (whose subst method is called) contains a variable matching the string,
 * the result Expr* should have the given replacement, instead.
* \param s
* \param e pointer
* \return Expr
*/
    virtual Expr* subst(std::string s, Expr *e) = 0;

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
    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
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
    Expr *lhs; /**< left hand side expr of AddExpr*/
    Expr *rhs; /**< right hand side expr of AddExpr*/

    AddExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
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
    Expr *lhs; /**< left hand side expr of MultExpr*/
    Expr *rhs; /**< right hand side expr of MultExpr*/

    MultExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
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
    std::string val;/**< String called val, which is a member variable of VarExpr*/

    VarExpr(std::string val);

    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
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
    Expr* rhs;
    Expr* body;

    LetExpr(std::string lhs, Expr *rhs, Expr *body);

    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class BoolExpr : public Expr {
public:
    bool val;/**< bool called val, which is a member variable of BoolExpr*/

    BoolExpr(bool val);

    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class IfExpr : public Expr {
public:
    Expr* ifCondition;
    Expr* thenCondition;
    Expr* elseConditon;

    IfExpr(Expr *ifCondition, Expr *thenCondition, Expr *elseCondition);

    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};

class EqExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    EqExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr *expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
    void print(std::ostream& stream);
    void pretty_print(std::ostream& stream);
    void pretty_print_at(std::ostream& stream, precedence_t ptype, long *pos);
};
#endif /* expr_hpp */
