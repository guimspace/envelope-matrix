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

function [diagg, env, env_lin, env_col] = lin_envelope (A)
    diagg = diag(A);
    env = [];
    env_col = [];
    env_lin = [1];

    n = size(A)(1);

    for i = 2:1:n
        j = 1;
        % search by column first non-zero
        while (j < i && A(i, j) == 0)
            j = j + 1;
        end

        s = 1 + size(env)(2);
        env_lin = [env_lin s];

        % if line is zero up to diagonal, skip to next
        if (j == i)
            continue
        end

        % get envelope elements
        next = A(i, j:(i - 1));
        env = [env next];

        % column number of elements
        env_col = [env_col j:(i - 1)];
    end

    env = [env 0];
    env_col = [env_col 0];

    s = size(env)(2);
    env_lin = [env_lin s];
end
