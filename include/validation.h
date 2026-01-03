#ifndef VALIDATION_H
#define VALIDATION_H

#include "list.h"

/*
 * Declares functions for syntax verification and validation of mathematical expressions.
 * Ensures input conforms to rules before evaluation.
 */


bool analyzeSyntaxForNumber(OperationObject *);
bool analyzeSyntaxForOperator(OperationObject *);
bool analyzeSyntaxForConstant(OperationObject *);
bool analyzeSyntaxForSeparator(OperationObject *);
bool analyzeSyntaxForExternalFunction(OperationObject *);
bool checkLeftAndRightSeparators(List *, OperationObject *);
void printSyntaxError(List *, OperationObject *);
bool syntaxAnalysis(List *);

#endif /* VALIDATION_H */