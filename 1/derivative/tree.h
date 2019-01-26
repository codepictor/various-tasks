//! {======================================================
//! @file tree.h
//! @date 2014-11-30
//! @author Artem Mikhalev <grozzmaster@gmail.com>
//!
//! This file helps to work with binary trees
//! }======================================================

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "lexeme.h"
#include "tex.h"

struct Node_t
{
    int type;
    int value;
    char str;
    Node_t* left;
    Node_t* right;
};

enum Type_of_node
{
    NODE_NUMBER,
    NODE_OPERATOR,
    NODE_VARIABLE,
    NODE_FUNCTION,
    NODE_ERROR
};

enum Brackets_t
{
    TEX_NOBRACKET,
    TEX_BRACKET,
    TEX_ERROR
};



Node_t*  NodeNew         (const int argtype, const void* arg, Node_t* const left, Node_t* const right);
Node_t*  Differentiation (struct Node_t* root);
Node_t*  DiffMul         (struct Node_t* node);
Node_t*  DiffDiv         (struct Node_t* node);
Node_t*  DiffFunc        (struct Node_t* node);
Node_t*  TreeCopy        (struct Node_t* node);

void    DestructTree    (struct Node_t* node);
void    TreeDump        (struct Node_t* root);
void    VisualDump      (FILE* out, Node_t* node, int *count);
void    SimpleNode      (struct Node_t* node, int val);

int OptimizeTree (struct Node_t* root);
int Optimize1    (struct Node_t* node);
int Optimize2    (struct Node_t* node);

int  Zero        (struct Node_t* node);
int  SimpleMul   (struct Node_t* node);
int  SimpleDiv   (struct Node_t* node);
int  SimpleSum   (struct Node_t* node);
int  SimpleSub   (struct Node_t* node);
void SaveTree    (struct Node_t* node, struct Node_t* side);
void NodeCopy    (struct Node_t* first, struct Node_t* second);
int  SimplePow   (struct Node_t* node, int pow);

int  IfBracket (Node_t* const node, Node_t* const side);
void TexDump   (Node_t* const root, const int mode);
void PrintTree (Node_t* const node, const int mode);





//{ Creating a new node
//! --------------------------------------------------------------------------

Node_t* NodeNew (const int argtype, const void* arg, Node_t* const left, Node_t* const right)
{
    assert (NODE_NUMBER <= argtype && argtype < NODE_ERROR);
    assert (arg);

    Node_t* new_node = (Node_t*) calloc (1, sizeof (Node_t));
    assert (new_node);

    switch (argtype)
    {
        case NODE_NUMBER:
            new_node->value = *(int*) arg;
            new_node->type = NODE_NUMBER;
            break;

        case NODE_OPERATOR:
            new_node->str = *(char*) arg;
            new_node->type = NODE_OPERATOR;
            break;

        case NODE_VARIABLE:
            new_node->str = *(char*) arg;
            new_node->type = NODE_VARIABLE;
            break;

        case NODE_FUNCTION:
            new_node->value = *(int*) arg;
            new_node->type = NODE_FUNCTION;
            break;

        default:
            printf ("ERROR. Unknown type of the node in the function 'NodeNew'!\n");
            printf ("The pointer to the new node will be NULL!\n");
            assert (0);
    }

    new_node->left  = left;
    new_node->right = right;

    return new_node;
}

//! --------------------------------------------------------------------------
//} Creating a new node



//{ Copying of the tree
//! --------------------------------------------------------------------------

Node_t* TreeCopy (struct Node_t* node)
{
    if (node == NULL) return NULL;

    Node_t* left = NULL;
    Node_t* right = NULL;

    if (node->left)  left  = TreeCopy (node->left);
    if (node->right) right = TreeCopy (node->right);

    if (node->type == NODE_NUMBER || node->type == NODE_FUNCTION)
        return NodeNew (node->type, &node->value, left, right);

    return NodeNew (node->type, &node->str, left, right);
}

//! --------------------------------------------------------------------------
//} Copying of the tree



//{ Destructing a tree
//! --------------------------------------------------------------------------

