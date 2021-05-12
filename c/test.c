#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "wrap.h"
#include "solve.h"

void test_utils();
void test_substitution();
void test_decomposition();

int main(int argc, char **argv)
{
        test_utils();
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

void test_utils()
{
        float *matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, -12, 22, 23, 0, 0, 0, 0, -23, 33, 0, 0, 0, -14, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, -46, 0, 66};
        int n = (int)matrix[0];
        int n_2 = n * n;
        int i, j;

        env triU = init_envelope(n);
        env triL = init_envelope(n);

        build_envelope(triL, matrix, true);
        print_envelope(triL);
        printf("\n");

        build_envelope(triU, matrix, false);
        print_envelope(triU);
        printf("\n");

        i = 0;
        j = 0;
        matrix++;

        while (i < n) {
                if (get_element(triL, j, i) != matrix[i * n + j]) {
                        printf("l: %.2f != %.2f\tat ", get_element(triL, j, i), matrix[i * n + j]);
                        printf("(%d, %d)\n", i, j);
                }

                if (get_element(triU, j, i) != matrix[j * n + i]) {
                        printf("c: %.2f != %.2f\tat ", get_element(triU, j, i), matrix[j * n + i]);
                        printf("(%d, %d)\n", j, i);
                }

                if (j == i) {
                        j = 0;
                        i++;
                }

                j++;
        }
        printf("\n");

        float *regen = (float*)calloc(1 + n * n, sizeof(float));

        unwrap_envelope(triL, regen, true);
        unwrap_envelope(triU, regen, false);
        regen++;

        i = 0;
        while (i < n_2) {
                if (regen[i] != matrix[i]) {
                        printf("%.2f != %.2f\tat ", regen[i], matrix[i]);
                        printf("(%d, %d)\n", i / n, i % n);
                }
                i++;
        }

        end_envelope(triL);
        end_envelope(triU);
        printf("\n");
}
