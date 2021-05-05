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
 % Generates the envelope (by column) of a square matrix.
 % The envelope by line can be generated from the transposed matrix.
 %
 % @param   {Matrix}        A          The matrix.
 % @return  {Cell array}    envelope   The envelope in a cell array.
 %%
function envelope = envelopeBuild (A)
    diagg = diag(A)';
    enve = [];
    enveCol = [1];
    enveLin = [];

    n = size(A)(2);

    for j = 2:1:n
        i = 1;
        % search by row first non-zero
        while (i < j && A(i, j) == 0)
            i = i + 1;
        end

        s = 1 + size(enve)(2);
        enveCol = [enveCol s];

        % if column is zero up to diagonal, skip to next
        if (i == j)
            continue
        end

        % get envelope elements
        next = A(i:(j-1), j);
        next = transpose(next);
        enve = [enve next];

        % line number of elements
        enveLin = [enveLin i:(j-1)];
    end

    enve = [enve 0];
    enveLin = [enveLin 0];

    s = size(enve)(2);
    enveCol = [enveCol s];

    envelope = {diagg, enve, enveCol, enveLin};
end
