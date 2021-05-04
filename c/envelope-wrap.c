#include "envelope-tools.h"
#include "envelope-wrap.h"

void build_envelope(env envelope, float *matrix)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = (matrix - 1)[0];

        int s, p;
        int i, j, k;

        s = 0;
        p = 0;

        j = 0;
        while (j < n) {
                diagg[j] = matrix[j * n + j];

                i = 0;
                while (i < j && matrix[i * n + j] == 0)
                        i++;

                enveCol[j] = p;

                if (i == j) {
                        j++;
                        continue;
                }

                for (k = i; k < j; k++) {
                        enve[p] = matrix[k * n + j];
                        s++;
                        enveLin[p] = k;
                        p++;
                }

                j++;
        }

        envelope->s = s;

        enve[p] = -1;
        enveLin[p] = -1;

        enve = realloc(enve, (1 + s) * sizeof(float));
        enveLin = realloc(enveLin, (1 + s) * sizeof(int));

        enveCol[n] = p;
}
