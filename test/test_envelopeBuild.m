addpath('../src');
run('matrices.m');

p = 1;
n = size(matrices)(1);

while (p < n)
    A = matrices{p};
    [diagg, enve, enveCol, enveLin] = envelopeBuild(A)

    p = p + 1;
end
