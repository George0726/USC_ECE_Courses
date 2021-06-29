% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/28/2021
clc;clear
close all
addpath('function_pool');
addpath('C:\Users\Sunqr\OneDrive - University of Southern California\USC\EE569\EE569-2020Spring-master\EE569-2020Spring-master\HW3\EE569_hw3_7112807212_ZhengWen Source Code\basicOperations')
%%
% assign label: bark =1; brik =2; knit=3;stone=4; 
train_filepath = 'train\';
img_path_list = dir(strcat(train_filepath,'*.raw'));
train_lenght = length(img_path_list);
train_vector = zeros(25,train_lenght);
train_label = zeros(train_lenght,1);

for i = 1:train_lenght
    file_name = img_path_list(i).name;
    file = read_raw(strcat(train_filepath,file_name));
    img = raw_matrix(file, 128, 128);
    
    label = file_name(1:3);
    train_label(i) = assign_label(label);
    
    feature = law_filter(img);
    train_vector(:,i) = energy_average(feature);
end

train_vector = train_vector';
pca_data = pca(train_vector,'NumComponents',3);
feature= bsxfun(@minus,train_vector,mean(train_vector,1));
PCA_train_vector= feature*pca_data;
%%
test_filepath = 'test\';
img_path_list = dir(strcat(test_filepath,'*.raw'));
test_lenght = length(img_path_list);
test_vector = zeros(25,test_lenght);
% train_label = zeros(train_lenght,1);

for i = 1:test_lenght
    file = read_raw(strcat(test_filepath,num2str(i),'.raw'));
    img = raw_matrix(file, 128, 128);
    
    feature = law_filter(img);
    test_vector(:,i) = energy_average(feature);
end

test_vector =test_vector';
% pca_test_coeff = pca(test_vector, 'NumComponents',3);
test_feature= bsxfun(@minus,test_vector,mean(test_vector,1));
PCA_test_vector= test_feature*pca_data;


%%
% random forest
load fisheriris
s = rng(1988,'twister');

B = TreeBagger(50,PCA_train_vector, train_label,'method','classification','OOBPrediction','on');

pre_train_RF =  predict(B,PCA_train_vector);
pre_test_RF = predict(B,PCA_test_vector);
label = [3 1 1 2 4 3 2 4 4 2 1 3]';

% disp(cal_acc(pre_test_RF,label))


%%
% svm
t = templateSVM('KernelFunction','rbf','Standardize',true);
SVM = fitcecoc(PCA_train_vector, train_label,'Learners',t);
pre_test_svm = predict(SVM, PCA_test_vector);

disp(cal_acc(pre_test_svm,label))
