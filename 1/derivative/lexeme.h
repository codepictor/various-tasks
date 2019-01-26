//! {======================================================
//! @file lexeme.h
//! @date 2014-11-30
//! @author Artem Mikhalev <grozzmaster@gmail.com>
//!
//! This file helps to do lexical analysis
//! }======================================================

#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct Lexeme_t
{
    int type;
    int number;
    char* str;
};


enum Type_of_lexeme
{
    LEX_BEGIN,
    LEX_NUMBER,
    LEX_OPERATOR,
    LEX_VARIABLE,
    LEX_BRACKET,
    LEX_FUNCTION,
    LEX_END,
    LEX_ERROR
};


enum Functions_t
{
    FUNC_SIN,
    FUNC_COS,
    FUNC_POW,
    FUNC_MAX
};


enum Errors_t
{
    ERR_HAPPINESS,
    ERR_SYNTAX_ERROR,
    ERR_TOO_LONG,
    ERR_TOO_FEW,
    ERR_MAX
};


char* str = 0;                 //!< pointer to the string
int len = 0;                   //!< is a length of the string

const int MAXLEN = 1000;       //!< max length of the string


void      GetStr       ();                         //!< scans string
void      DestructStr  (struct Lexeme_t* lex);     //!< destroys input string and lexemes
Lexeme_t* LexAnalysis  ();                         //!< lexical analysis
void      LexDump      (struct Lexeme_t* lex);     //!< prints lexemes
int       CheckLexemes (struct Lexeme_t* lex);     //!< finds syntax errors
void      Diagnostics  (int nERR, int position);   //!< prints diagnostics if there is an error in the expression



//! WARNING! This function includes #define!-------------
//{ Printing Diagnostics if there are some syntax errors in the expression
//! -----------------------------------------------------

#define DIAGNOSTICS { Diagnostics (ERR_SYNTAX_ERROR, i); return ERR_SYNTAX_ERROR; }

