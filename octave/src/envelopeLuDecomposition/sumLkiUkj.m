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
 % Sum the product of elements from two matrices.
 %
 % @param   {Cell array}    enveTriL    The envelope by line of A.
 % @param   {Scalar}        indI        The selected line of A.
 % @param   {Cell array}    enveTriU    The envelope by column of A.
 % @param   {Scalar}        indJ        The selected column of A.
 % @return  {Scalar}        summ        The sum of products.
 %%
function summ = sumLkiUkj (enveTriL, indI, enveTriU, indJ)
    posL = enveTriL{3}(indI);
    nL = enveTriL{3}(indI + 1);

    posU = enveTriU{3}(indJ);
    nU = enveTriU{3}(indJ + 1);

    if (enveTriL{4}(indI) >= enveTriU{4}(indJ))
        posU = posU + (enveTriL{4}(indI) - enveTriU{4}(indJ));
    else
        posL = posL + (enveTriU{4}(indJ) - enveTriL{4}(indI));
    end

    d = min(nL - posL, nU - posU);
    v1 = enveTriL{2}(posL:(posL + d));
    v2 = enveTriU{2}(posU:(posU + d));

    summ = dot(v1, v2);
end
