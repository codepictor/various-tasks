#include <stdio.h>
#include <assert.h>


const char* s1  = "Aaa";
const char* s2  = "Bbb";
const char* s3  = "Ccc";
const char* s4  = "ddd";
const char* s5  = "eee";
const char* s6  = "fff";
const char* s7  = "ggg";
const char* s8  = "hhh";
const char* s9  = "iii";
const char* s10 = "jjj";


FILE* texout = NULL;

enum Out_t
{
    OUT_TEXT,
    OUT_FORMULA,
    OUT_RESULT,
    OUT_ERROR
};

void TexPrepare ();
void TexEnd ();

void TexPrepare ()
{
    //setlocale(LC_ALL, "Russian");

    texout = fopen ("output.tex", "w");
    assert (texout);

    fprintf (texout, "\\documentclass{article}\n");
    fprintf (texout, "\\usepackage{amsmath}\n");
    fprintf (texout, "\\usepackage{amssymb,latexsym}\n");
    fprintf (texout, "\\usepackage[T2A]{fontenc}\n");
    fprintf (texout, "\\usepackage[utf8]{inputenc}\n");
    fprintf (texout, "\\usepackage[english, russian]{babel}\n");
    fprintf (texout, "\\begin{document}\n");
    fprintf (texout, "\\title{Diff}\n");
    fprintf (texout, "\\author{Mikhalev~A.\\,D.\\\\Kaliningrad\\\\grozzmaster@gmail.com}\n");
    fprintf (texout, "\\date{\\today}\n");
    //fprintf (out, "\\today\n");
	fprintf (texout, "\\maketitle\n");
	fprintf (texout, "\\newpage\n");
	fprintf (texout, "��-��-��\n");

    return;
}

void TexEnd ()
{
    assert (texout);

    fprintf (texout, "\n\\end{document}\n");

    assert (!fclose (texout));
    texout = NULL;

    return;
}



#define TEXT(i) { fprintf (texout, "%s ", s##i); }

void PrintText (int mode)
{
    assert (texout);
    assert (0 <= mode && mode < OUT_ERROR);

    int i = rand () % 10 + 1;

    switch (mode)
    {
        case OUT_TEXT:    fprintf (texout, "%s " , s1);  break;
        case OUT_FORMULA: fprintf (texout, "%s\n", s2);  break;
        case OUT_RESULT:  fprintf (texout, "Answer:\n"); break;
    }

    printf ("i = %d\n", i);

    //TEXT(i)

    return;
}


#undef TEXT
















