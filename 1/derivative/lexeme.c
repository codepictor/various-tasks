#include "lexeme.h"



int CheckLexemes (struct Lexeme_t* lex)
{
    assert (lex);
    if ((lex + 1)->type == LEX_END)
    {
        Diagnostics (ERR_TOO_FEW, 1);
        return ERR_TOO_FEW;
    }

    int i = 1, next = 0, prev = 0, open_bracket = 0;

    while ((lex + i)->type != LEX_END)
    {
        next = (lex + i + 1)->type;
        prev = (lex + i - 1)->type;

        switch ((lex + i)->type)
        {
            case LEX_NUMBER:
                if (prev == LEX_NUMBER || prev == LEX_VARIABLE || next == LEX_NUMBER || next == LEX_VARIABLE)
                    DIAGNOSTICS
            break;

            case LEX_OPERATOR:
                if (prev == LEX_OPERATOR || prev == LEX_BEGIN || next == LEX_OPERATOR || next == LEX_END)
                    DIAGNOSTICS
            break;

            case LEX_VARIABLE:
                if (prev == LEX_NUMBER || prev == LEX_VARIABLE || next == LEX_NUMBER || next == LEX_VARIABLE)
                    DIAGNOSTICS
            break;

            case LEX_FUNCTION:
                if ((lex + i)->number == FUNC_POW)
                {
                    if (prev == LEX_OPERATOR || next == LEX_OPERATOR)
                        DIAGNOSTICS
                }
                else
                {
                    if (prev == LEX_NUMBER || prev == LEX_VARIABLE || next == LEX_OPERATOR || next == LEX_END)
                        DIAGNOSTICS
                }
            break;

            case LEX_BRACKET:
                if (*(lex + i)->str == '(')
                {
                    open_bracket++;
                    if ((lex + i + 1)->type == LEX_BRACKET)
                    {
                        if (*(lex + i + 1)->str == ')')
                            DIAGNOSTICS
                    }
                }

                else
                    open_bracket--;

                if (open_bracket < 0)
                    DIAGNOSTICS
            break;

            default: DIAGNOSTICS

        }

        i++;
    }

    i--;
    if (open_bracket != 0) DIAGNOSTICS

    return 0;
}

#undef DIAGNOSTICS

//! -----------------------------------------------------
//} Printing Diagnostics if there are some syntax errors in the expression



//{ Scanning the string
//! -----------------------------------------------------

void GetStr ()
{
    //FILE* in = fopen ("input.txt", "rb");
    //assert (in);

    str = (char*) calloc (MAXLEN, sizeof (char));
    assert (str);

    //fscanf (in, "%s", str);
    //len = strlen (str);

    int flag = 1;

    while (flag)
    {
        str [len] = getchar ();

        if (str [len] == ' ') len--;
        if (str [len] == '\n') flag = 0;

        len++;

        if (len >= MAXLEN) Diagnostics (ERR_TOO_LONG, len);
    }

    //assert (!fclose (in));

    return;
}

//! -----------------------------------------------------
//} Scanning the string



//{ Destroying the string
//! -----------------------------------------------------

void DestructStr (struct Lexeme_t* lex)
{
    assert (str);
    assert (len);
    assert (lex);

    free (lex);
    lex = NULL;

    free (str);
    str = NULL;

    return;
}

//! -----------------------------------------------------
//} Destroying the string



//! WARNING! This function includes #define!-------------
//{ Lexeme analysis
//! -----------------------------------------------------

#define ADD_LEXEME(lex_type) { (lex + cnt_lex)->type = lex_type; cnt_lex++; flag = 0; }

