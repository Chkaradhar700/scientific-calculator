#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <float.h>

//NOTE : We will use the "long double" type to represent real numbers and the "long long" type to represent integers.

#define FUNCTION_NAME_SIZE 20
#define FUNCTION_ARGS_SIZE 10000
#define MAX_LENGTH_OF_NUMBER 100
#define COMMAND_LENGTH 500
#define LENGTH_OF_MODE 4

//The commands
#define C_SET_M "setMode"
#define C_BACK "back"
#define C_SET_P "setPrecision"
#define C_DISPLAY_I "displayInfos"
#define C_CLEAR "clear"
#define C_EXIT "exit"

//Constants
#define PI "pi"
#define E "e"

//Operators
#define OP_DIVIDE "/"
#define OP_TIMES "*"
#define OP_U_MINUS "u-"
#define OP_B_MINUS "b-"
#define OP_PLUS "+"
#define OP_PERCENT "%"
#define OP_FACTORIAL "!"
#define OP_POWER "^"

//External functions; E for External
//External functions are the functions that the user can use. Their names can be easily imagined by the user, for example "sin", "ln". They all have a correspondence among the internal functions.
#define E_SQRT "sqrt"
#define E_SIN "sin"
#define E_COS "cos"
#define E_TAN "tan"
#define E_LN "ln"
#define E_LOG "log"
#define E_ASIN "asin"
#define E_ACOS "acos"
#define E_ATAN "atan"
#define E_EXP "exp"

//Internal functions
//Internal functions are the functions used only inside the program. Their names are like abbreviations because the normal names of some functions are too long.
#define ACOSL "ac"
#define ASINL "as"
#define ATANL "at"
#define COSL "co"
#define SINL "si"
#define TANL "ta"
#define EXPL "ex"
#define LOGL "ln"
#define LOG10L "lg"
#define POWL "po"
#define SQRTL "sq"
#define ADD "ad"
#define SUBTRACT "su"
#define MULTIPLY "mu"
#define DIVIDE "di"
#define PERCENTAGE "pe"
#define FACTORIAL "fa"
#define OPPOSITE "op"
#define TO_DECIMAL "td"

#endif /* COMMON_H */