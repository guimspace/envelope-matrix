#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../src/utils.h"
#include "../src/wrap.h"
#include "../src/solve.h"
#include "../src/operation.h"

float *matrix, *b, *x_;

void load_matrix(char *file_A, char *file_b, char *file_x);
void evaluate_solution(float x[], int n);
void evaluate_matrices(float *matrix, float *approx);

int main(int argc, char *argv[])
{
        if (argc > 3) {
                load_matrix(argv[1], argv[2], argv[3]);
        } else {
                matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, -12, 22, 23, 0, 0, 0, 0, -23, 33, 0, 0, 0, -14, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, -46, 0, 66};
                b = (float[6]){91, 101, 53, 438, 275, 212};
                x_ = (float[6]){1, 2, 3, 4, 5, 6};
        }

        int i;
        int n = matrix[0];
        int n_2 = n * n;

        env triL = init_envelope(n);
        env triU = init_envelope(n);

        build_envelope(triL, matrix, true);
        build_envelope(triU, matrix, false);

        float *regen = (float*)calloc(1 + n * n, sizeof(float));

        unwrap_envelope(triL, regen, true);
        unwrap_envelope(triU, regen, false);

        evaluate_matrices(matrix, regen);

        lu_decomposition(triL, triU);

        float *product = multiply_triangles(triL, triU);

        evaluate_matrices(matrix, product);

        float *y = solve_forward_substitution(triL, b);
        float *x = solve_backward_substitution(triU, y);

        evaluate_solution(x, n);

        end_envelope(triL);
        end_envelope(triU);
        free(product);
        free(y);
        free(x);

	return 0;
}

void evaluate_matrices(float *matrix, float *approx)
{
        int n = matrix[0];
        int n2 = n * n;

        float p = 0;
        float r = 0;
        float t;

        float mP = 0;
        float mR = 0;

        matrix++;
        approx++;

        int i = 0;
        while (i < n2) {
                t = fabsf(matrix[i] - approx[i]);
                if (r < t)
                        r = t;

                t = fabsf(matrix[i]);
                if (p < t)
                        p = t;

                i++;
                if (i % n == 0) {
                        if (mP < p)
                                mP = p;
                        if (mR < r)
                                mR = r;

                        r = 0;
                        p = 0;
                }
        }

        matrix--;
        approx--;

        printf("%.2f\n", mR / mP);
}

void evaluate_solution(float x[], int n)
{
        float a = 0;
        float b = 0;

        for (int i = 0; i < n; i++) {
                x[i] = fabsf(x_[i] - x[i]);
                if (b < x[i])
                        b = x[i];

                x_[i] = fabsf(x_[i]);
                if (a < x_[i])
                        a = x_[i];
        }

        printf("%.2f\n", b / a);
}

void load_matrix(char *file_A, char *file_b, char *file_x)
{
        int n, n_2, i;
        float t;
        char c;

        FILE *file_object = NULL;

        file_object = fopen(file_b, "r");
        if (file_object == NULL) {
                printf("File could not be opened\n");
                return;
        }

        n = 0;
        while (!feof(file_object)) {
                fscanf(file_object, "%f%c", &t, &c);
                n++;
        }

        n--;
        n_2 = n * n;
        rewind(file_object);

        b = (float*)calloc(n, sizeof(float));
        for (i = 0; i < n; i++)
                fscanf(file_object, "%f%c", &b[i], &c);

        file_object = fopen(file_A, "r");
        if (file_object == NULL) {
                printf("File could not be opened\n");
                return;
        }

        matrix = (float*)calloc(1 + n * n, sizeof(float));
        matrix[0] = n;

        matrix++;
        for (i = 0; i < n_2; i++)
                fscanf(file_object, "%f%c", &matrix[i], &c);
        matrix--;

        file_object = fopen(file_x, "r");
        if (file_object == NULL) {
                printf("File could not be opened\n");
                return;
        }

        x_ = (float*)calloc(n, sizeof(float));
        for (i = 0; i < n; i++)
                fscanf(file_object, "%f%c", &x_[i], &c);
}
