/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2011.
*/

#include <iostream>
#include "scan.h"

using namespace std;

char token_image[100];

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }
    if (c == EOF)
        return t_eof;
    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (!strcmp(token_image, "read")) return t_read;
        else if (!strcmp(token_image, "write")) return t_write;
        else if (!strcmp(token_image, "if")) return t_if;
        else if (!strcmp(token_image, "do")) return t_do;
        else if (!strcmp(token_image, "fi")) return t_fi;
        else if (!strcmp(token_image, "od")) return t_od;        
        else if (!strcmp(token_image, "check")) return t_check;
        else if (!strcmp(token_image, "ro")) return t_ro;
        else if (!strcmp(token_image, "ao")) return t_ao;
        else if (!strcmp(token_image, "mo")) return t_mo;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        case ':':
            if (c = getchar() != '=') {
                cerr << "error\n";
                exit(1);
            } else {
                c = getchar();
                return t_gets; // :=
            }
            break;
        case '$':
            if (c = getchar() != '$') {
                cerr << "error\n";
                exit(1);
            } else {
                c = getchar();
                return t_eof; // $$
            }
            break;
        case '=':
            if (c = getchar() != '=') {
                cerr << "error\n";
                exit(1);
            } else {
                c = getchar();
                return t_eq_eq; // ==
            }
            break;
        case '<':
            c = getchar();
            if (c == '>') {
                c = getchar();
                return t_not_eq; // <>
            }
            else if (c == '=' )  {
                c = getchar();
                return t_less_eq; // <=
            }
            else {
                c = getchar();
                return t_less; // <
            }
            break;
        case '>':
            c = getchar();
            if (c == '=') {
                c = getchar();
                return t_great_eq; // >=
            } else {
                c = getchar();
                return t_great; // >
            }
            break;
        
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        default:
            cout << "error\n";
            exit(1);
    }
}
