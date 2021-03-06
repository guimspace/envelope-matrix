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

void unwrap_symmetric_envelope(env envelope, float *matrix)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;
        matrix[0] = n;
        matrix++;

        int top, l, p;

        l = enveLin[0];
        p = 0;
        top = enveCol[2];

        matrix[0] = diagg[0];

        int j = 1;
        while (j < n) {
                if (p < top) {
                        matrix[l * n + j] = enve[p];
                        matrix[j * n + l] = enve[p];

                        l++;
                        p++;
                } else {
                        matrix[j * n + j] = diagg[j];

                        j++;
                        l = enveLin[j];
                        top = enveCol[j + 1];
                }
        }

        matrix--;
}

void unwrap_envelope(env envelope, float *matrix, bool isLine)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;
        matrix[0] = n;
        matrix++;

        int limit, p, v;
        int i, j;
        int o = isLine ? 1 : n;

        p = 0;
        limit = enveCol[2];

        matrix[0] = diagg[0];

        j = 1;
        v = isLine ? j * n + enveLin[p] : enveLin[p] * n + j;
        while (j < n) {
                if (p < limit) {
                        matrix[v] = enve[p];
                        v += o;
                        p++;
                } else {
                        matrix[j * n + j] = diagg[j];

                        j++;
                        v = isLine ? j * n + enveLin[j] : enveLin[j] * n + j;
                        limit = enveCol[j + 1];
                }
        }

        matrix--;
}

void build_envelope(env envelope, float *matrix, bool isLine)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = matrix[0];
        matrix++;

        int p, v;
        int i, j;
        int d = isLine ? n : 1;
        int o = isLine ? 1 : n;

        p = 0;

        diagg[0] = matrix[0];
        enveCol[0] = 0;

        j = 1;
        while (j < n) {
                diagg[j] = matrix[j * n + j];
                enveCol[j] = p;

                v = d * j;

                i = 0;
                while (i < j && matrix[v] == 0) {
                        i++;
                        v += o;
                }

                enveLin[j] = i;

                while (i < j) {
                        enve[p] = matrix[v];

                        i++;
                        v += o;
                        p++;
                }

                j++;
        }

        enve[p] = 0;

        enve = realloc(enve, (1 + p) * sizeof(float));

        enveCol[n] = p;
        matrix--;
}
