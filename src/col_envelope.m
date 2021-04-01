function [diag env env_col env_lin] = col_envelope (A)
    diag = diag(A);
    env = [];
    env_lin = [];
    env_col = [1];

    n = size(A)(2);

    for j = 2:1:n
        i = 1;
        while (i < j && A(i, j) == 0)
            i = i + 1;
        endwhile

        s = 1 + size(env)(2);
        env_col = [env_col s];

        if (i == j)
            continue
        endif

        next = A(i:(j-1), j);
        next = transpose(next);
        env = [env next];

        env_lin = [env_lin i:(j-1)];
    end

    env = [env 0];

    env_lin = [env_lin 0];

    s = size(env)(2);
    env_col = [env_col s];
endfunction
