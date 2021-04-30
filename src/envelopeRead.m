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
 % Returns the element a_ij from A.
 %
 % @param   {Scalar}        indL        The index of the line.
 % @param   {Scalar}        indC        The index of the column.
 % @param   {Cell array}    envelope    The envelope of the matrix.
 % @return  {Scalar}        a           The matrix element a_ij.
 %%
function a = envelopeRead (indL, indC, envelope)
    diagg = envelope{1};
    enve = envelope{2};
    enveCol = envelope{3};
    enveLin = envelope{4};

    if (indL == indC)
        a = diagg(indL);
        return;
    elseif (enveCol(indC) == enveCol(indC + 1))
        a = 0;
        return;
    end

    pos = enveCol(indC);
    i = enveLin(pos);

    if (i > indL)
        a = 0;
        return;
    end

    pos = pos + (indL - i);

    a = enve(pos);
end
