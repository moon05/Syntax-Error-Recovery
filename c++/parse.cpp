/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
*/

#include <iostream>
#include <string>
#include "scan.h"

using namespace std;

const string names[] = {"read", "write", "if", "do", "fi", "od" , "check",
                        "id", "literal", "gets","equalequal", "notequal",
                        "lessthan", "greaterthan", "lessORequal", "greaterORequal",
                        "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

//Storing all the First Sets
token P[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof};
token SL[] = {t_id, t_read, t_write, t_if, t_do, t_check};
token S[] = {t_id, t_read, t_write, t_if, t_do, t_check};
token R[] = {t_lparen, t_id, t_literal};
token E[] = {t_lparen, t_id, t_literal};
token T[] = {t_lparen, t_id, t_literal};
token F[] = {t_lparen, t_id, t_literal};
token ET[] = {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq};
token TT[] = {t_add, t_sub};
token FT[] = {t_mul, t_div};
token ro[] = {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq};
token ao[] = {t_add, t_sub};
token mo[] = {t_mul, t_div};

//Storing all the epsilons
bool epsP = false;
bool epsSL = true;
bool epsS = false;
bool epsR = false;
bool epsE = false;
bool epsT = false;
bool epsF = false;
bool epsET = true;
bool epsTT = true;
bool epsFT = true;
bool eps_ro = false;
bool eps_ao = false;
bool eps_mo = false;


//Storing all the Follow Sets
token P_follow[] = {};
token SL_follow[] = {t_eof, t_fi, t_od};
token S_follow[] = {t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token R_follow[] = {t_rparen, t_fi, t_id, t_read, t_write, t_if, t_do, t_check, t_od, t_eof};
token E_follow[] = {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen, t_fi,
                    t_od, t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token T_follow[] = {t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen, t_fi,
                    t_od, t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token F_follow[] = {t_mul, t_div, t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq,
                    t_rparen, t_fi, t_od, t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token ET_follow[] = {t_rparen, t_fi, t_id, t_read, t_write, t_if, t_do, t_check, t_od, t_eof};
token TT_follow[] = {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen, t_fi,
                    t_od, t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token FT_follow[] = {t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen, t_fi,
                    t_od, t_eof, t_id, t_read, t_write, t_if, t_do, t_check};
token ro_follow[] = {t_lparen, t_id, t_literal};
token ao_follow[] = {t_lparen, t_id, t_literal};
token mo_follow[] = {t_lparen, t_id, t_literal};

static token input_token;

void error () {
    cout << "syntax error\n";
    exit (1);
}

void report_error (token a) {
    cout << "Invalid symbol"<< a << "\n";
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



bool iter ( token given_token, token l[] ) {
    for (int i=0; i < sizeof(l)/sizeof(given_token); i++) {
        if (given_token == l[i]) {
            cout << "printing array " << l[i] << names[l[i]] << "\n";
            return true;
        }
        cout << "printing array " << l[i] << names[l[i]];


    }
    cout << given_token << "\n";
    return false;
}

void check_error ( token first[], bool eps, token follow[] ) {
    token epsilon[] = {t_eof};
    if (!(iter(input_token, first) || eps)) {

        report_error(input_token);
        do {
            input_token = scan();
        }
        while ( !(iter(input_token, first) || iter(input_token, follow) || iter(input_token, epsilon)) );
    }
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
void r_op();
void add_op ();
void mul_op ();

void program () {
    check_error (P, epsP, P_follow);
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_do:
        case t_if:
        case t_check:
        case t_eof:
            cout << "predict program --> stmt_list eof\n";
            stmt_list ();
            match (t_eof); // takes care of $$
            break;
        default: return;
    }
}

void stmt_list () {
    check_error (SL, epsS, SL_follow);
    switch (input_token) {
        case t_id:
        case t_read:
        case t_if:
        case t_do:
        case t_check:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list\n";
            stmt ();
            stmt_list ();
            break;
        default: return;

        // epsilon
    }
}

void stmt () {
    check_error (S, epsS, S_follow);
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
            match (t_fi);
            break;
        case t_do:
            cout << "prdict stmt --> do stmt_list od\n";
            match (t_do);
            stmt_list ();
            match (t_od);
            break;
        case t_check:
            cout << "predict stmt --> check R_Expr\n";
            match (t_check);
            R_Expr ();
            break;
        default: return;
    }
}

void R_Expr () {
    check_error (R, epsR, R_follow);
    cout << "predict R_Expr --> expr expr_tail\n";
    expr ();
    expr_tail ();
}

void expr () {
    check_error (E, epsE, E_follow);
    cout << "predict expr --> term term_tail\n";
    term ();
    term_tail ();
}

void term () {
    check_error (T, epsT, T_follow);
    cout << "predict term --> factor factor_tail\n";
    factor ();
    factor_tail ();
}

void factor () {
    check_error (F, epsF, F_follow);
    switch (input_token) {
        case t_lparen:
            cout << "predict factor --> lparen R_Expr rparen\n";
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
        default: return;
    }
}

void expr_tail () {
    check_error (ET, epsET, ET_follow);
    switch (input_token) {
        case t_eq_eq:
        case t_not_eq:
        case t_less:
        case t_great:
        case t_less_eq:
        case t_great_eq:
            cout << "predict expr_tail --> relational_op expr\n";
            r_op ();
            expr ();
            break;
        default: return;
        // epsilon

    }
}

void term_tail () {
    check_error (TT, epsTT, TT_follow);
    switch (input_token) {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail\n";
            add_op ();
            cout << "came to term";
            term ();
            term_tail ();
            break;
        default: return;
        // epsilon

    }
}

void factor_tail () {
    check_error (FT, epsFT, FT_follow);
    switch (input_token) {
        case t_mul:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail\n";
            mul_op ();
            cout << "came here";
            factor ();
            factor_tail ();
            break;
        default: return;
        // epsilon

    }
}

void r_op () {
    check_error (ro, eps_ro, ro_follow);
    switch (input_token) {
        case t_eq_eq:
            cout << "predict r_op --> equalequal\n";
            match (t_eq_eq);
            break;
        case t_not_eq:
            cout << "predict r_op --> notequal\n";
            match (t_not_eq);
            break;
        case t_less:
            cout << "predict r_op --> lessthan\n";
            match (t_less);
            break;
        case t_great:
            cout << "predict r_op --> greaterthan\n";
            match (t_great);
            break;
        case t_less_eq:
            cout << "predict r_op --> lessORequal\n";
            match (t_less_eq);
            break;
        case t_great_eq:
            cout << "predict r_op --> greaterORequal\n";
            match (t_great_eq);
            break;
        default: return;
    }
}

void add_op () {
    check_error (ao, eps_ao, ao_follow);
    switch (input_token) {
        case t_add:
            cout << "predict add_op --> add\n";
            match (t_add);
            break;
        case t_sub:
            cout << "predict add_op --> sub\n";
            match (t_sub);
            break;
        default: return;
    }
}

void mul_op () {
    check_error (mo, eps_mo, mo_follow);
    switch (input_token) {
        case t_mul:
            cout << "predict mul_op --> mul\n";
            match (t_mul);
            break;
        case t_div:
            cout << "predict mul_op --> div\n";
            match (t_div);
            break;
        default: return;
    }
}

int main () {
    input_token = scan ();
    program ();
}
