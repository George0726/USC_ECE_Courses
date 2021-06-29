fid = fopen("Fruits_median.raw",'r');
img4_temp = fread(fid,inf);
fclose(fid);
X=500;Y=400; p= Y*X;
img4 = zeros(Y,X,3);
img4_r = zeros(X,Y);img4_g = zeros(X,Y);img4_b = zeros(X,Y);
img4_r(1:p) = img4_temp(1:3:3*p);
img4_g(1:p) = img4_temp(2:3:3*p);
img4_b(1:p) = img4_temp(3:3:3*p);
img4(:,:,1) = img4_r';
img4(:,:,2) = img4_g';
img4(:,:,3) = img4_b';
figure
imshow(uint8(img4))
%%
fid = fopen("Fruits_noisy.raw",'r');
img5_temp = fread(fid,inf);
fclose(fid);
X=500;Y=400; p= Y*X;
img5 = zeros(Y,X,3);
img5_r = zeros(X,Y);img5_g = zeros(X,Y);img5_b = zeros(X,Y);
img5_r(1:p) = img5_temp(1:3:3*p);
img5_g(1:p) = img5_temp(2:3:3*p);
img5_b(1:p) = img5_temp(3:3:3*p);
img5(:,:,1) = img5_r';
img5(:,:,2) = img5_g';
img5(:,:,3) = img5_b';
% figure
% imshow(uint8(img5))
%%

img5 = zeros(Y,X);
img50 = zeros(Y,X);
img50(1:p) = img5_temp(1:p);
figure
binranges=0:256;
[bincounts] = histc(img5_temp(3:3:3*p),binranges);
bar(binranges,bincounts,'histc')
xlabel("pixel difference")
ylabel("Frequency")
% 
% img4 = img40';
% figure
% imshow(uint8(img4))
% binranges=0:256;
% [bincounts] = histc(img4_temp,binranges);
% figure
% cumulative = [];
% count = 0;
% for i = 0:256
%     count = count +bincounts(i+1);
%     cumulative = [cumulative;count];
% end
% bar(binranges,cumulative,'histc')
% xlabel("pixel values")
% ylabel("Frequency")
% xlim([-5 260])
% ylim([0 1000])

% histogram(img4_temp,'cdf');  % plot the cumulative histogram