void DestructTree (struct Node_t* node)
{
    assert (node);

    if (node->left)  DestructTree (node->left);
    if (node->right) DestructTree (node->right);

    free (node);
    node = NULL;

    return;
}

//! --------------------------------------------------------------------------
//} Destructing a tree



//{ Differentiation
//! --------------------------------------------------------------------------

Node_t* Differentiation (struct Node_t* node)
{
    assert (node);
    assert (NODE_NUMBER <= node->type && node->type < NODE_ERROR);

    int val = 0;

    switch (node->type)
    {
        case NODE_NUMBER:
            return NodeNew (NODE_NUMBER, &val, NULL, NULL);
            break;

        case NODE_VARIABLE:
            val = 1;
            return NodeNew (NODE_NUMBER, &val, NULL, NULL);
            break;

        case NODE_FUNCTION:
            return DiffFunc (node);
            break;

        case NODE_OPERATOR:
            assert (node->left);
            assert (node->right);
            assert (node->str);

            if (node->str == '+' || node->str == '-')
                return NodeNew (NODE_OPERATOR, &node->str, Differentiation (node->left), Differentiation (node->right));

            if (node->str == '*')
                return DiffMul (node);

            if (node->str == '/')
                return DiffDiv (node);
            break;


        default: printf ("ERROR. Unknown type of the node in the function 'Differentiation'!\n");

        assert (0);
    }

    assert (0);
    return NodeNew (NODE_ERROR, NULL, NULL, NULL);
}


Node_t* DiffMul (struct Node_t* node)
{
    assert (node);
    assert (node->type == NODE_OPERATOR);
    assert (node->left);
    assert (node->right);

    Node_t* left  = NodeNew (NODE_OPERATOR, "*", Differentiation (node->left), TreeCopy (node->right));
    Node_t* right = NodeNew (NODE_OPERATOR, "*", TreeCopy (node->left), Differentiation (node->right));

    return NodeNew (NODE_OPERATOR, "+", left, right);
}


Node_t* DiffDiv (struct Node_t* node)
{
    assert (node);
    assert (node->type == NODE_OPERATOR);
    assert (node->left);
    assert (node->right);

    Node_t* node1 = NodeNew (NODE_OPERATOR, "*", Differentiation (node->left), TreeCopy (node->right));
    Node_t* node2 = NodeNew (NODE_OPERATOR, "*", TreeCopy (node->left), Differentiation (node->right));
    Node_t* node3 = NodeNew (NODE_OPERATOR, "-", node1, node2);
    Node_t* node4 = NodeNew (NODE_OPERATOR, "*", TreeCopy (node->right), TreeCopy (node->right));

    return NodeNew (NODE_OPERATOR, "/", node3, node4);
}


Node_t* DiffFunc (struct Node_t* node)
{
    assert (node);
    assert (node->type == NODE_FUNCTION);
    assert (node->right);

    Node_t* left  = NULL;
    Node_t* right = NULL;
    int val = 0;

    switch (node->value)
    {
        case FUNC_SIN:
            val = FUNC_COS;
            left = NodeNew (NODE_FUNCTION, &val, NULL, TreeCopy (node->right));

            right = Differentiation (node->right);

            return NodeNew (NODE_OPERATOR, "*", left, right);
            break;

        case FUNC_COS:
            val = 0;
            left = NodeNew (NODE_NUMBER, &val, NULL, NULL);
            val = FUNC_SIN;
            right = NodeNew (NODE_FUNCTION, &val, NULL, TreeCopy (node->right));
            left = NodeNew (NODE_OPERATOR, "-", left, right);

            right = Differentiation (node->right);

            return NodeNew (NODE_OPERATOR, "*", left, right);
            break;

        case FUNC_POW:
            val = node->right->value;
            left = NodeNew (NODE_NUMBER, &val, NULL, NULL);

            val = FUNC_POW;
            right = NodeNew (NODE_FUNCTION, &val, TreeCopy (node->left), TreeCopy (node->right));
            (right->right->value)--;
            left = NodeNew (NODE_OPERATOR, "*", left, right);

            return NodeNew (NODE_OPERATOR, "*", left, Differentiation (node->left));
            break;

        default:
            printf ("Unknown type of function in 'DiffFunc'!\n");
    }

    printf ("Unknown type of a function in 'DiffFunc'!\n");
    return NULL;
}

