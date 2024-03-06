The description of famous48 dataset

famous48 is a set of example images contained faces of 48 famous persons like sportsmens, politicians, actors or television stars. It was divided into 3 files: x24x24.txt, y24x24.txt, z24x24.txt, each containing 16 personal classes.  

Each file is organized as follows:

<L>
<N>
<example 1>
<example 2>
.
.
<example L>

e.g. first line contains the number of examples L,
second line contains the number of pixels N in each image and the
rest of lines contain example data - each example in separate line

each example line is organized as follows:

<example x> := <image pixel intensities> <attributes>

e.g. first N numbers describe pixel intensities in gray scale and
the rest of numbers describe attributes:

<attributes> := <a1, a2, ... , a8>

a1 - face containing flag: (1-with face, 0-without face),
a2 - image number in current class (person) beginning from 0,
a3 - class (person) number beginning from 0,
a4 - sex (0 - woman, 1 - man)
a5 - race (0- white, 1 - negro, 2 - indian, ...)
a6 - age (0 - baby, 1 - young, 2 - middle-age, 3 - old) 
a7 - binokulars (0 - without, 1 - transparent, 2 - dark)
a8 - emotional expression (not state!) (0 - sad, 1 - neutral, 2 - happy)

in each attribute the number -1 describe undefined attribute value.

Example images of the 6x8 image array can by depicted by Matlab script show_images.m. 