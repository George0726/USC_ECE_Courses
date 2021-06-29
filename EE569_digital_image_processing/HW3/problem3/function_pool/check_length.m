function len=check_length(l,max)
len = l;
if(l<1)
    len=1;
end
if(l>max)
    len = max;
end
end