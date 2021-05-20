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
#include "operation.h"
#include "solve.h"

float *multiply_triangles(env triL, env triU)
{
        int d, i, j, k;
        int p, pL, pU;
        float summ;

        int n = triL->n;
        float *matrix = (float *)calloc(1 + n * n, sizeof(float));
        matrix[0] = n;
        matrix++;

        i = 0;
        while (i < n) {
                for (j = triL->enveLin[i]; j < n; j++) {
                        if (triU->enveLin[j] > i)
                                continue;

                        summ = sum_lki_ukj(triL, i, triU, j);

                        if (j < i && triL->enveLin[i] <= j) {
                                pL = triL->enveCol[i] + j - triL->enveLin[i];
                                summ += triL->enve[pL] * triU->diagg[j];
                        } else if (j == i) {
                                summ += triL->diagg[i] * triU->diagg[i];
                        } else if (triU->enveLin[j] <= i) {
                                pU = triU->enveCol[j] + i - triU->enveLin[j];
                                summ += triL->diagg[i] * triU->enve[pU];
                        }

                        matrix[j] = summ;
                }

                matrix += n;
                i++;
        }

        matrix -= 1 + n * n;
        return matrix;
}
