function img = zero_padding(input)

[m,n] = size(input);

img =zeros(m+2,n+2);

    for i =2:m+1
        for j = 2:n+1
            img(i,j) = input(i-1,j-1);
        end
    end
end