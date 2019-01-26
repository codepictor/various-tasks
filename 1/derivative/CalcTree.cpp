//! {======================================================
//! @file calc.cpp
//! @date 2014-11-30
//! @author Artem Mikhalev <grozzmaster@gmail.com>
//!
//! Differentiation
//! }======================================================

#include "CalcTree.h"


int count = 1;  //!< current lexeme


Node_t* CreateTree(struct Lexeme_t* lex)
{
    assert(lex);
    Node_t* root = GetE (lex);

    if ((lex + count)->type != LEX_END)
    {
        Diagnostics(ERR_SYNTAX_ERROR, count);
    }

    return root;
}



Node_t* GetE(struct Lexeme_t* lex)
{
    assert(lex);
    assert (0 < count && count < len);

    Node_t* node = GetT(lex);
    int cnt = 0;

    while ((lex + count)->type == LEX_OPERATOR
        && (*(lex + count)->str == '+' || *(lex + count)->str == '-'))
    {
        cnt = count;
        count++;
        node = NodeNew(NODE_OPERATOR, (lex + cnt)->str, node, GetT(lex));
    }

    return node;
}



Node_t* GetT(struct Lexeme_t* lex)
{
    assert(lex);
    assert(0 < count && count < len);

    Node_t* node = GetF(lex);
    int cnt = 0;

    while ((lex + count)->type == LEX_OPERATOR
        && (*(lex + count)->str == '*' || *(lex + count)->str == '/'))
    {
        cnt = count;
        count++;
        node = NodeNew(NODE_OPERATOR, (lex + cnt)->str, node, GetF(lex));
    }

    return node;
}



Node_t* GetF(struct Lexeme_t* lex)
{
    assert(lex);
    assert(0 < count && count < len);

    Node_t* node = GetP(lex);
    int func = 0;

    while ((lex + count)->type == LEX_FUNCTION)
    {
        func = (lex + count)->number;
        assert (0 <= func && func < FUNC_MAX);

        count++;
        node = NodeNew(NODE_FUNCTION, &func, node, GetP(lex));
    }

    return node;
}



Node_t* GetP(struct Lexeme_t* lex)
{
    assert(lex);
    assert(0 < count && count < len);

    Node_t* node = GetN(lex);

    if ((lex + count)->type == LEX_BRACKET && *(lex + count)->str == '(')
    {
        count++;
        node = GetE(lex);

        if ((lex + count)->type != LEX_BRACKET || *(lex + count)->str != ')')
        {
            Diagnostics (ERR_SYNTAX_ERROR, count);
        }

        count++;
        return node;
    }

    return node;
}



Node_t* GetN(struct Lexeme_t* lex)
{
    assert(lex);
    assert(0 < count && count < len);

    Node_t* node = GetV(lex);

    if ((lex + count)->type == LEX_NUMBER)
    {
        int val = 0;

        val = (lex + count)->number;
        count++;

        return NodeNew(NODE_NUMBER, &val, NULL, NULL);
    }

    return node;
}



Node_t* GetV(struct Lexeme_t* lex)
{
    assert(lex);
    assert(0 < count && count < len);

    if ((lex + count)->type == LEX_VARIABLE && *(lex + count)->str == 'x')
    {
        count++;
        return NodeNew(NODE_VARIABLE, (lex + count - 1)->str, NULL, NULL);
    }

    return NULL;
}

