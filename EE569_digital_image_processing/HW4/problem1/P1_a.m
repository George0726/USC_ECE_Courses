% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/28/2021
clc;clear
close all
addpath('function_pool');
%%

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

%% intra-inter variance
[~,m] = size(train_vector);
average_feature = sum(train_vector,2)./m;
average_feature_class = zeros(25,4);
for i = 1:25
    for j = 1:36
        average_feature_class(i,train_label(j)) = average_feature_class(i,train_label(j))+1/9*train_vector(i,j);
    end
end

intra_sum = zeros(25,1);
for i = 1:25
    for j = 1:36
        intra_sum(i) = intra_sum(i)+(train_vector(i,j)-average_feature_class(i,train_label(j)))^2;
    end
end

inter_sum = zeros(25,1);
for i = 1:25
    for j = 1:36
        inter_sum(i) = inter_sum(i)+(average_feature(i)-average_feature_class(i,train_label(j)))^2;
    end
end

dis_power = intra_sum./inter_sum;


train_vector = train_vector';
pca_data = pca(train_vector,'NumComponents',3);
feature= bsxfun(@minus,train_vector,mean(train_vector,1));
train_feature_after_PCA= feature*pca_data;
%%
figure;
for i =1:4
    scatter3(train_feature_after_PCA(9*i-8:i*9,1),train_feature_after_PCA(9*i-8:i*9,2),train_feature_after_PCA(9*i-8:i*9,3))
    hold on
end
legend('blanket','brick','grass','rice')

%%
test_filepath = 'test\';
img_path_list = dir(strcat(test_filepath,'*.raw'));
test_lenght = length(img_path_list);
test_vector = zeros(25,test_lenght);
% train_label = zeros(train_lenght,1);

for i = 1:test_lenght
%     file_name = img_path_list(i).name;
%     img = imread(strcat(train_filepath,num2str(i),'.png'));

    file = read_raw(strcat(test_filepath,num2str(i),'.raw'));
    img = raw_matrix(file, 128, 128);
    feature = law_filter(uint8(img));
    test_vector(:,i) = energy_average(feature);
end

test_vector =test_vector';
% pca_test = pca(test_vector,'NumComponents',3);
test_feature= bsxfun(@minus,test_vector,mean(test_vector,1));
test_feature_after_PCA= test_feature*pca_data;
%%
distance_matrix = zeros(test_lenght,4);
predict_label = zeros(test_lenght,1);
for i = 1:test_lenght
    for j = 1:4
        distance_matrix(i,j) = Mahalanobis_distance(test_feature_after_PCA(i,:),train_feature_after_PCA(9*j-8:j*9,:));
    end
    [~,index] = min(distance_matrix(i,:));
    predict_label(i) = index;
end
disp(predict_label)

label = [3 1 1 2 4 3 2 4 4 2 1 3]';
disp(cal_acc(predict_label,label))
