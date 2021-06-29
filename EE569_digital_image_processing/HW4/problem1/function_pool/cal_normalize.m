function normalized = cal_normalize(img)
[m,n] = size(img);
normalized = double(img) - (sum(sum(img))) / (m*n);
end