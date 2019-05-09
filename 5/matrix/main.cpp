#include <iostream>

#include "matrix.h"
#include "profile.h"



int main()
{
    const int matrix_height = 1500;
    const int matrix_width = 1500;

    Matrix matrix1(matrix_height, matrix_width);
    Matrix matrix2(matrix_height, matrix_width);

    {
        LOG_DURATION("Naive multiplication");
        const Matrix res_matrix = matrix1.MultiplyNaive(matrix2);
    }

    {
        LOG_DURATION("Cache-friendly multiplication");
        const Matrix res_matrix = matrix1.MultiplyCacheFriendly(matrix2);
    }

    {
        LOG_DURATION("Cache-friendly and parallel multiplication");
        const Matrix res_matrix = matrix1.MultiplyParallel(matrix2);
    }

    //std::cout << res << std::endl;
    return 0;
}

