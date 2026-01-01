#ifndef VALIDATION_H
#define VALIDATION_H

#include "list.h"

bool analyzeSyntaxForNumber(OperationObject *);
bool analyzeSyntaxForOperator(OperationObject *);
bool analyzeSyntaxForConstant(OperationObject *);
bool analyzeSyntaxForSeparator(OperationObject *);
bool analyzeSyntaxForExternalFunction(OperationObject *);
bool checkLeftAndRightSeparators(List *, OperationObject *);
void printSyntaxError(List *, OperationObject *);
bool syntaxAnalysis(List *);

#endif /* VALIDATION_H */