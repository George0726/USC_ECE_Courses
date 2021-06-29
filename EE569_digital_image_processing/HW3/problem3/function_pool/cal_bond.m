function img_bond = cal_bond(img)
    [m,n] = size(img);
    img_bond = zeros(m,n);
    
    img_padding = zero_padding(img);
 for i=1:m
    for j=1:n
        if img_padding(i + 1, j + 1) == 0
            continue
        else
            temp = 0;
            if img_padding(i + 1 + 1, j + 1 + 1) == 1
                temp = temp+1;
            end
            if img_padding(i + 1 - 1, j + 1 + 1) == 1
                temp = temp+1;
            end
            if img_padding(i + 1 + 1, j + 1 - 1) == 1
                temp = temp+1;
            end
            if img_padding(i + 1 - 1, j + 1 - 1) == 1
                temp = temp+1;
            end
            if img_padding(i + 1, j + 1 + 1) == 1
                temp = temp+2;
            end
            if img_padding(i + 1, j + 1 - 1) == 1
                temp = temp+2;
            end
            if img_padding(i + 1 + 1, j + 1) == 1
                temp = temp+2;
            end
            if img_padding(i + 1 - 1, j + 1) == 1
                temp = temp+2;
            end
        end
        img_bond(i,j) = temp;
    end
end