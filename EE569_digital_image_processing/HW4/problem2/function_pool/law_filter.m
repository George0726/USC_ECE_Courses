function feature_img = law_filter(img)

% L5 = [-1 4 6 4 1];
% E5 = [-1 -2 0 2 1];
% S5 = [-1 0 2 0 -1];
% W5 = [-1 2 0 -2 1];
% R5 = [1 -4 6 -4 1];
filter_bank = zeros(5,5,25);
filter_half = [1 4 6 4 1;
            -1 -2 0 2 1;
            -1 0 2 0 -1;
            -1 2 0 -2 1;
            1 -4 6 -4 1];
        
for i = 1:5
    for j = 1:5
        filter_bank(:,:,5*i+j-5) = filter_half(i,:)'*filter_half(j,:);
    end
end

[m,n] = size(img);
% img = cal_normalize(img);

feature_img = zeros(m,n,25);

for i = 1:25
    feature_img(:,:,i) = convolve(img,filter_bank(:,:,i));
end

end