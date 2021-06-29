fid = fopen("Toy_b.raw",'r');
img4_temp = fread(fid,inf);
fclose(fid);
Y=400;X=560; p= Y*X;
img4 = zeros(Y,X);

img40 = zeros(Y,X);
img40(1:p) = img4_temp(1:p);
img4 = img40';
figure
imshow(uint8(img4))
 binranges=0:256;
[bincounts] = histc(img4_temp,binranges);
figure
cumulative = [];
count = 0;
for i = 0:256
    count = count +bincounts(i+1);
    cumulative = [cumulative;count];
end
bar(binranges,cumulative,'histc')
xlabel("pixel values")
ylabel("Frequency")
xlim([-5 260])
% ylim([0 1000])

% histogram(img4_temp,'cdf');  % plot the cumulative histogram