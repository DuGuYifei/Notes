
% Program tworzy tablice zawierajaca w poszczegolnych wierszach przykladowe twarze 
% do zadan rozpoznawania twarzy
% This script creates a big picture contained an array of example face images 

clear

filenames = {'x24x24.txt','y24x24.txt','z24x24.txt'}
number_of_files = length(filenames)
number_of_classes_in_row = 8;   
create_image_files = 0;


%X = ones(24,24);

colormap gray;
patterns = [];
classes = [];
number_of_patterns = 0;

number_of_classes = 48;
number_of_rows = number_of_classes/number_of_classes_in_row;

for pl=1:number_of_files
    f = fopen(filenames{pl},'r');

    line = fgets(f);   
    number_of_patterns_in_file = str2num(line)
    number_of_patterns = number_of_patterns + number_of_patterns_in_file;
    line = fgets(f);   
    number_of_pixels = str2num(line)
    
    line = fgets(f);
    while line ~= -1
        A = str2num(line);
        patterns = [patterns; A(1:number_of_pixels)];
        class = A(number_of_pixels+3);
        classes = [classes class];
      
        line = fgets(f);
    end
    fclose(f);
end

for kl=1:48
    class_indexes{kl} = find(classes == kl-1);
end


for kl=1:48
    numbers_of_patterns_per_class(kl) = length(class_indexes{kl});
end

min_num_pat_per_class = min(numbers_of_patterns_per_class);
size_of_pattern = round(sqrt(number_of_pixels));

% mean pattern:
big_picture = [];
for w=1:number_of_rows
    row = [];
    for k=1:number_of_classes_in_row
        nr_classes = (w-1)*number_of_classes_in_row+k;
        for i=1:size_of_pattern
            for j=1:size_of_pattern
                average_val = 0;
                for m=1:numbers_of_patterns_per_class(nr_classes)
                    average_val = average_val+patterns(class_indexes{nr_classes}(m),j+(i-1)*size_of_pattern);
                end
                X(i,j) = average_val/numbers_of_patterns_per_class(nr_classes);
            end
        end
        row = [row X];
    end
    big_picture = [big_picture; row];
end
imagesc(big_picture);
title(sprintf('mean images'));
pause
if create_image_files
    eval(sprintf('print -deps -tiff mean_pattern_'));
    eval(sprintf('print -djpeg90 mean_pattern'));
end


for m=1:min_num_pat_per_class
    big_picture = [];
    for w=1:number_of_rows
        row = [];
        for k=1:number_of_classes_in_row
            indeks = class_indexes{(w-1)*number_of_classes_in_row+k}(m);
                    
            for i=1:size_of_pattern
                for j=1:size_of_pattern
                    X(i,j) = patterns(indeks,j+(i-1)*size_of_pattern);
                end
            end
            row = [row X];
        end
        big_picture = [big_picture; row];
    end
    imagesc(big_picture);
    title(sprintf('example images no %d',m));
    pause
    if create_image_files
        eval(sprintf('print -deps -tiff pattern_%d',m));
        eval(sprintf('print -djpeg90 pattern%d',m));
    end
  
end



