/* definitions the scanner shares with the parser */

enum token { t_read, t_write, t_if, t_do, t_fi, t_od, t_check,
			t_id, t_literal, t_gets, t_eq_eq, t_not_eq,
			t_less, t_great, t_less_eq, t_great_eq, t_add,
			t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof};

extern char token_image[100];

extern token scan();

typedef void (*NR) ();