Lexeme_t* LexAnalysis ()
{
    assert (str);

    struct Lexeme_t* lex = (struct Lexeme_t*) calloc (MAXLEN, sizeof (struct Lexeme_t));
    assert (lex);

    lex->type = LEX_BEGIN;
    int i = 0, number = 0, cnt_lex = 1, flag = 1;

    while (i < len)
    {
        if ('0' <= str [i] && str [i] <= '9')
        {
            while ('0' <= str [i] && str [i] <= '9')
            {
                number = number * 10 + str [i] - '0';
                i++;
            }

            (lex + cnt_lex)->number = number;
            ADD_LEXEME(LEX_NUMBER)
            number = 0;
            i--;
        }

        if (str [i] == '+' || str [i] == '-' || str [i] == '*' || str [i] == '/')
        {
            (lex + cnt_lex)->str = str + i;
            ADD_LEXEME(LEX_OPERATOR)
        }

        if (str [i] == 'x')
        {
            (lex + cnt_lex)->str = str + i;
            ADD_LEXEME(LEX_VARIABLE)
        }

        if ((str [i] == '^' || 'a' <= str [i] && str [i] <= 'z') && str [i] != 'x')
        {
            if (str [i] == '^')                                             (lex + cnt_lex)->number = FUNC_POW;
            if (str [i] == 's' && str [i + 1] == 'i' && str [i + 2] == 'n') (lex + cnt_lex)->number = FUNC_SIN;
            if (str [i] == 'c' && str [i + 1] == 'o' && str [i + 2] == 's') (lex + cnt_lex)->number = FUNC_COS;

            if (str [i] != '^') i += 2;
            ADD_LEXEME(LEX_FUNCTION)
        }

        if (str [i] == '(' || str [i] == ')')
        {
            (lex + cnt_lex)->str = str + i;
            ADD_LEXEME(LEX_BRACKET)
        }

        if (flag == 1 && str [i] != '\0' && str [i] != '\r' && str [i] != '\n') Diagnostics (ERR_SYNTAX_ERROR, i);

        i++;
        flag = 1;
    }

    ADD_LEXEME(LEX_END)
    //printf ("cnt_lex = %d\n", cnt_lex);
    len = cnt_lex;

    return lex;
}

#undef ADD_LEXEME

//! -----------------------------------------------------
//} Lexeme analysis



//{ LexDump
//! -----------------------------------------------------

void LexDump (struct Lexeme_t* lex)
{
    assert (lex);

    int lex_size = 0;

    while ((lex + lex_size)->type != LEX_END) lex_size++;

    for (int i = 0; i < lex_size; i++)
    {
        switch ((lex + i)->type)
        {
            case LEX_BEGIN:                                                      break;
            case LEX_NUMBER:   printf ("NUMBER   %d\n",      (lex + i)->number); break;
            case LEX_OPERATOR: printf ("OPERATOR %c\n",     *(lex + i)->str);    break;
            case LEX_VARIABLE: printf ("VARIABLE %c\n",     *(lex + i)->str);    break;
            case LEX_BRACKET:  printf ("BRACKET  %c\n",     *(lex + i)->str);    break;
            case LEX_FUNCTION:
                switch ((lex + i)->number)
                {
                    case FUNC_SIN: printf ("FUNCTION sin\n"); break;
                    case FUNC_COS: printf ("FUNCTION cos\n"); break;
                    case FUNC_POW: printf ("FUNCTION ^\n");   break;

                    default: printf ("ERROR. Unknown function in 'LexDump'!\n");
                }
            break;

            default: printf ("ERROR. Unknown lexeme in function 'LexDump'!\n");
        }
    }

    printf ("\n");

    return;
}

//! -----------------------------------------------------
//} LexDump



//{ Printing diagnostics if there are some mistakes
//! -----------------------------------------------------

void Diagnostics (int nERR, int position)
{
    assert (str);
    assert (0 <= position < len);
    assert (0 < nERR < ERR_MAX);

    switch (nERR)
    {
        case ERR_SYNTAX_ERROR:
            printf ("ERROR. Incorrect input. Syntax error on position %d.\n", position);
            break;

        case ERR_TOO_LONG:
            printf ("ERROR. Incorrect input. Too long expression (the length must be less 1000 symbols).\n");
            break;

        case ERR_TOO_FEW:
            printf ("ERROR. Incorrect input. Void expression.\n");
            break;

        default:
            printf ("Unknown error. The function 'Diagnostics' does not know about this error.\n");
    }

    return;
}

//! -----------------------------------------------------
//} Printing diagnostics if there are some mistakes
