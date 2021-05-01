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
 % Solves the linear system Lx = b by forward substitution.
 %
 % @param   {Cell array}    envelope    The envelope of L.
 % @param   {Array}         b           The vector b.
 % @return  {Array}         x           The solution of the system.
 %%
function x = envelopeForwardSubstitution (envelope, b)
    diagg = envelope{1};
    enve = envelope{2};
    enveCol = envelope{3};
    enveLin = envelope{4};

    x = [];

    A_n = max(size(diagg));

    for j = 1:1:A_n
        i = enveCol(j);
        n = enveCol(j + 1);
        while (i < n)
            l = enveLin(i);

            b(j) = b(j) - enve(i) * x(l);

            i = i + 1;
        end

        x(j) = b(j) / diagg(j);
    end

    x = x';
end
