/**
 * MIT License
 *
 * Copyright (c) 2021 Guilherme Tadashi Maeoka
 * https://github.com/guimspace/envelope-matrix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "envelope-tools.h"
#include "envelope-wrap.h"

float *unwrap_envelope(env envelope)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;

        float *matrix = (float*)calloc(1 + n * n, sizeof(float));
        matrix[0] = n;
        matrix += 1;

        int limit, p;
        int i, j;

        p = enveCol[0];
        limit = enveCol[1];

        j = 0;
        while (j < n) {
                if (p == limit) {
                        matrix[j * n + j] = diagg[j];

                        j++;
                        limit = enveCol[j + 1];
                        continue;
                }

                i = enveLin[p];
                matrix[i * n + j] = enve[p];
                p++;
        }

        return matrix - 1;
}

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
