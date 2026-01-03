# HISTORY

## Introduction

This project, named **Scientific Calculator**, was written in 2023.

It started with the simple idea of building a project in C (or C++). While searching online for project ideas, I repeatedly came across discussions about calculator programs. That topic caught my attention.

I had already written calculation programs in the past, but they were always very basic ones: programs that asked the user to input two numbers, then choose an operation to apply. This time, I wanted to go further and build a more complete calculator.

The goal was clear: the user should be able to type a mathematical expression in text form, and the program should evaluate it correctly.

For example, if the user types:

```
2+3*4
```

the program must be able to return:

```
14
```


## 1. Basic mathematical functions

I chose to write the program in **C**.

To define the basic features, I took inspiration from a calculator application available on my smartphone. The first idea was to create one function per mathematical operation, plus a central function responsible for *operating*.

I implemented functions for: addition, subtraction, multiplication, division, percentage and factorial.

I did not reimplement functions such as sine, cosine, logarithms, etc., because they are already provided by the C standard math library (`math.h`).

All these functions return real numbers. To maximize precision, I decided to use the `long double` type for parameters and return values. The program is therefore compiled with the `-lm` option so that mathematical functions are properly linked.

These functions are considered **internal functions** of the program.


## 2. From expressions to function calls

Very early on, I decided that calculations should go through an intermediate representation: every operation would be rewritten as a textual function call.

For example, to compute:

```
2+3*4
```

the program should internally convert it to something like:

```
add(2,multiply(3,4))
```

At that stage, I did not yet know how to perform this conversion automatically, but I knew operator precedence would be a key issue.

The central function, named `operate(...)`, takes such a string as input. Its role is to:

1. identify which function to call
2. extract its arguments
3. evaluate them

To achieve this, I created a function called `getFunctionInfos(...)`. It analyzes a string and returns a structure containing:

* the function name
* its first argument
* its second argument (if any)

Because functions can be nested, `operate(...)` must be **recursive**.

For example:

* `operate("add(2,3)")` becomes `add(operate("2"), operate("3"))`
* `operate("add(2,multiply(3,4))")` becomes
  `add(operate("2"), multiply(operate("3"), operate("4")))`


## 3. Literal numbers and `toDecimal`

Normally, `operate(...)` expects explicit function calls. A call like:

```
operate("2")
```

is not valid by itself.

To solve this, I introduced a special internal function named `toDecimal(...)`. Unlike other internal functions, it takes a **string** as input and converts it into a `long double`.

This function is only used to convert numeric literals written as text.

So instead of:

```
add(2,multiply(3,4))
```

the correct internal representation becomes:

```
add(toDecimal(2),multiply(toDecimal(3),toDecimal(4)))
```


## 4. Long expressions and error detection

As expressions grow more complex, the strings manipulated by `operate(...)` can become quite long. To keep the code readable and maintainable, I decided to use **symbolic definitions** (macros) for all internal function names.

I also added a function named `detectNanInfErrors(...)` to detect special floating-point errors such as: Infinity and Not-a-Number (NaN)

This allows the program to stop invalid computations early and avoid undefined behavior.


## 5. Using lists instead of raw strings

Direct string manipulation quickly became difficult and unintuitive.

To improve this, I introduced **doubly linked lists** to represent mathematical expressions. Each element of the list corresponds to an operation object (number, operator, function, etc.).

I implemented:

* a structure for doubly linked lists
* helper functions to insert and remove objects safely

Lists are used at several stages of the program:

* to represent user input
* to progressively transform expressions
* to allow easy insertion and deletion of elements


## 6. Trees and operator hierarchy

The `operate(...)` function only works with expressions where the evaluation order is already explicit. In practice, user input often relies on implicit precedence rules.

To resolve this, I introduced two key concepts:

* **blocks**
* **operators**

A block can be:

* a parenthesized expression: `(2+4/6)`
* a function call: `sin(10)`
* a single number

Any mathematical expression can therefore be represented as a hierarchy of blocks and operators — in other words, as a **tree**.

Each node of the tree represents a block, along with the operators it contains. I created:

* a tree structure
* functions to build, traverse, and manipulate trees


## 7. The `manage...` functions

Once the structure of expressions was clear, another problem remained: how to transform a list like:

```
2+3
```

into:

```
add(td(2),td(3))
```

To handle this, I implemented several functions prefixed with `manage...`: `manageConstant(...)`, `manageNumber(...)`, `manageOperator(...)`, `manageExternalFunction(...)` and `manageAdditionalParentheses(...)`.

Each function performs a specific transformation step. Their order of execution is fixed in the code and ensures a progressive, consistent conversion of user input into a valid internal representation.


## 8. Operator sorting and full transformation

Operators inside the same block must be evaluated according to priority and direction. To do this, I implemented: `sortOperators(...)`. I also created: `manageBlockOperators(...)` and `manageAllObjects(...)`.

At the end of this process, a valid user expression is converted into a string that can safely be passed to `operate(...)`.

However, not all user inputs are valid. This made **syntax validation** necessary.


## 9. Syntax validation

Syntax validation starts with the function `stringToList(...)`, which converts a raw string into a list of operation objects.

Then, several functions analyze the syntax rules of the expression. These rules are detailed in the [README](README.md#full-syntax-rules) and are based on:

* the previous element
* the next element
* correct parenthesis matching

Additional preprocessing is done using:

* `manageAllConstants(...)`
* `manageImplicitMultiplications(...)`

Once these steps are completed, the expression is ready for evaluation.


## 10. Command-line interface and tools

To make the program usable, I added a command-line interface with helper functions such as: `isCommand(...)` and `c_setPrecision(...)`.

I also explored extensibility. As a first example, I added a **prime number checker** as an additional tool.

The architecture allows more tools to be added later without modifying the core calculation engine.


## 11. Publishing the project on GitHub

By late 2025 and early 2026, I decided to publish the project on GitHub.

At that point, the calculator was already functional, but the codebase had grown a lot and was still organized around a single large `main.c` file of several thousand lines. Publishing the project was an opportunity to clean things up and make the code easier to understand, build, and maintain.

Several actions were taken during this phase:

* The code was split into multiple modules, each one focused on a specific responsibility (parsing, lists, trees, arithmetic operations, tools, etc.).
* Header files were introduced to clearly define module boundaries.
* A `Makefile` was created to simplify compilation, linking, and execution, including a dedicated target for running tests.
* Test code that was previously commented inside `main.c` was moved into a separate test file.
* A basic project structure was set up to make future extensions easier.

This phase did not aim to change the core logic of the calculator, but rather to make the project more readable, more maintainable, and easier to share with others.

From that point on, the project was no longer just a personal experiment, but something that could be explored, compiled, and improved by anyone interested in how the calculator works internally.

