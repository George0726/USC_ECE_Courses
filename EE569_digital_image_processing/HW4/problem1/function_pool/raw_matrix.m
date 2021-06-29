function output = raw_matrix(input, m, n)

output = zeros(m,n);
k=1;
for j=1:n
    for i=1:m
        output(i,j) = input(k);
        k = k+1;
    end
end
output = TRANSPOSE(output);
end

