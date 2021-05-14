#include <stdio.h>
#include <stdlib.h>

#include "../src/utils.h"
#include "../src/wrap.h"
#include "../src/solve.h"

float *matrix, *b;

void load_matrix(char *file_A, char *file_b);

int main(int argc, char *argv[])
{
        if (argc > 2) {
                load_matrix(argv[1], argv[2]);
        } else {
                matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, -12, 22, 23, 0, 0, 0, 0, -23, 33, 0, 0, 0, -14, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, -46, 0, 66};
                b = (float[6]){91, 101, 53, 438, 275, 212};
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

        regen++;
        matrix++;

        for (i = 0; i < n_2; i++) {
                if (matrix[i] != regen[i])
                        printf("%.2f != %.2f\n", matrix[i], regen[i]);
        }

        matrix--;

        lu_decomposition(triL, triU);

        float *y = solve_forward_substitution(triL, b);
        float *x = solve_backward_substitution(triU, y);

        for (i = 0; i < n; i++)
                printf("%.2f\n", x[i]);

        end_envelope(triL);
        end_envelope(triU);
        free(y);
        free(x);

	return 0;
}

void load_matrix(char *file_A, char *file_b)
{
        int n = 0;
        scanf("%d", &n);
        int n_2 = n * n;

        int i;
        char c;

        FILE *file_object = NULL;

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

        file_object = fopen(file_b, "r");
        if (file_object == NULL) {
                printf("File could not be opened\n");
                return;
        }

        b = (float*)calloc(n, sizeof(float));
        for (i = 0; i < n; i++)
                fscanf(file_object, "%f%c", &b[i], &c);
}
