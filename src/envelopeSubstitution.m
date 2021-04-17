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

function x = envelopeSubstitution (envelope, b)
    diagg = envelope{1};
    enve = envelope{2};
    enveCol = envelope{3};
    enveLin = envelope{4};

    x = [];

    A_n = max(size(diagg));

    for j = A_n:-1:1
        x(j) = b(j) / diagg(j);

        i = enveCol(j);
        n = enveCol(j + 1);
        while (i < n)
            l = enveLin(i);

            b(l) = b(l) - enve(i) * x(j);

            i = i + 1;
        end
    end

    x = x';
end
