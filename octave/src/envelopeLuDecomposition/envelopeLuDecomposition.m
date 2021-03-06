%	MIT License
%
%	Copyright (c) 2021 Guilherme Tadashi Maeoka
%	https://github.com/guimspace/envelope-matrix
%
%	Permission is hereby granted, free of charge, to any person obtaining a copy
%	of this software and associated documentation files (the "Software"), to deal
%	in the Software without restriction, including without limitation the rights
%	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
%	copies of the Software, and to permit persons to whom the Software is
%	furnished to do so, subject to the following conditions:
%
%	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
%	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
%	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
%	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
%	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
%	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
%	SOFTWARE.

%%
 % Decompose a matrix A in LU.
 %
 % @param   {Cell array}    enveTriL   The envelope by line of A.
 % @param   {Cell array}    enveTriU   The envelope by column of A.
 % @return  {Cell array}    enveTriL   The envelope by line of L.
 % @return  {Cell array}    enveTriU   The envelope by column of U.
 %%
function [enveTriL, enveTriU] = envelopeLuDecomposition (enveTriL, enveTriU)
    if (enveTriU{1}(1) == 0)
        error('Factorization impossible');
        return
    end

    n = size(enveTriU{1})(2);
    enveTriL{1} = ones(1, n);

    u_ii = enveTriU{1}(1);
    for j = 2:n
        pos = enveTriL{3}(j);
        if (pos == enveTriL{3}(j + 1) || enveTriL{4}(j) ~= 1)
            continue
        end

        enveTriL{2}(pos) = enveTriL{2}(pos) / u_ii;
    end

    for i = 2:(n - 1)
        summ = sumLkiUkj(enveTriL, i, enveTriU, i);
        u_ii = enveTriU{1}(i) - summ;

        if (u_ii == 0)
            error('Factorization impossible');
            return
        end

        enveTriU{1}(i) = u_ii;

        for j = (i + 1):n
            l = enveTriU{4}(j);
            pos = enveTriU{3}(j) + i - l;
            if (l <= i && pos < enveTriU{3}(j + 1))
                summ = sumLkiUkj(enveTriL, i, enveTriU, j);
                enveTriU{2}(pos) = enveTriU{2}(pos) - summ;
            end

            l = enveTriL{4}(j);
            pos = enveTriL{3}(j) + i - l;
            if (l <= i && pos < enveTriL{3}(j + 1))
                summ = sumLkiUkj(enveTriU, i, enveTriL, j);
                enveTriL{2}(pos) = (enveTriL{2}(pos) - summ) / u_ii;
            end
        end
    end

    summ = sumLkiUkj(enveTriL, n, enveTriU, n);
    enveTriU{1}(n) = enveTriU{1}(n) - summ;

    if (enveTriU{1}(n) == 0)
        warning('A = LU but A is singular');
    end
end
