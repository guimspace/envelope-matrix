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

#include "utils.h"
#include "wrap.h"

void unwrap_envelope(env envelope, float *matrix, bool isLine)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;

        matrix[0] = n;
        matrix += 1;

        int limit, p, v;
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

                v = isLine ? j * n + enveLin[p] : enveLin[p] * n + j;
                matrix[v] = enve[p];
                p++;
        }

        matrix -= 1;
}

void build_envelope(env envelope, float *matrix, bool isLine)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = (matrix - 1)[0];

        int p, v;
        int i, j;
        int o = isLine ? 1 : n;

        p = 0;

        j = 0;
        while (j < n) {
                diagg[j] = matrix[j * n + j];
                enveCol[j] = p;

                v = isLine ? j * n : j;

                i = 0;
                while (i < j && matrix[v] == 0) {
                        i++;
                        v += o;
                }

                while (i < j) {
                        enve[p] = matrix[v];
                        enveLin[p] = i;

                        i++;
                        v += o;
                        p++;
                }

                j++;
        }

        enve[p] = -1;
        enveLin[p] = -1;

        enve = realloc(enve, (1 + p) * sizeof(float));
        enveLin = realloc(enveLin, (1 + p) * sizeof(int));

        enveCol[n] = p;
}
