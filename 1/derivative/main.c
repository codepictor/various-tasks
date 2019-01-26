#include "tree.h"
#include "lexeme.h"
#include "tex.h"


int main()
{
    GetStr();
    Lexeme_t* lex = LexAnalysis();
    //LexDump(lex);

    int nERR = CheckLexemes(lex);
    if (nERR)
    {
        DestructStr(lex);
        return nERR;
    }

    TexPrepare();

    Node_t* primary_root = CreateTree(lex);
    while (OptimizeTree(primary_root))
    {
    }

    Node_t* diff_root = Differentiation(primary_root);
    while (OptimizeTree(diff_root))
    {
    }

    PrintText(OUT_RESULT);
    TexDump(diff_root, OUT_RESULT);
    TexEnd();
    //TreeDump(diff_root);

    DestructTree(primary_root);
    DestructTree(diff_root);
    DestructStr(lex);

    return 0;
}

