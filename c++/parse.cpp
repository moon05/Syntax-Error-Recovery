/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
*/

#include <iostream>
#include <vector>
#include <regex>

#include "scan.h"

using namespace std;

const string names[] = {"read", "write", "if", "do", "fi", "od" , "check",
                        "id", "literal", "gets","equalequal", "notequal",
                        "lessthan", "greaterthan", "lessORequal", "greaterORequal",
                        "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

string syntax_tree = "";

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
    throw invalid_argument("Syntax Error");
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
        syntax_tree += names[expected] + " ";
        input_token = scan ();
    }
    else error ();
}



bool isin (token given_token, vector<token> l) {
    int a = l.size();
    for (int i=0; i < a; i++) {
        if (given_token == l[i]) {
            cout << "printing vector ( " << l[i] << ", "<< names[l[i]] << " )\n";
            return true;
        }
    }
    for (int j=0; j<a; j++){
        cout<< names[l[j]] << ", "; 
    }
    cout<<"\n";
    cout << "This token wasn't in the vector: "<<given_token << "\n";
    return false;
}

bool check_error (vector<token> first, bool eps, vector<token> follow) {
    if (!(isin(input_token, first) || eps)) {
        cout << eps <<endl;
        report_error(input_token);
        do {
            cout << "got into do while";
            input_token = scan();
        }
        while ( !(isin(input_token, first) || isin(input_token, follow)) );
        if (isin(input_token, first)){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}


void recover_from_error (vector<token> follow) {
    do {
        input_token = scan();
    } while (!(isin(input_token,follow)));
}

void print_error_info(string e, string a){
    cout << "Expected: "<< e << endl;
    cout << "Actual: " << a << endl;

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
    if (check_error (P, epsP, P_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_do:
        case t_if:
        case t_check:
        case t_eof:
            cout << "predict program --> stmt_list eof\n";
            cout << "Going into stmt_list" <<endl;
            stmt_list ();
            match (t_eof); // takes care of $$
            break;
        default: return;
    }
    syntax_tree += ")";
}

void stmt_list () {
    cout << "screwed in stmt_list";
    if (check_error (SL, epsSL, SL_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_id:
        case t_read:
        case t_if:
        case t_do:
        case t_check:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list\n";
            cout << "Going into stmt" <<endl;
            stmt ();
            cout << "Going into stmt_list" <<endl;
            stmt_list ();
            break;
        default: return;

        // epsilon
    }
    syntax_tree += ")";
}

void stmt () {
    cout << "screwed in stmt";
    if (check_error (S, epsS, S_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_id:
            cout << "predict stmt --> id gets expr\n";
            try{
                match (t_id);
                match (t_gets);
            }catch(exception& ex) {
                recover_from_error(S_follow);
                cout << ex.what() << endl;
            }
            cout << "Going into expr" <<endl;
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
            cout << "Going into r_expr" <<endl;
            R_Expr ();
            break;
        case t_if:
            cout << "predict stmt --> if R_Expr stmt_list fi\n";
            match (t_if);
            cout << "Going into r_expr" <<endl;
            R_Expr ();
            cout << "Going into stmt_list" <<endl;
            stmt_list ();
            match (t_fi);
            break;
        case t_do:
            cout << "predict stmt --> do stmt_list od\n";
            match (t_do);
            cout << "Going into stmt_list" <<endl;
            stmt_list ();
            match (t_od);
            break;
        case t_check:
            cout << "predict stmt --> check R_Expr\n";
            match (t_check);
            cout << "Going into r_expr" <<endl;
            R_Expr ();
            break;
        default: return;

    }
    syntax_tree += ")";
}

void R_Expr () {
    if(check_error (R, epsR, R_follow)){
        return;
    }
    syntax_tree += "(";
    cout << "predict R_Expr --> expr expr_tail\n";
    cout << "Going into expr in R_Expr" <<endl;
    expr ();
    cout << "Going into expr_tail in R_Expr" <<endl;
    expr_tail ();
    syntax_tree += ")";
}

void expr () {
    if (check_error (E, epsE, E_follow)){
        return;
    }
    syntax_tree += "(";
    cout << "predict expr --> term term_tail\n";
    cout << "Going into term in expr" <<endl;
    term ();
    cout << "Going into term_tail in expr" <<endl;
    term_tail ();
    syntax_tree += ")";
}

void term () {
    if (check_error (T, epsT, T_follow)){
        return;
    }
    syntax_tree += "(";
    cout << "predict term --> factor factor_tail\n";
    cout << "Going into factor in term" <<endl;
    factor ();
    cout << "Going into factor_tail in term" <<endl;
    factor_tail ();
    syntax_tree += ")";
}

void factor () {
    cout << "going into factor check\n";
    if (check_error (F, epsF, F_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_lparen:
            cout << "predict factor --> lparen R_Expr rparen\n";
            match (t_lparen);
            cout << "Going into r_expr in factor" <<endl;
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
    syntax_tree += ")";
}

void expr_tail () {
    if (check_error (ET, epsET, ET_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_eq_eq:
        case t_not_eq:
        case t_less:
        case t_great:
        case t_less_eq:
        case t_great_eq:
            cout << "predict expr_tail --> relational_op expr\n";
            r_op ();
            cout << "Going into expr in expr_tail" <<endl;
            expr ();
            break;
        default: return;
        // epsilon

    }
    syntax_tree += ")";
}

void term_tail () {
    if (check_error (TT, epsTT, TT_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail\n";
            add_op ();
            cout << "Going into term in term_tail" <<endl;
            term ();
            cout << "Going into term_tail in term_tail" <<endl;
            term_tail ();
            break;
        default: return;
        // epsilon
    }
    syntax_tree += ")";
}

void factor_tail () {
    if (check_error (FT, epsFT, FT_follow)){
        return;
    }
    syntax_tree += "(";
    switch (input_token) {
        case t_mul:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail\n";
            mul_op ();
            cout << "Going into factor in factor_tail" <<endl;
            factor ();
            cout << "Going into factor_tail in factor_tail" <<endl;
            factor_tail ();
            break;
        default: return;
        // epsilon
    }
    syntax_tree += ")";
}

void r_op () {
    if (check_error (ro, eps_ro, ro_follow)){
        return;
    }
    syntax_tree += "(";
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
    syntax_tree += ")";
}

void add_op () {
    if (check_error (ao, eps_ao, ao_follow)){
        return;
    }
    syntax_tree += "(";
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
    syntax_tree += ")";
}

void mul_op () {
    if (check_error (mo, eps_mo, mo_follow)){
        return;
    }
    syntax_tree += "(";
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
    syntax_tree += ")";
}

int main () {
    input_token = scan ();
    program ();
    cout << "Printing Syntax Tree" << endl;
    cout << syntax_tree << endl;
    
    regex pattern("\\(\\)");

    syntax_tree = regex_replace(syntax_tree, pattern, "");
    cout << "Cleaned up tree" << endl;
    cout << syntax_tree << endl;
}
