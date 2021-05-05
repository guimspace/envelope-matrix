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

#include "tools.h"

float *solve_forward_substitution(env envelope, float vecB[])
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;
        float *solX = (float *)calloc(n, sizeof(float));

        int limit, l, p, j;

        j = 0;
        while (j < n) {
                p = enveCol[j];
                limit = enveCol[j + 1];
                while (p < limit) {
                        l = enveLin[p];
                        vecB[j] -= enve[p] * solX[j];
                        p++;
                }

                solX[j] = vecB[j] / diagg[j];

                j++;
        }

        return solX;
}

float *solve_back_substitution(env envelope, float vecB[])
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        int n = envelope->n;
        float *solX = (float *)calloc(n, sizeof(float));

        int limit, l, p, j;

        j = n - 1;
        while (j > -1) {
                solX[j] = vecB[j] / diagg[j];

                p = enveCol[j];
                limit = enveCol[j + 1];
                while (p < limit) {
                        l = enveLin[p];
                        vecB[l] -= enve[p] * solX[j];
                        p++;
                }

                j--;
        }

        return solX;
}
