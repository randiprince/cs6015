//
// Created by Randi Prince on 2/20/23.
//

#include "parse.hpp"

void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c != expect) {
        throw std::runtime_error("consume mismatch");
    }
}

void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek();
        if (!isspace(c)) {
            break;
        }
        consume(in, c);
    }
}

Expr* parse_str(std::string string) {
    std::istringstream in(string);
    return parse_expr(in);
}

Expr* parse_num(std::istream &in) {
    int n = 0;
    bool negative = false;
    if (in.peek() == '-') {
        negative = true;
        consume(in, '-');
    }

    while (1) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            n = n*10 + (c - '0');
        } else {
            break;
        }
    }
    if (negative) {
        n = -n;
    }
    return new NumExpr(n);
}

Expr* parse_expr(std::istream &in) {
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new AddExpr(e, rhs);
    } else {
        return e;
    }
}

Expr* parse_addend(std::istream &in) {
    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new MultExpr(e, rhs);
    } else {
        return e;
    }
}

Expr* parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c)) {
        return parse_num(in);
    } else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
    } else if (isalpha(c)) {
        return parse_var(in);
    }
    else if (c == '_') {
        return parse_let(in);
    }
    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}

Expr* parse_var(std::istream &in) {
    std::string string = "";
    while (1) {
        int c = in.peek();
        if (isalpha(c)) {
            consume(in, c);
            string += c;
        } else {
            break;
        }
    }
    return new VarExpr(string);
}

Expr* parse_let(std::istream &in) {
//    std::string letString = "_let";
//    std::string inString = "_in";
//    std::string testString = "";
    skip_whitespace(in);
    int c = in.peek();
    if (c == '_') {
        consume(in, c);
        parse_keyword(in, "let");
    }
    skip_whitespace(in);
    Expr* lhs = parse_var(in);

    skip_whitespace(in);
    c = in.peek();
    if (c == '='){
        consume(in, '=');
    }
    skip_whitespace(in);
    Expr* rhs = parse_expr(in);

    skip_whitespace(in);
    c = in.peek();
    if (c == '_') {
        consume(in, '_');
        parse_keyword(in, "in");
    }
    Expr* body = parse_expr(in);
    return new LetExpr(lhs->to_string_pretty(), rhs, body);
}

void parse_keyword(std::istream &in, std::string keyword) {
    for (int i = 0; i < keyword.size(); i++) {
        in.get();
    }
}

