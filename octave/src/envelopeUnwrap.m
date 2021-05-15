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
 % Unwraps the envelope of a matrix.
 %
 % @param   {Cell array}    envelope    The envelope of the matrix.
 % @return  {Matrix}        A           The matrix.
 %%
function A = envelopeUnwrap (envelope)
    diagg = envelope{1};
    enve = envelope{2};
    enveCol = envelope{3};
    enveLin = envelope{4};

    A_n = size(diagg)(2);
    A = zeros(A_n);

    j = 1;
    l = enveLin(j);
    pos = enveCol(1);
    n = enveCol(2);
    while (j < A_n)
        if (pos ~= n)
            A(l, j) = enve(pos);

            pos = pos + 1;
            l = l + 1;
        else
            A(j, j) = diagg(j);

            j = j + 1;
            l = enveLin(j);
            n = enveCol(j + 1);
        end
    end

    l = enveLin(j);
    while (pos < n)
        A(l, j) = enve(pos);

        pos = pos + 1;
        l = l + 1;
    end
    A(j, j) = diagg(j);
end
