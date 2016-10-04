import math
import sys

global input_token;
global image;
global syntax_tree;

image = ''
syntax_tree = ''

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

#first sets
P = ["t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_eof"]
SL = ["t_id", "t_read", "t_write", "t_if", "t_do", "t_check"]
S = ["t_id", "t_read", "t_write", "t_if", "t_do", "t_check"]
R = ["t_lparen", "t_id", "t_literal"]
E = ["t_lparen", "t_id", "t_literal"]
T = ["t_lparen", "t_id", "t_literal"]
F = ["t_lparen", "t_id", "t_literal"]
ET = ["t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq"]
TT = ["t_add", "t_sub"]
FT = ["t_mul", "t_div"]
ro = ["t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq"]
ao = ["t_add", "t_sub"]
mo = ["t_mul", "t_div"]

#epsilons
epsP = False;
epsSL = True;
epsS = False;
epsR = False;
epsE = False;
epsT = False;
epsF = False;
epsET = True;
epsTT = True;
epsFT = True;
eps_ro = False;
eps_ao = False;
eps_mo = False;

#follow sets
P_follow = []
SL_follow = ["t_fi", "t_od", "t_eof"]
S_follow = ["t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
R_follow = ["t_rparen", "t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
E_follow = ["t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq", "t_rparen","t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
T_follow = ["t_add", "t_sub", "t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq", "t_rparen","t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
F_follow = ["t_mul", "t_div", "t_add", "t_sub", "t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq", "t_rparen","t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
ET_follow = ["t_rparen", "t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
TT_follow = ["t_literal", "t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq", "t_rparen", "t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
FT_follow = ["t_add", "t_sub", "t_eq_eq", "t_not_eq", "t_less", "t_great", "t_less_eq", "t_great_eq", "t_rparen",
                    "t_id", "t_read", "t_write", "t_if", "t_do", "t_check", "t_fi", "t_od", "t_eof"]
ro_follow = ["t_lparen", "t_id", "t_literal"]
ao_follow = ["t_lparen", "t_id", "t_literal"]
mo_follow = ["t_lparen", "t_id", "t_literal"]

#error reporting
def error():
	print "syntax error"
	sys.exit(0);

def report_error(tok):
	print "Invalid symbol: %s" %  names[tokens[tok]]

#scan and other helper function
def scanMatcher(str):
	if (str is "read"):
		return tokens["t_read"]
	elif (str is "write"):
		return tokens["t_write"]
	elif (str is "$$"):
		return tokens["t_eof"]
	elif (str is "if"):
		return tokens["t_if"]
	elif (str is "fi"):
		return tokens["t_fi"]
	elif (str is "do"):
		return tokens["t_do"]
	elif (str is "od"):
		return tokens["t_od"]
	elif (str is "check"):
		return tokens["t_check"]
	elif (str is ":="):
		return tokens["t_gets"]
	elif (str is "=="):
		return tokens["t_eq_eq"]
	elif (str is "<>"):
		return tokens["t_not_eq"]
	elif (str is "<"):
		return tokens["t_less"]
	elif (str is ">"):
		return tokens["t_great"]
	elif (str is "<="):
		return tokens["t_less_eq"]
	elif (str is ">="):
		return tokens["t_great_eq"]
	elif (str is "+"):
		return tokens["t_add"]
	elif (str is "-"):
		return tokens["t_sub"]
	elif (str is "/"):
		return tokens["t_div"]
	elif (str is "*"):
		return tokens["t_mul"]
	elif (str is "("):
		return tokens["t_lparen"]
	elif (str is ")"):
		return tokens["t_rparen"]
	else:
		print "Invalid Character"
		return sys.exit(0)

def scan(str):
	newStr  = str.split()
	print newStr
	return





def match(expected):
	if (input_token is expected):
		print "Matched %s" % names[input_token]
		if  (input_token is 7 or input_token is 8):
			print ": %s" % image
		print
		syntax_tree += (names[expected] + " ")
	else:
		error()


#error-recovery functions

##takes in token(int) and token-list
def isin(token, listy):
	a = len(listy)
	for i in listy:
		if ( token is tokens[listy[i]] ):
			return True;
	return False;

##takes in first-set, eps, follow-set
def check_error(first, eps, follow):
	if ( (not isin(input_token, first)) and eps):
		return True
	
	if ( isin(input_token, first) ):
		return False

	report_error(input_token)
	while ( (not isin(input_token, first) or isin(input_token, follow)) ):
		input_token = scan()
	if ( isin(input_token, first) ):
		return False
	else:
		return True


#grammar rules

def program():
	if (check_error (P, epsP, P_follow)):
		program()
	syntax_tree += "("
	if (input_token is (tokens["t_id"] or tokens["t_read"] or tokens["t_write"] or tokens["t_do"] or tokens["t_if"] or tokens["t_check"] or tokens["t_eof"])):
		print "predict program --> stmt_list eof"
		stmt_list()
		try:
			match( tokens["t_eof"] )
		except:
			if ( check_error( ["eof"], False, P_follow) ):
				return
	else:
		return

	syntax_tree += ")"

def stmt_list():
	if ( check_error (SL, epsSL, SL_follow) ):
		return
	syntax_tree += "("

	if (input_token is (tokens["t_id"] or tokens["t_read"] or tokens["t_if"] or tokens["t_do"] or tokens["t_check"] or tokens["t_write"])):
		print "predict stmt_list --> stmt stmt_list"
		stmt()
		stmt_list()
	
	else:
		return

	syntax_tree += ")"

def stmt():
	if ( check_error (S, epsS, S_follow) ):
		return
	syntax_tree += "("

	if (input_token is tokens["t_id"]):
		print "predict stmt --> id gets expr"
		match( tokens["t_id"] )
		match( tokens["t_gets"] )
		expr()
	elif (input_token is tokens["t_read"]):
		print "predict stmt --> read id"
		match( tokens["t_read"] )
		match( tokens["t_id"] )
		
	elif (input_token is tokens["t_write"]):
		print "predict stmt --> write R_expr"
		match( tokens["t_write"] )
		R_expr()
		
	elif (input_token is tokens["t_if"]):
		print "predict stmt --> if R_expr stmt_list fi"
		match( tokens["t_if"] )
		R_expr()
		stmt_list()
		match( tokens["t_fi"] )
		
	elif (input_token is tokens["t_do"]):
		print "predict stmt --> do stmt_list od"
		match( tokens["t_do"] )
		stmt_list()
		match( tokens["t_od"] )

	elif (input_token is tokens["t_check"]):
		print "predict stmt --> check R_expr"
		match( tokens["t_check"] )
		R_expr()
		
	return

def R_expr():
	if ( check_error (R, epsR, R_follow) ):
		return
	syntax_tree += "("
	print "predict R_expr --> expr expr_tail"
	expr()
	expr_tail()
	syntax_tree += ")"

def expr():
	if ( check_error (E, epsE, E_follow) ):
		return
	syntax_tree += "("
	print "predict expr --> term term_tail"
	term()
	term_tail()
	syntax_tree += ")"

def term():
	if ( check_error (T, epsT, T_follow) ):
		return
	syntax_tree += "("
	print "predict term --> factor factor_tail"
	factor()
	factor_tail()
	syntax_tree += ")"

def factor():
	if ( check_error (F, epsF, F_follow) ):
		return
	syntax_tree += "("

	if (input_token is tokens["t_lparen"]):
		print "predict factor --> lparen R_expr rparen"
		
		try:
			match( tokens["t_lparen"] )
		except:
			if ( check_error (["lparen"], False, F_follow) ):
				return
			else:
				match( tokens["t_lparen"] )

		R_expr()
		
		try:
			match( tokens["t_rparen"] )
		except:
			if ( check_error (["rparen"], False, F_follow) ):
				return
			else:
				match( tokens["t_rparen"] )
		
	elif (input_token is tokens["t_id"]):
		print "predict factor --> id"
		
		try:
			match( tokens["t_id"] )
		except:
			if ( check_error (["id"], False, F_follow) ):
				return
			else:
				match( tokens["t_id"] )
		
	elif (input_token is tokens["t_literal"]):
		print "predict factor --> literal"
		
		try:
			match( tokens["t_literal"] )
		except:
			if ( check_error (["literal"], False, F_follow) ):
				return
			else:
				match( tokens["t_literal"] )

	else:
		return

	syntax_tree += ")"


def expr_tail():
	if ( check_error (ET, epsET, ET_follow) ):
		return
	syntax_tree += "("

	if (input_token is (tokens["t_eq_eq"] or tokens["t_not_eq"] or tokens["t_less"] or tokens["t_great"] or tokens["t_less_eq"] or tokens["t_great_eq"])):
		print "print expr_tail --> relational_op expr"
		r_op()
		expr()
	else:
		return
	
	syntax_tree += ")"

def term_tail():
	if ( check_error (TT, epsTT, TT_follow) ):
		return
	syntax_tree += "("

	if ( input_token is ( tokens["t_add"] or tokens["t_sub"] ) ):
		print "predict term_tail --> add_op term term_tail"
		add_op()
		term()
		term_tail()

	else:
		return

	syntax_tree += ")"

def factor_tail():
	if ( check_error (FT, epsFT, FT_follow) ):
		return
	syntax_tree += "("

	if ( input_token is ( tokens["t_mul"] or tokens["t_div"]) ):
		print "predict factor_tail --> mul_op factor factor_tail"
		mul_op()
		factor()
		factor_tail()
	
	else:
		return
		
	syntax_tree += ")"

def r_op():
	if ( check_error (ro, eps_ro, ro_follow) ):
		return
	syntax_tree += "("
	
	if ( input_token is tokens["t_eq_eq"] ):
		print "predict r_op --> equalequal"
		try:
			match( tokens["t_eq_eq"] )
		except:
			if ( check_error (["equalequal"], False, ro_follow) ):
				return
		
	elif ( input_token is tokens["t_not_eq"] ):
		print "predict r_op --> notequal"
		try:
			match( tokens["t_not_eq"] )
		except:
			if ( check_error (["notequal"], False, ro_follow) ):
				return

	elif ( input_token is tokens["t_less"] ):
		print "predict r_op --> lessthan"
		try:
			match( tokens["t_less"] )
		except:
			if ( check_error (["lessthan"], False, ro_follow) ):
				return

	elif ( input_token is tokens["t_great"] ):
		print "predict r_op --> greaterthan"
		try:
			match( tokens["t_great"] )
		except:
			if ( check_error (["greaterthan"], False, ro_follow) ):
				return

	elif ( input_token is tokens["t_less_eq"] ):
		print "predict r_op --> lessORequal"
		try:
			match( tokens["t_less_eq"] )
		except:
			if ( check_error (["lessORequal"], False, ro_follow) ):
				return
	
	elif ( input_token is tokens["t_great_eq"] ):
		print "predict r_op --> greaterORequal"
		try:
			match( tokens["t_great_eq"] )
		except:
			if ( check_error (["greaterORequal"], False, ro_follow) ):
				return
	
	else:
		return

	syntax_tree += ")"

def add_op():
	if ( check_error (mo, eps_mo, mo_follow) ):
		return
	syntax_tree += "("
	
	if ( input_token is tokens["t_add"] ):
		print "predict add_op --> add"
		try:
			match( tokens["t_add"] )
		except:
			if ( check_error (["add"], False, ao_follow) ):
				return
	
	elif ( input_token is tokens["t_sub"] ):
		print "predict add_op --> sub"
		try:
			match( tokens["t_sub"] )
		except:
			if ( check_error (["sub"], False, ao_follow) ):
				return
	
	else:
		return

	syntax_tree += ")"

def mul_op():
	if ( check_error (mo, eps_mo, mo_follow) ):
		return
	syntax_tree += "("
	
	if ( input_token is tokens["t_mul"] ):
		print "predict mul_op --> mul"
		try:
			match( tokens["t_mul"] )
		except:
			if ( check_error (["mul"], False, mo_follow) ):
				return

	elif ( input_token is tokens["t_div"] ):
		print "predict mul_op --> div"
		try:
			match( tokens["t_div"] )
		except:
			if ( check_error (["div"], False, mo_follow) ):
				return
	
	else:
		return

	syntax_tree += ")"


def main():
	input_token = scan("a")
	program()
	return


if __name__ =="__main__":
	main()






