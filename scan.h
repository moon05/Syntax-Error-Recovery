/* definitions the scanner shares with the parser */

enum token{t_if, t_do, t_check, t_read, t_write, t_id, t_literal, t_gets,
                t_eq_eq, T_great_less, t_great, t_less, t_great_eq, t_less_eq,
                t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof};

extern char token_image[100];

extern token scan();
