function vector = energy_average(feature)
[m,n,p] = size(feature);
vector = zeros(p,1);
for i = 1:p
    vector(i) = sum(sum(feature(:,:,i).^2))./(m*n);
%       vector(i) = sum(sum(abs(feature(:,:,i))))./(m*n);
end
end