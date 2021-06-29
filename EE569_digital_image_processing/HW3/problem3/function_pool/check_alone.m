function output = check_alone(index,img)
temp = 0;
for i=-1:1
    for j = -1:1
        temp = temp+img(index(1)+i,index(2)+j);
    end
end

if temp>1
    output = 0;
else
    output =1;
end
end
    
