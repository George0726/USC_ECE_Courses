function img = convolve(input,pattern)
[m,n] = size(input);
input = relf_padding(input);

img = zeros(m,n);

for i =1:m
    for j = 1:n
        temp = 0.0;
        for l = -2:2
            for p = -2:2
                temp = temp + input(i + 2 +l , j + 2 +p)*pattern(3 + l, 3 + p);
            end
        end
        img(i,j) = temp;
    end
end

end
                


