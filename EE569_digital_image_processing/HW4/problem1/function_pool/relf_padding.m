function img = relf_padding(input)

[m,n] = size(input);

img =zeros(m+4,n+4);

    for i =1:m+4
        for j = 1:n+4
            row = check_length(i-2,m);
            col = check_length(j-2,n);
            img(i,j) = input(row,col);
        end
    end
end