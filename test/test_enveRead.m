addpath('../src');
run('matrices.m');

p = 1;
n = size(matrices)(1);

while (p < n)
    A = matrices{p};
    dim = size(A);

    [diagg, enve, enveCol, enveLin] = envelopeBuild(A);
    envelope = {diagg, enve, enveCol, enveLin};

    for j = 1:1:dim(2)
        for i = 1:1:j
            if (A(i, j) ~= enveRead(i, j, envelope, false))
                warning('Mismatching value at (%d, %d).', i, j);
                return;
            end
        end
    end

    fprintf('Good run: %d.\n', p);

    p = p + 1;
end
