function [output,num]=CCL_img(img)
[m,n]=size(img);
%  Step 1
mask=zeros(m+2,n+2);
label=1;

for i=1:m
    for j=1:n
        if img(i,j)==1
            if mask(i,j)==0 && mask(i,j+1)==0 && mask(i,j+2)==0 && mask(i+1,j)==0  
                mask(i+1,j+1)=label;
                label=label+1;
            else

                sort_suround=sort([mask(i,j),mask(i,j+1),mask(i,j+2),mask(i+1,j)]);
             
                for k =1:4
                    if sort_suround(k) >0
                        break;
                    end
                end
                mask(i+1,j+1)=sort_suround(k);                
            end
        end
     end
end

% Step 2
pre_mask = zeros(size(mask));
while sum(sum(abs(pre_mask-mask )))
    pre_mask=mask;
    
    for i=1:m
        for j=1:n
            if mask(i+1,j+1) >0
                suround=sort([mask(i,j),mask(i,j+1),mask(i,j+2),...
                    mask(i+1,j),mask(i+1,j+2),mask(i+2,j),...
                    mask(i+2,j+1),mask(i+2,j+2)]);
                for k =1:8
                    if suround(k) >0
                        break;
                    end
                end
                
                mini=suround(k);
                if mini < mask(i+1,j+1) && mini>0 
                    mask(i+1,j+1)=mini;
                else
                    mask(i+1,j+1)=mask(i+1,j+1);
                end
            end
        end
    end
end

output=mask(2:m+1,2:n+1);
% update output mask and shrink the number
max_obj = max(max(output));
record = zeros(max_obj+1,1);
[m,n] = size(output);
for i =1:m
    for j =1:n
        if record(output(i,j)+1) == 0
            record(output(i,j)+1)=1;
        end
    end
end

iters = 0;
for i = 1:max(max_obj)+1
    if record(i) ==0
        continue;
    end
    if iters ~= i-1
        for r =1:m
            for j =1:n
                if output(r,j) == i-1
                    output(r,j) =iters;
                end
            end
        end
        iters =iters+1;
    else
        iters = iters+1;
    end
end
    num = max(max(output));

end