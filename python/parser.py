import math
import sys

global input_token;
global image = '';

names = ["read", "write", "if", "do", "fi", "od",
			"od", "check", "id", "literal","gets",
			"equalequal", "notequal", "lessthan", "greaterthan",
			"lessORequal", "greaterORequal", "add", "sub",
			"mul", "div", "lparen", "rparen", "eof"]

#defining the tokens
tokens = {"t_read":0, "t_write":1, "t_if":2, "t_do":3, "t_fi":4,
			"t_od":5, "t_check":6, "t_id":7, "t_literal":8, "t_gets":9,
			"t_eq_eq":10, "t_not_eq":11, "t_less":12, "t_great":13,
			"t_less_eq":14, "t_great_eq":15, "t_add":16, "t_sub":17,
			"t_mul":18, "t_div":19, "t_lparen":20, "t_rparen":21,"t_eof":22}

#scan and other helper function
def scanMatcher(str):
	if (str is "read"):
		return tokens["t_read"]
	elif (str is "write"):
		return tokens["t_write"]
	elif (str is )

def scan(str):
	newStr  = str.split()
	print newStr
	return 




#grammar rules

def error():
	print "syntax error"
	sys.exit(0);

def match(expected):
	if (input_token is expected):
		print "Matched %s" % names[input_token]
		if  (input_token is 7 or input_token is 8):
			print ": %s" % image
		print
	else:
		error()


def program():
	if (input_token is (tokens["t_id"] or tokens["t_read"] or tokens["t_write"] or tokens["t_do"] or tokens["t_if"] or tokens["t_check"] or tokens["t_eof"])):
		print "predict program --> stmt_list eof"
		stmt_list()
		match( tokens["t_eof"] )
		break
	return

def stmt_list():
	if (input_token is (tokens["t_id"] or tokens["t_read"] or tokens["t_if"] or tokens["t_do"] or tokens["t_check"] or tokens["t_write"])):
		print "predict stmt_list --> stmt stmt_list"
		stmt()
		stmt_list()
		break
	return;

def stmt():
	if (input_token is tokens["t_id"]):
		print "predict stmt --> id gets expr"
		match( tokens["t_id"] )
		match( tokens["t_gets"] )
		expr()
		break
	elif (input_token is tokens["t_read"]):
		print "predict stmt --> read id"
		match( tokens["t_read"] )
		match( token["t_id"] )
		break
	elif (input_token is tokens["t_write"]):
		print "predict stmt --> write R_expr"
		match( tokens["t_write"] )
		R_expr()
		break
	elif (input_token is tokens["t_if"]):
		print "predict stmt --> if R_expr stmt_list fi"
		match( tokens["t_if"] )
		R_expr()
		stmt_list()
		match( tokens["t_fi"] )
		break
	elif (input_token is tokens["t_do"]):
		print "predict stmt --> do stmt_list od"
		match( tokens["t_do"] )
		stmt_list()
		match( tokens["t_od"] )
		break
	elif (input_token is tokens["t_check"]):
		print "predict stmt --> check R_expr"
		match( tokens["t_check"] )
		R_expr()
		break
	return

def R_expr():
	print "predict R_expr --> expr expr_tail"
	expr()
	expr_tail()

def expr():
	print "predict expr --> term term_tail"
	term()
	term_tail()

def term():
	print "predict term --> factor factor_tail"
	factor()
	factor_tail()

def factor():
	if (input_token is tokens["t_lparen"]):
		print "predict factor --> lparen R_expr rparen"
		match( tokens["t_lparen"] )
		R_expr()
		match( tokens["t_rparen"] )
		break
	elif (input_token is tokens["t_id"]):
		print "predict factor --> id"
		match( token["t_id"] )
		break
	elif (input_token is tokens["t_literal"]):
		print "predict factor --> literal"
		match( token["t_literal"] )
		break
	return

def expr_tail():
	if (input_token is (tokens["t_eq_eq"] or tokens["t_not_eq"] or tokens["t_less"] or tokens["t_great"] or tokens["t_less_eq"] or tokens["t_great_eq"])):
		print "print expr_tail --> relational_op expr"
		r_op()
		expr()
		break
	return

def factor_tail():
	if ( input_token is ( tokens["t_mul"] or tokens["t_div"]) ):
		print "predict factor_tail --> mul_op factor factor_tail"
		mul_op()
		factor()
		factor_tail()
		break
	return

def r_op():
	if ( input_token is tokens["t_eq_eq"] ):
		print "predict r_op --> equalequal"
		match( tokens["t_eq_eq"] )
		break
	elif ( input_token is tokens["t_not_eq"] ):
		print "predict r_op --> notequal"
		match( tokens["t_not_eq"] )
		break
	elif ( input_token is tokens["t_less"] ):
		print "predict r_op --> lessthan"
		match( tokens["t_less"] )
		break
	elif ( input_token is tokens["t_great"] ):
		print "predict r_op --> greaterthan"
		match( tokens["t_great"] )
		break
	elif ( input_token is tokens["t_less_eq"] ):
		print "predict r_op --> lessORequal"
		match( tokens["t_less_eq"] )
		break
	elif ( input_token is tokens["t_great_eq"] ):
		print "predict r_op --> greaterORequal"
		match( tokens["t_great_eq"] )
		break
	return

def add_op():
	if ( input_token is tokens["t_add"] ):
		print "predict add_op --> add"
		match( tokens["t_add"] )
		break
	elif ( input_token is tokens["t_sub"] ):
		print "predict add_op --> sub"
		match( tokens["t_sub"] )
		break
	return

def mul_op():
	if ( input_token is tokens["t_mul"] ):
		print "predict mul_op --> mul"
		match( tokens["t_mul"] )
		break
	elif ( input_token is tokens["t_div"] ):
		print "predict mul_op --> div"
		match( tokens["t_div"] )
		break
	return


def main():
	input_token = scan()
	program()
	return


if __name__ =="__main__":
	main()






