function normalized = cal_normalize(img)
[m, n] = size(img);
normalized = zeros(m,n);
mean_value = 0;
for i=1:m
    for j=1:n
        mean_value = mean_value + img(i,j);
    end
end

mean_value = mean_value / (m * n);

for i=1:m
    for j=1:n
        normalized(i,j) = img(i,j) - mean_value;
    end
end
end
% function normalized = cal_normalize(img)
% [m,n] = size(img);
% normalized = double(img) - (sum(sum(img))) / (m*n);
% end
