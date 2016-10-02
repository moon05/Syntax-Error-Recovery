/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
*/

#include <iostream>
#include <vector>

#include <string>
#include "scan.h"

using namespace std;

const string names[] = {"read", "write", "if", "do", "fi", "od" , "check",
                        "id", "literal", "gets","equalequal", "notequal",
                        "lessthan", "greaterthan", "lessORequal", "greaterORequal",
                        "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

//Storing all the First Sets
vector<int> b {1,2};
vector<int> a = {1,2};

vector<token> P = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof};
vector<token> SL {t_id, t_read, t_write, t_if, t_do, t_check};
vector<token> S {t_id, t_read, t_write, t_if, t_do, t_check};
vector<token> R {t_lparen, t_id, t_literal};
vector<token> E {t_lparen, t_id, t_literal};
vector<token> T {t_lparen, t_id, t_literal};
vector<token> F {t_lparen, t_id, t_literal};
vector<token> ET {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq};
vector<token> TT {t_add, t_sub};
vector<token> FT {t_mul, t_div};
vector<token> ro {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq};
vector<token> ao {t_add, t_sub};
vector<token> mo {t_mul, t_div};

//Storing all the epsilons
bool epsP = true;
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
vector<token> P_follow {};
vector<token> SL_follow {t_fi, t_od, t_eof};
vector<token> S_follow {t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> R_follow {t_rparen, t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> E_follow {t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen,
                    t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> T_follow {t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen,
                    t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> F_follow {t_mul, t_div, t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen,
                    t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> ET_follow {t_rparen, t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> TT_follow {t_literal,t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen,
                    t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> FT_follow {t_add, t_sub, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_rparen,
                    t_id, t_read, t_write, t_if, t_do, t_check, t_fi, t_od, t_eof};
vector<token> ro_follow {t_lparen, t_id, t_literal};
vector<token> ao_follow {t_lparen, t_id, t_literal};
vector<token> mo_follow {t_lparen, t_id, t_literal};

static token input_token;

void error () {
    cout << "syntax error\n";
    exit (1);
}

void report_error (token a) {
    cout << "Invalid symbol: "<< names[a] << "\n";
}

void match (token expected) {
    if (input_token == expected) {        
        cout <<"Matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
            cout << ": " << token_image;
        cout <<"\n";
        input_token = scan ();
    }
    else error ();
}

//Finding the Size/Length of any array (Generics)
template <typename T, unsigned S>
inline unsigned arraySize(const T (&v)[S]) {return S;}
//

bool isin ( token given_token, vector<token> l ) {
    int a = l.size();
    for (int i=0; i < a; i++) {
        if (given_token == l[i]) {
            cout << "printing array " << l[i] << ", "<< names[l[i]] << "\n";
            return true;
        }
    }
    cout << given_token << "\n";
    return false;
}

void check_error ( vector<token> first, bool eps, vector<token> follow ) {
    if (!(isin(input_token, first) || eps)) {

        report_error(input_token);
        do {
            input_token = scan();
        }
        while ( !(isin(input_token, first) || isin(input_token, follow) || input_token == t_eof) );
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
    // int j[] = sets_length(P, P_follow);
    cout << P.size() << endl;
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
            cout << "predict stmt --> do stmt_list od\n";
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
    cout << "going into term check\n";
    check_error (T, epsT, T_follow);
    cout << "predict term --> factor factor_tail\n";
    cout << "going into factor\n";
    factor ();
    factor_tail ();
}

void factor () {
    cout << "going into factor check\n";
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
            cout << "going into term\n";
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
            cout << "came to factor_tail";
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
