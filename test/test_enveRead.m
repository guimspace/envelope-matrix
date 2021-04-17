addpath('../src');

listA = {
    eye(6);
    [
        11  12  0   14  0   0;
        0   22  23  0   0   0;
        0   0   33  0   0   0;
        0   0   0   44  0   46;
        0   0   0   0   55  0;
        0   0   0   0   0   66
    ];
    [
        11  12  0   0   0   0;
        0   22  23  0   0   0;
        0   0   33  0   0   0;
        0   0   0   44  0   46;
        0   0   0   0   55  0;
        0   0   0   0   0   66
    ];
    [
        11  12  0   0   0   0;
        0   22  23  0   0   0;
        0   0   33  34  0   0;
        0   0   0   44  45  0;
        0   0   0   0   55  56;
        0   0   0   0   0   66
    ];
    [
        11  12  13  14  15  16;
        0   22  0   0   0   0;
        0   0   33  0   0   0;
        0   0   0   44  0   0;
        0   0   0   0   55  0;
        0   0   0   0   0   66
    ]
};


p = 1;
n = size(listA)(1);

while (p < n)
    A = listA{p};
    dim = size(A);

    [diagg, enve, enveCol, enveLin] = col_envelope(A);
    envelope = {diagg, enve, enveCol, enveLin};

    for j = 1:1:dim(2)
        for i = 1:1:j
            if (A(i, j) ~= enveRead(i, j, envelope))
                warning('Mismatching value at (%d, %d).', i, j);
                return;
            end
        end
    end

    fprintf('Good run: %d.\n', p);

    p = p + 1;
end
