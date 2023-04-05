//
// Created by Randi Prince on 2/20/23.
//

#ifndef MSDSCRIPT_PARSE_HPP
#define MSDSCRIPT_PARSE_HPP

#include "expr.hpp"
#include <cstdio>
#include "pointer.hpp"

void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);
PTR(Expr) parse_str(std::string string);
PTR(Expr) parse_num(std::istream &in);
PTR(Expr) parse_expr(std::istream &in);
PTR(Expr) parse_addend(std::istream &in);
PTR(Expr) parse_multicand(std::istream &in);
PTR(Expr) parse_var(std::istream &in);
PTR(Expr) parse_let(std::istream &in);
std::string parse_keyword(std::istream &in);
PTR(Expr) parse_comparg(std::istream &in);
PTR(Expr) parse_if(std::istream &in);
PTR(Expr) parse_inner(std::istream &in);
PTR(Expr) parse_function(std::istream &in);


#endif //MSDSCRIPT_PARSE_HPP
