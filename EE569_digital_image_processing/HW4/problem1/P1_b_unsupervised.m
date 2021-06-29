% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/28/2021
clc;clear
close all
addpath('function_pool');
%%
test_filepath = 'test\';
img_path_list = dir(strcat(test_filepath,'*.raw'));
test_lenght = length(img_path_list);
test_vector = zeros(25,test_lenght);
% train_label = zeros(train_lenght,1);

for i = 1:test_lenght
    file = read_raw(strcat(test_filepath,num2str(i),'.raw'));
    img = raw_matrix(file, 128, 128);
    feature = law_filter(uint8(img));
    test_vector(:,i) = energy_average(feature);
end

test_vector =test_vector';
pca_test_coeff = pca(test_vector, 'NumComponents',3);
test_feature= bsxfun(@minus,test_vector,mean(test_vector,1));
PCA_test_vector= test_feature*pca_test_coeff;

%%

idx_25 = kmeans(test_vector,4);
idx_3 = kmeans(PCA_test_vector,4);
label = [3 1 1 2 4 3 2 4 4 2 1 3]';
disp(idx_25');
disp(idx_3');




