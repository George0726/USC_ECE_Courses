function trans = TRANSPOSE(mat)

[m,n] = size(mat);
trans = zeros(n,m);
for i=1:m
    for j=1:n
        trans(j,i) = mat(i,j);
    end
end
end