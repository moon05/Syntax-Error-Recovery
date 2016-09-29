/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
*/

#include <iostream>
#include "scan.h"

using namespace std;

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;

void error () {
    cout << "syntax error\n";
    exit (1);
}

void match (token expected) {
    if (input_token == expected) {
        cout <<"matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
            cout << ": " << token_image;
        cout <<"\n";
        input_token = scan ();
    }
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void R_Expr ();
void expr ();
void expr_tail ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void add_op ();
void mul_op ();

void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict program --> stmt_list eof\n";
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list\n";
            stmt ();
            stmt_list ();
            break;
        case t_eof:
            cout << "predict stmt_list --> epsilon\n";
            break;          /*  epsilon production */
        default: error ();
    }
}

void stmt () {
    switch (input_token) {
        case t_id:
            cout << "predict stmt --> id gets expr\n";
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
            cout << "predict stmt --> read id\n";
            match (t_read);
            match (t_id);
            break;
        case t_write:
            cout << "predict stmt --> write R_Expr\n";
            match (t_write);
            R_Expr ();
            break;
        case t_if:
            cout << "predict stmt --> if R_Expr stmt_list fi\n";
            match (t_if);
            R_Expr ();
            stmt_list ();
            match (t_fi)
            break;
        case t_do:
            cout << "prdict stmt --> do stmt_list od\n";
            match (t_do);
            stmt_list ();
            match (t_od)
            break;
        case t_check:
            cout << "predict stmt --> check R_Expr\n";
            match (t_check);
            R_Expr ();
            break;
        default: error ();
    }
}
/*Start-----------------------------------------------------------------*/
void R_Expr () { 
    cout << "predict R_Expr --> expr expr_tail\n";
    expr ();
    expr_tail ();
}

void expr () { 
    cout << "predict expr --> term term_tail\n";
    term ();
    term_tail ();
}

void term () {
    cout << "predict term --> factor factor_tail\n";
    factor ();
    factor_tail ();
}

void factor () {
    switch (input_token) {
        case t_lparen:
            cout << "predict factor --> left_paren R_Expr right_paren\n";
            match (t_lparen);
            R_Expr ();
            match (t_rparen);
            break;
        case t_id:
            cout << "predict factor --> id\n";
            match (t_id);
            break;
        case t_literal:
            cout << "predict factor --> literal\n";
            match (t_literal);
            break;
        default: error();
    }
}

void expr_tail () {
    switch (input_token) {
        case t_ro:
            cout << "predict expr_tail --> r_op expr"
            
        case t_eof:
            cout << "predict factor_tail --> epsilon\n";
        default: error();
    }
}

void term_tail () {
    switch (input_token) {
        case t_eof:
            cout << "predict factor_tail --> epsilon\n";
        default: error();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_eof:
            cout << "predict factor_tail --> epsilon\n";
        default: error();
    }

}

/*End-----------------------------------------------------------------*/

void r_op () {
    switch (input_token) {
        case t_eq_eq:
            cout << "predict r_op --> equal equal\n";
            match (t_eq_eq);
            break;
        case t_not_eq:
            cout << "predict r_op --> not equal\n";
            match (t_not_eq);
            break;
        case t_less:
            cout << "predict r_op --> less than\n";
            match (t_less);
            break;
        case t_great:
            cout << "predict r_op --> greater than\n";
            match (t_great);
            break;
        case t_less_eq:
            cout << "predict r_op --> less than or equal\n";
            match (t_less_eq);
            break;
        case t_great_eq:
            cout << "predict r_op --> greater than or equal\n";
            match (t_great_eq);
            break;
        default: error ();
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            cout << "predict add_op --> add\n";
            match (t_add);
            break;
        case t_sub:
            cout << "predict add_op --> sub\n";
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            cout << "predict mul_op --> mul\n";
            match (t_mul);
            break;
        case t_div:
            cout << "predict mul_op --> div\n";
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
    input_token = scan ();
    program ();
}
