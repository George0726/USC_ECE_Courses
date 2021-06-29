function output = blur_feature(input,kernel)
half_kernel = (kernel-1)/2;
window = fspecial('gaussian',kernel, 10);
[m,n,p] = size(input);
output = zeros(m,n,p);
for o = 1:p
    for i =1:m
        for j =1:n
            iter = 0;
            temp = 0;
            for r = -half_kernel:half_kernel
                for s = -half_kernel:half_kernel
                    col = check_length(i+r,m);
                    row = check_length(j+s,n);
                    temp = temp + abs(input(col,row,o))*window(r+half_kernel+1,s+half_kernel+1);
%                     temp = temp + input(col,row,o).^2*window(r+half_kernel+1,s+half_kernel+1);
                    iter =iter +1;
                end
            end
            output(i,j,o) = temp/iter;
        end
    end
end
end
            
