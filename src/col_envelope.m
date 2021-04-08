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

function [diagg, env, env_col, env_lin] = col_envelope (A)
    diagg = diag(A);
    env = [];
    env_lin = [];
    env_col = [1];

    n = size(A)(2);

    for j = 2:1:n
        i = 1;
        while (i < j && A(i, j) == 0)
            i = i + 1;
        end

        s = 1 + size(env)(2);
        env_col = [env_col s];

        if (i == j)
            continue
        end

        next = A(i:(j-1), j);
        next = transpose(next);
        env = [env next];

        env_lin = [env_lin i:(j-1)];
    end

    env = [env 0];

    env_lin = [env_lin 0];

    s = size(env)(2);
    env_col = [env_col s];
end
