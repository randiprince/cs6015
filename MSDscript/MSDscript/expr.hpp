//
//  expr.hpp
//  MSDscript
//
//  Created by Randi Prince on 1/23/23.
//

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *expr);
};

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *expr);
};

#endif /* expr_hpp */
