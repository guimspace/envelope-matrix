#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "wrap.h"
#include "solve.h"

void test_utils();
void test_line();
void test_substitution();
void test_decomposition();

int main(int argc, char **argv)
{
        test_utils();
        test_line();
        test_substitution();
        test_decomposition();

	return 0;
}

void test_decomposition()
{
        float *solY, *solX;

        float *A = (float[17]){4, 1, 1, -1, 2, 1, 2, 0, 2, -1, -1, 2, 0, 0, 0, -1, 1};
        float b[4] = {8, 13, 3, 1};
        int n = A[0];

        env triL = init_envelope(n);
        env triU = init_envelope(n);

        A += 1;

        build_envelope(triL, A, true);
        build_envelope(triU, A, false);

        lu_decomposition(triL, triU);

        solY = solve_forward_substitution(triL, b);
        solX = solve_backward_substitution(triU, solY);

        for (int i = 0; i < n; i++)
                printf("%.2f\n", solX[i]);
}

void test_substitution()
{
        float *triU = (float[17]){4, 1, 1, 0, 3, 0, -1, -1, -5, 0, 0, 3, 13, 0, 0, 0, -13};
        float vecB[4] = {8, -9, 26, -26};
        float *solX;
        int n, i;

        n = triU[0];
        env envelope = init_envelope(n);
        triU += 1;

        build_envelope(envelope, triU, false);

        solX = solve_backward_substitution(envelope, vecB);
        for (i = 0; i < n; i++)
                printf("%.2f\n", solX[i]);
        free(solX);
        printf("\n");

        solX = solve_forward_substitution(envelope, vecB);
        for (i = 0; i < 4; i++)
                printf("%.2f\n", solX[i]);
        free(solX);
        printf("\n");

        end_envelope(envelope);
}

void test_line()
{
        float *matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, -12, 22, 23, 0, 0, 0, 0, -23, 33, 0, 0, 0, -14, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, -46, 0, 66};

        env envelope = init_envelope(matrix[0]);
        matrix += 1;

        build_envelope(envelope, matrix, true);
        print_envelope(envelope);
        printf("\n");

        int n = (matrix - 1)[0];

        float *regen = unwrap_envelope(envelope, true);
        regen += 1;

        int i = 0;
        int j = 0;
        while (i < n) {
                if (regen[i * n + j] != matrix[i * n + j]) {
                        printf("%.2f != %.2f\tat ", regen[i * n + j], matrix[i * n + j]);
                        printf("(%d, %d)\n", i, j);
                }

                if (j == i) {
                        i++;
                        j = 0;
                } else {
                        j++;
                }
        }

        end_envelope(envelope);
        printf("\n");
}

void test_utils()
{
        float *matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, 0, 22, 23, 0, 0, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 66};

        env envelope = init_envelope(matrix[0]);
        matrix += 1;

        build_envelope(envelope, matrix, false);
        print_envelope(envelope);
        printf("\n");

        int i = 0;
        int j = 0;
        int n = (matrix - 1)[0];
        while (i < n) {
                if (get_element(envelope, i, j) != matrix[i * n + j]) {
                        printf("%.2f != %.2f\tat ", get_element(envelope, i, j), matrix[i * n + j]);
                        printf("(%d, %d)\n", i, j);
                }

                if (j == i) {
                        i++;
                        j = i;
                } else {
                        j++;
                }
        }
        printf("\n");

        float *regen = unwrap_envelope(envelope, false);
        if ((int)regen[0] != n)
                printf("%d != %d\tMismatch dimension", (int)regen[0], n);
        regen += 1;

        while (i < n) {
                if (regen[i * n + j] != matrix[i * n + j]) {
                        printf("%.2f != %.2f\tat ", regen[i * n + j], matrix[i * n + j]);
                        printf("(%d, %d)\n", i, j);
                }

                if (j == i) {
                        i++;
                        j = i;
                } else {
                        j++;
                }
        }

        end_envelope(envelope);
        printf("\n");
}
