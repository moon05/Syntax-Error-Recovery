import math
import sys

tokens = {"t_read":0, "t_write":1, "t_if":2, "t_do":3, "t_fi":4,
			"t_od":5, "t_check":6, "t_id":7, "t_literal":8, "t_gets":9,
			"t_eq_eq":10, "t_not_eq":11, "t_less":12, "t_great":13,
			"t_less_eq":14, "t_great_eq":15, "t_add":16, "t_sub":17,
			"t_mul":18, "t_div":19, "t_lparen":20, "t_rparen":21,"t_eof":22}