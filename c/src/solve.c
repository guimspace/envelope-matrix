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
#include "solve.h"

float sum_lki_ukj(env triL, int indI, env triU, int indJ)
{
        float summ = 0;

        int pL = triL->enveCol[indI];
        int nL = triL->enveCol[indI + 1];

        int pU = triU->enveCol[indJ];
        int nU = triU->enveCol[indJ + 1];

        if (triL->enveLin[indI] >= triU->enveLin[indJ])
                pU += triL->enveLin[indI] - triU->enveLin[indJ];
        else
                pL += triU->enveLin[indJ] - triL->enveLin[indI];

        while (pL < nL && pU < nU) {
                summ += triL->enve[pL] * triU->enve[pU];

                pL++;
                pU++;
        }

        return summ;
}

void lu_decomposition(env triL, env triU)
{
        if (triU->diagg[0] == 0) {
                printf("Factorization impossible\n");
                return;
        }

        int i, j;
        int l, p;
        float u_ii, summ;

        int n = triL->n;

        for (i = 0; i < n; i++)
                triL->diagg[i] = 1;

        u_ii = triU->diagg[0];

        for (j = 1; j < n; j++) {
                p = triL->enveCol[j];
                if (p == triL->enveCol[j + 1] || triL->enveLin[j] != 0)
                        continue;

                triL->enve[p] /= u_ii;
        }

        int n_1 = n - 1;
        for (i = 1; i < n_1; i++) {
                summ = sum_lki_ukj(triL, i, triU, i);
                u_ii = triU->diagg[i] - summ;

                if (u_ii == 0) {
                        printf("Factorization impossible\n");
                        return;
                }

                triU->diagg[i] = u_ii;

                for (j = i + 1; j < n; j++) {
                        p = triU->enveCol[j];
                        l = triU->enveLin[j];
                        p += i - l;
                        if (l <= i && p < triU->enveCol[j + 1]) {
                                summ = sum_lki_ukj(triL, i, triU, j);
                                triU->enve[p] -= summ;
                        }

                        p = triL->enveCol[j];
                        l = triL->enveLin[j];
                        p += i - l;
                        if (l <= i && p < triL->enveCol[j + 1]) {
                                summ = sum_lki_ukj(triU, i, triL, j);
                                triL->enve[p] = (triL->enve[p] - summ) / u_ii;
                        }
                }
        }

        summ = sum_lki_ukj(triL, n_1, triU, n_1);
        triU->diagg[n_1] -= summ;

        if (triU->diagg[n_1] == 0)
                printf("A = LU but A is singular\n");
}

float *solve_forward_substitution(env triL, float b[])
{
        float *diagg = triL->diagg;
        float *enve = triL->enve;
        int *enveCol = triL->enveCol;
        int *enveLin = triL->enveLin;

        int n = triL->n;
        float *x = (float *)calloc(n, sizeof(float));

        int limit, l, p, j;

        j = 0;
        while (j < n) {
                p = enveCol[j];
                limit = enveCol[j + 1];
                l = enveLin[j];
                while (p < limit) {
                        b[j] -= enve[p] * x[l];
                        p++;
                        l++;
                }

                x[j] = b[j] / diagg[j];

                j++;
        }

        return x;
}

float *solve_backward_substitution(env triU, float b[])
{
        float *diagg = triU->diagg;
        float *enve = triU->enve;
        int *enveCol = triU->enveCol;
        int *enveLin = triU->enveLin;

        int n = triU->n;
        float *x = (float *)calloc(n, sizeof(float));

        int limit, l, p, j;

        j = n - 1;
        while (j > -1) {
                x[j] = b[j] / diagg[j];

                p = enveCol[j];
                limit = enveCol[j + 1];
                l = enveLin[j];
                while (p < limit) {
                        b[l] -= enve[p] * x[j];
                        p++;
                        l++;
                }

                j--;
        }

        return x;
}
