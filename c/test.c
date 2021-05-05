#include <stdio.h>
#include <stdlib.h>

#include "envelope-tools.h"
#include "envelope-wrap.h"
#include "envelope-solve.h"

int main(int argc, char **argv)
{
        int n, i, j;

        float *matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, 0, 22, 23, 0, 0, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 66};
        matrix += 1;

        env envelope = init_envelope((matrix - 1)[0]);

        build_envelope(envelope, matrix);

        print_envelope(envelope);
        printf("\n");

        i = 0;
        j = 0;
        n = (matrix - 1)[0];
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

        float *matrix2 = unwrap_envelope(envelope);

        int l = (int)matrix2[0];
        n = l * l;
        for (i = 1; i <= n; ) {
                printf("%.2f\t", matrix2[i]);
                if (i % l == 0)
                        printf("\n");
                i++;
        }

        end_envelope(envelope);
        printf("\n");

        float *triU = (float[17]){4, 1, 1, 0, 3, 0, -1, -1, -5, 0, 0, 3, 13, 0, 0, 0, -13};
        triU += 1;

        envelope = init_envelope((triU - 1)[0]);

        build_envelope(envelope, triU);

        float vecB[4] = {8, -9, 26, -26};
        float *solX;

        solX = solve_back_substitution(envelope, vecB);

        for (i = 0; i < 4; i++)
                printf("%.2f\n", solX[i]);

	return 0;
}
