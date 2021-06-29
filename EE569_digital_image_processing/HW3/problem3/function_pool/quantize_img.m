function output = quantize_img(img,threshold)

    [m,n] = size(img);
    output = zeros(m,n);
    
    for i=1:m
        for j = 1:n
            if(img(i,j)>threshold)
                output(i,j) = 1;
            else
               output(i,j) = 0;
            end
        end
    end
end