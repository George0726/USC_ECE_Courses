function output1 = cal_surronding(img)
    [m,n] = size(img);
    img_pad = zero_padding(img);
    output = strings(m,n);
    for i = 1:m
        for j =1:n
            if(img(i,j)==0)
                output(i,j) = '00000000';
            else
                temp = '';
                for x= -1:1
                    for y =-1:1
                        if (x==0)&&(y==0)
                            continue;
                        end
                        temp = [temp, dec2bin(img_pad(i+1+x,j+1+y))];
                    end
                end
                output(i,j) = temp;
            end
        end
    end
    output1 = zeros(m,n);
    
    for i = 1:m
        for j =1:n
            output1(i,j) = bin2dec(output(i,j)); 
        end
    end
end