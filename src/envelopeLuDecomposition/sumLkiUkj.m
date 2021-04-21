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

function summ = sumLkiUkj (enveTriL, indI, enveTriU, indJ)
    summ = 0;

    posL = enveTriL{3}(indI);
    if (posL == enveTriL{3}(indI + 1))
        return
    end

    posU = enveTriU{3}(indJ);
    if (posU == enveTriU{3}(indJ + 1))
        return
    end

    if (enveTriL{4}(posL) >= enveTriU{4}(posU))
        init = enveTriL{4}(posL);
    else
        init = enveTriU{4}(posU);
    end

    i = 0;
    for k = init:(indI - 1)
        summ = summ + enveTriL{2}(posL + i) * enveTriU{2}(posU + i);
        i = i + 1;
    end
end