//! --------------------------------------------------------------------------
//} Differentiation



//{ TreeDump
//! --------------------------------------------------------------------------

void TreeDump (Node_t* root)
{
    assert (root);

    FILE* out = fopen ("TreeDump.txt", "w");
    assert (out);

    int count = 0;
    VisualDump (out, root, &count);

    assert (!fclose (out));

    return;
}

void VisualDump (FILE* out, Node_t* node, int *count)
{
    assert (out);
    assert (node);
    assert (NODE_NUMBER <= node->type && node->type < NODE_ERROR);
    assert (count);

    for (int i = 0; i < *count; i++)
        fprintf (out, "    ");

    switch (node->type)
    {
        case NODE_NUMBER:   fprintf (out, "(%d", node->value); break;
        case NODE_OPERATOR: fprintf (out, "(%c", node->str);   break;
        case NODE_VARIABLE: fprintf (out, "(%c", node->str);   break;
        case NODE_FUNCTION:
            switch (node->value)
            {
                case FUNC_SIN: fprintf (out, "(sin"); break;
                case FUNC_COS: fprintf (out, "(cos"); break;
                case FUNC_POW: fprintf (out, "(^");   break;

                default: printf ("ERROR. Unknown type of the function in 'VisualDump'! (%d)\n", node->type);
            }
        break;

        default: printf ("ERROR. Unknown type of the node in the function 'VisualDump'!\n");
    }

    if (node->left)
    {
        fprintf (out, "\n");
        VisualDump (out, node->left,  &(++(*count)) );
    }

    if (node->right)
    {
        fprintf (out, "\n");
        VisualDump (out, node->right, &(++(*count)) );

        fprintf (out, "\n");
        for (int i = 0; i < *count; i++)
            fprintf (out, "    ");
    }

    fprintf (out, ")");

    (*count)--;

    return;
}

//! --------------------------------------------------------------------------
//} TreeDump



//{ Optimization
//! --------------------------------------------------------------------------

int OptimizeTree (struct Node_t* root)
{
    assert (root);

    PrintText (OUT_FORMULA);
    TexDump (root, OUT_FORMULA);
    fprintf (texout, "\n\n");

    return Optimize1 (root) + Optimize2 (root);
}

int Optimize1 (struct Node_t* node)
{
    assert (node);

    int val = 0, ret_left = 0, ret_right = 0;

    if (node->left)  ret_left  = Optimize1 (node->left);
    if (node->right) ret_right = Optimize1 (node->right);

    if (node->type == NODE_OPERATOR)
    {
        assert (node->str);

        if (node->left->type == NODE_NUMBER && node->right->type == NODE_NUMBER)
        {
            PrintText (OUT_TEXT);
            TexDump (node, OUT_TEXT);

            if (node->str == '+')
                val = node->left->value + node->right->value;

            if (node->str == '-')
                val = node->left->value - node->right->value;

            if (node->str == '*')
                val = node->left->value * node->right->value;

            if (node->str == '/' && node->right->value == 0)
                printf ("ERROR. Division by zero!\n");

            if (node->str == '/' && node->right->value != 0)
                val = node->left->value / node->right->value;

            SimpleNode (node, val);
            ret_left  = 1;
            ret_right = 1;

            fprintf (texout, " = ");
            TexDump (node, OUT_TEXT);
            fprintf (texout, ".\n");
        }
    }

    return ret_left + ret_right;
}

