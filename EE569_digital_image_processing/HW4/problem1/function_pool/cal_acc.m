function acc = cal_acc(matrix ,matrix2)
[m,~] = size(matrix);

sum1 =sum(matrix == matrix2);

acc = sum1/m;
end


