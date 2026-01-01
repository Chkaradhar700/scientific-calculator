#ifndef TREE_H
#define TREE_H

#include "list.h"

enum Direction
{
	left_to_right,
	right_to_left
};
typedef enum Direction Direction;

typedef struct Block Block;
struct Block
{
	OperationObject *beginning;
	OperationObject *end;
	short int nbrOfOperators;
	OperationObject **operators;
	short int nbrOfSubBlocks;
	Block **subBlocks;
};

typedef struct Tree Tree;
struct Tree
{
	Block *root;
	List *associatedList;
};

typedef struct Blocks Blocks;
struct Blocks
{
	short int nbrOfBlocks;
	Block **blocks;
};


Tree *initializeTree();
void fillBlock(Block *, List *);
void fillTree(Tree *, List *);
void deleteBlock(Block *);
void deleteAllFromTree(Tree *);
char *blockToString(Block *);
char *treeToString(Tree *);

Block *identifyBlockFrom(List *, OperationObject *, Direction);
Blocks identifyBlocksBetween(List *, OperationObject *, OperationObject *);

#endif /* TREE_H */