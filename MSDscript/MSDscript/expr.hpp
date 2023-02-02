//
//  expr.hpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#ifndef expr_hpp
#define expr_hpp

//#include <stdio.h>
#include <string>

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string s, Expr *e) = 0;
};

class Num : public Expr {
public:
    int val;
    
    Num(int val);
    bool equals(Expr *expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
};

class Add : public Expr { // add expr to name
public:
    Expr *lhs;
    Expr *rhs;
    
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
};

class Variable : public Expr {
public:
    std::string val;
    
    Variable(std::string val);
    bool equals(Expr *expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr *e);
};

#endif /* expr_hpp */
