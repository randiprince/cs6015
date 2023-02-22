//
// Created by Randi Prince on 2/20/23.
//

#ifndef MSDSCRIPT_PARSE_HPP
#define MSDSCRIPT_PARSE_HPP

#include "expr.hpp"
#include <cstdio>

void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);
Expr* parse_str(std::string string);
Expr *parse_num(std::istream &in);
Expr *parse_expr(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);
Expr *parse_var(std::istream &in);
Expr *parse_let(std::istream &in);
void parse_keyword(std::istream &in, std::string keyword);


#endif //MSDSCRIPT_PARSE_HPP
