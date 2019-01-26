#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"



Node_t* CreateTree(struct Lexeme_t* lex);  //!< primary grammar

Node_t* GetE(struct Lexeme_t* lex);  //!< works with '+' and '-'
Node_t* GetT(struct Lexeme_t* lex);  //!< works with '*' and '/'
Node_t* GetF(struct Lexeme_t* lex);  //!< works with different functions
Node_t* GetP(struct Lexeme_t* lex);  //!< works with '(' and ')'
Node_t* GetN(struct Lexeme_t* lex);  //!< works with numbers
Node_t* GetV(struct Lexeme_t* lex);  //!< works with variables