int Optimize2 (struct Node_t* node)
{
    assert (node);

    int val = 0, ret_left = 0, ret_right = 0;

    if (node->left)  ret_left  = Optimize2 (node->left);
    if (node->right) ret_right = Optimize2 (node->right);

    if (node->type == NODE_OPERATOR)
    {
        assert (node->str);

        if ((node->left->type == NODE_NUMBER && node->left->value == 0 || node->right->type == NODE_NUMBER && node->right->value == 0) && node->str == '*')
            return Zero (node);

        if (node->left->type == NODE_NUMBER && node->left->value == 0 && node->str == '/')
            return Zero (node);

        if ((node->left->type == NODE_NUMBER && node->left->value == 1 || node->right->type == NODE_NUMBER && node->right->value == 1) && node->str == '*')
            return SimpleMul (node);

        if ((node->right->type == NODE_NUMBER && node->right->value == 1) && node->str == '/')
            return SimpleDiv (node);

        if ((node->left->type == NODE_NUMBER && node->left->value == 0 || node->right->type == NODE_NUMBER && node->right->value == 0) && node->str == '+')
            return SimpleSum (node);

        if ((node->right->type == NODE_NUMBER && node->right->value == 0) && node->str == '-')
            return SimpleSub (node);

        if ((node->right->type == NODE_VARIABLE && node->left->type == NODE_VARIABLE) && node->str == '-')
            return Zero (node);

        if ((node->right->type == NODE_NUMBER && node->right->value == 0) && node->str == '/')
            printf ("ERROR. Division by zero!\n");
    }

    if (node->type == NODE_FUNCTION && node->value == FUNC_POW)
    {
        if (node->right->type == NODE_NUMBER && (node->right->value == 0 || node->right->value == 1))
            ret_left += SimplePow (node, node->right->value);
    }

    return ret_left + ret_right;
}




void SimpleNode (struct Node_t* node, int val)
{
    assert (node);

    DestructTree (node->left);
    DestructTree (node->right);
    node->left  = NULL;
    node->right = NULL;
    node->str   = 0;
    node->value = val;
    node->type  = NODE_NUMBER;

    return;
}

int SimplePow (struct Node_t* node, int pow)
{
    assert (node);
    assert (pow == 0 || pow == 1);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    if (pow == 1)
        SaveTree (node, node->left);
    else
        SimpleNode (node, 1);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}

int Zero (struct Node_t* node)
{
    assert (node);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    SimpleNode (node, 0);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}

int SimpleMul (struct Node_t* node)
{
    assert (node);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    if (node->left->value == 1 && node->left->type == NODE_NUMBER)
        SaveTree (node, node->right);
    else
        SaveTree (node, node->left);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}

int SimpleDiv (struct Node_t* node)
{
    assert (node);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    SaveTree (node, node->left);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}

int SimpleSum (struct Node_t* node)
{
    assert (node);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    if (node->left->value == 0 && node->left->type == NODE_NUMBER)
        SaveTree (node, node->right);
    else
        SaveTree (node, node->left);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}

int SimpleSub (struct Node_t* node)
{
    assert (node);

    PrintText (OUT_TEXT);
    TexDump (node, OUT_TEXT);

    SaveTree (node, node->left);

    fprintf (texout, " = ");
    TexDump (node, OUT_TEXT);
    fprintf (texout, ".\n");

    return 1;
}



void SaveTree (struct Node_t* node, struct Node_t* side)
{
    assert (node);
    assert (side);

    NodeCopy (side, node);
    Node_t* new_left  = TreeCopy (side->left);
    Node_t* new_right = TreeCopy (side->right);
    DestructTree (node->left);
    DestructTree (node->right);
    node->left  = new_left;
    node->right = new_right;

    return;
}

void NodeCopy (struct Node_t* first, struct Node_t* second)
{
    assert (first);
    assert (second);

    second->type  = first->type;
    second->str   = first->str;
    second->value = first->value;

    return;
}


//! --------------------------------------------------------------------------
//} Optimization










































void TexDump (Node_t* const root, const int mode)
{
    assert (root);
    assert (0 <= mode < OUT_ERROR);

    if (mode == OUT_TEXT)
        fprintf (texout, "$");
    else
        fprintf (texout, "\\[\n");

    if (mode == OUT_RESULT && root->type == NODE_NUMBER && root->left == NULL && root->right == NULL && root->value == 0)
        fprintf (texout, "%d", root->value);
    else
        PrintTree (root, mode);

    if (mode == OUT_TEXT)
        fprintf (texout, "$");
    else
        fprintf (texout, "\n\\]");

    return;
}


