function output = update_img(img,pattern)
    [m,n] = size(img);
    output = img;
    for i = 1:m
        for j =1:n
            if(pattern(i,j)==1)
                output(i,j) = 0;
            end
        end
    end    
end