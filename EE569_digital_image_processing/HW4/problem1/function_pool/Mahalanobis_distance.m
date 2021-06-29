function distance = Mahalanobis_distance(Y,X)
 S = cov(X);
 mu = mean(X,1);
 distance = sqrt((Y-mu)*inv(S)*(Y-mu)');
end
