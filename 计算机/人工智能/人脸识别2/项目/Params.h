#pragma once

//first line contains the number of examples L,
//second line contains the number of pixels N in each image
//a1 - face containing flag : (1 - with face, 0 - without face),
//a2 - image number in current class (person)beginning from 0,
//a3 - class (person)number beginning from 0,
//a4 - sex(0 - woman, 1 - man)
//a5 - race(0 - white, 1 - negro, 2 - indian, ...)
//a6 - age(0 - baby, 1 - young, 2 - middle - age, 3 - old)
//a7 - binokulars(0 - without, 1 - transparent, 2 - dark)
//a8 - emotional expression(not state!) (0 - sad, 1 - neutral, 2 - happy)


const int sizeX = 24;
const int sizeY = 24;

const int LBPH_blockX = 8; //8?
const int LBPH_blockY = 8; //8?
const int LBPH_blockXY59 = LBPH_blockX * LBPH_blockY * 59;
const int LBPH_cellPerBlockX = sizeX / LBPH_blockX;
const int LBPH_cellPerBlockY = sizeY / LBPH_blockY;

const int Hog_pixelXPerCell = 3;
const int Hog_pixelYPerCell = 3;
const int Hog_cellXPerBlock = 2;
const int Hog_cellYPerBlock = 2;
const int Hog_bin = 9;
const float Hog_angelRange = 180 / Hog_bin;
const int Hog_numX_block = sizeX / Hog_pixelXPerCell - Hog_cellXPerBlock + 1;
const int Hog_numY_block = sizeY / Hog_pixelYPerCell - Hog_cellYPerBlock + 1;
const int Hog_num_features = (sizeX / Hog_pixelXPerCell - Hog_cellXPerBlock + 1) * (sizeY / Hog_pixelYPerCell - Hog_cellYPerBlock + 1) * Hog_cellXPerBlock * Hog_cellYPerBlock * Hog_bin;

const int Haar_pixelXPerCell = 2;
const int Haar_pixelYPerCell = 3;
const int Haar_FourRectSize = 4;
const float HaarEdgeThreshold = 1;
const float HaarLineThreshold = 1;
const float HaarFourRectangleThreshold = 1;
const int Haar_num_features = 24 * 24 * 3;