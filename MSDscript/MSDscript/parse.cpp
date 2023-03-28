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
        if (!isdigit(in.peek())){
            throw std::runtime_error("invalid input");
        }
    }

    while (1) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            if (n > (INT_MAX - (c - '0')) / 10) {
                throw std::runtime_error("input too large. int overflow!");
            } else {
                n = n*10 + (c - '0');
            }
        } else {
            break;
        }
    }
    if (negative) {
        n = n * -1;
    }
    return new NumExpr(n);
}

Expr *parse_expr(std::istream &in) {
    Expr *e = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '=') {
        consume(in, '=');
        c = in.peek();
        if (c == '=') {
            consume(in, '=');
            Expr *rhs = parse_expr(in);
            return new EqExpr(e, rhs);
        } else {
            throw std::runtime_error("there should be two = signs!");
        }
    } else {
        return e;
    }
}

Expr* parse_addend(std::istream &in) {
    Expr *e = parse_multicand(in);
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

Expr* parse_inner(std::istream &in) {
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
        std::string kw = parse_keyword(in);
        if (kw == "_let") {
            return parse_let(in);
        } else if (kw == "_true") {
            return new BoolExpr(true);
        } else if (kw == "_false") {
            return new BoolExpr(false);
        } else if (kw == "_if") {
            return parse_if(in);
        } else if (kw == "_fun") {
            return parse_function(in);
        } else {
            throw std::runtime_error("error in trying to parse part of multicand using a keyword!!!!!");
        }
    } else {
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
    skip_whitespace(in);
    std::string lhs = parse_var(in)->to_string_pretty();
    skip_whitespace(in);
    int c = in.peek();
    if (c == '='){
        consume(in, '=');
    } else {
        throw std::runtime_error("= expected!");
    }
    skip_whitespace(in);
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    if (parse_keyword(in) != "_in") {
        throw std::runtime_error("_in expected to lead body of let expr");
    }
    Expr* body = parse_expr(in);
    return new LetExpr(lhs, rhs, body);
}

std::string parse_keyword(std::istream &in) {
    std::string keyword = "_";
    int c = in.peek();
    if (c == '_') {
        consume(in, c);
        c = in.peek();
        while(isalpha(c)) {
            keyword += c;
            consume(in, c);
            c = in.peek();
        }
    }
    skip_whitespace(in);
    return keyword;
}

Expr* parse_comparg(std::istream &in) {
    Expr *e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_comparg(in);
        return new AddExpr(e, rhs);
    } else {
        return e;
    }
}

Expr *parse_if(std::istream &in) {
    skip_whitespace(in);
    Expr *ifCondition = parse_expr(in);
    skip_whitespace(in);
    if (parse_keyword(in) != "_then") {
        throw std::runtime_error("_then expected to lead then condition of if expr");
    }
    skip_whitespace(in);
    Expr *thenCondition = parse_expr(in);
    skip_whitespace(in);
    if (parse_keyword(in) != "_else") {
        throw std::runtime_error("_else expected to lead else condition of if expr");
    }
    Expr *elseCondition = parse_expr(in);
    return new IfExpr(ifCondition, thenCondition, elseCondition);
}

Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    Expr *e = parse_inner(in);
    skip_whitespace(in);
    while (in.peek() == '(') {
        consume(in, '(');
        skip_whitespace(in);
        Expr* actual_arg = parse_expr(in);
        skip_whitespace(in);
        consume(in, ')');
        e = new CallExpr(e, actual_arg);
    }
    return e;
}

Expr* parse_function(std::istream &in) {
    skip_whitespace(in);
    std::string formal_arg;
    skip_whitespace(in);

    while (in.peek() == '(') {
        consume(in, '(');
        skip_whitespace(in);
        formal_arg = parse_var(in)->to_string_pretty();
        skip_whitespace(in);
        int c = in.get();
        if (c != ')') {
            throw std::runtime_error("closing parenthesis expected");
        }
    }
    skip_whitespace(in);
    Expr* body = parse_expr(in);
    return new FunExpr(formal_arg, body);
}