void PrintTree (Node_t* const node, const int mode)
{
    assert (node);
    assert (NODE_NUMBER <= node->type && node->type < NODE_ERROR);
    assert (0 <= mode < OUT_ERROR);

    switch (node->type)
    {
        case NODE_NUMBER:
            assert (!node->left);
            assert (!node->right);
            if (mode == OUT_TEXT) fprintf (texout, "%d ", node->value);
            else if (node->value != 0) fprintf (texout, "%d ", node->value);
            break;

        case NODE_VARIABLE:
            assert (!node->left);
            assert (!node->right);
            fprintf (texout, "%c ", node->str);
            break;

        case NODE_OPERATOR:
            if (node->str == '/') fprintf (texout, "\\frac{");

            if (IfBracket (node, node->left) == 1)
            {
                fprintf (texout, "\\left(");
                PrintTree (node->left, mode);
                fprintf (texout, "\\right) ");
            }
            else
                PrintTree (node->left, mode);

            if (node->str == '*') fprintf (texout, "\\cdot ");
            if (node->str == '/') fprintf (texout, "}{");
            if (node->str == '+') fprintf (texout, "+ ");
            if (node->str == '-') fprintf (texout, "- ");

            if (IfBracket (node, node->right) == 1)
            {
                fprintf (texout, "\\left(");
                PrintTree (node->right, mode);
                fprintf (texout, "\\right) ");
            }
            else
                PrintTree (node->right, mode);

            if (node->str == '/') fprintf (texout, "} ");

            break;

        case NODE_FUNCTION:
            switch (node->value)
            {
                case FUNC_SIN:
                    fprintf (texout, "\\sin");
                    if (IfBracket (node, node->right) == 1)
                    {
                        fprintf (texout, "\\left(");
                        PrintTree (node->right, mode);
                        fprintf (texout, "\\right) ");
                    }
                    else
                    {
                        fprintf (texout, "\\,");
                        PrintTree (node->right, mode);
                    }
                    break;

                case FUNC_COS:
                    fprintf (texout, "\\cos");
                    if (IfBracket (node, node->right) == 1)
                    {
                        fprintf (texout, "\\left(");
                        PrintTree (node->right, mode);
                        fprintf (texout, "\\right) ");
                    }
                    else
                    {
                        fprintf (texout, "\\,");
                        PrintTree (node->right, mode);
                    }
                    break;

                case FUNC_POW:
                    fprintf (texout, "{");
                    if (IfBracket (node, node->left) == 1)
                    {
                        fprintf (texout, "\\left(");
                        PrintTree (node->left, mode);
                        fprintf (texout, "\\right) ");
                    }
                    else
                        PrintTree (node->left, mode);

                    fprintf (texout, "}^{");

                    if (IfBracket (node, node->right) == 1)
                    {
                        fprintf (texout, "\\left(");
                        PrintTree (node->right, mode);
                        fprintf (texout, "\\right) ");
                    }
                    else
                        PrintTree (node->right, mode);

                    fprintf (texout, "}");
                    break;
            }
            break;

        default: printf ("Unknown type of node in the function 'PrintNode'!\n");
    }

    return;
}




int IfBracket (Node_t* const node, Node_t* const side)
{
    assert (node);
    assert (side);
    assert (node->type == NODE_OPERATOR || node->type == NODE_FUNCTION);

    if (node->type == NODE_OPERATOR)
    {
        if (node->str == '+' || node->str == '-')
        {
            if (side->type == NODE_OPERATOR && node->right == side && (side->str == '-' || side->str == '+'))
                return 1;
        }

        if (node->str == '*')
        {
            if (side->type == NODE_OPERATOR && (side->str == '+' || side->str == '-'))
                return 1;
        }
    }

    else
    {
        if (node->value == FUNC_SIN || node->value == FUNC_COS)
        {
            assert (node->right);
            assert (!node->left);
            assert (node->right == side);

            if (side->type == NODE_OPERATOR || side->type == NODE_FUNCTION)
                return 1;
        }

        if (node->value == FUNC_POW)
        {
            if (side->type == NODE_OPERATOR || side->type == NODE_FUNCTION)
                return 1;
        }
    }

    return 0;
}









//!
//! --------------------------------------------------------------------------






