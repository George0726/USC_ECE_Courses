function img = inverse_img(img)
[m,n] = size(img);
for i =1:m
    for j =1:n
        if   img(i,j) > 0 
            img(i,j) = 0;
        else
            img(i,j) = 1;
        end
    end
end

end