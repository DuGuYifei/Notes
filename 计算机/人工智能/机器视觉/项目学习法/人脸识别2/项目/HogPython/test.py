# STEPS OF HOG
# 1. Calculate gradient
# 2. Calculate magnitude and angle
# Divide img into Cells of size N
# 3. Orientation based histogram?
# compute it into
# 4. profit
import numpy as np
from matplotlib import pyplot as plt

CELL_SIZE_X = 4
CELL_SIZE_Y = 4
NUM_BINS = 9

imgs = []
lines = []
ppl = []
num_I = 0
f = open('../famous48/x24x24.txt', 'r')
for i, line in enumerate(f):
    if i == 1:
        num_I = int(line)
        img_size = int(np.sqrt(num_I))
    elif i >= 2:
        lines = [float(y) for y in line.split()]
        person = lines[-6]
        ppl.append(person)
        lines = lines[0:num_I]
        image = np.array(lines).reshape((img_size, img_size))
        imgs.append(image)

f = open('../famous48/y24x24.txt', 'r')
for i, line in enumerate(f):
    if i == 1:
        num_I = int(line)
        img_size = int(np.sqrt(num_I))
    elif i >= 2:
        lines = [float(y) for y in line.split()]
        person = lines[-6]
        ppl.append(person)
        lines = lines[0:num_I]
        image = np.array(lines).reshape((img_size, img_size))
        imgs.append(image)

f = open('../famous48/z24x24.txt', 'r')
for i, line in enumerate(f):
    if i == 1:
        num_I = int(line)
        img_size = int(np.sqrt(num_I))
    elif i >= 2:
        lines = [float(y) for y in line.split()]
        person = lines[-6]
        ppl.append(person)
        lines = lines[0:num_I]
        image = np.array(lines).reshape((img_size, img_size))
        imgs.append(image)

print(num_I)
print(ppl)


# GdirMatrix=np.zeros((img_size,img_size))


def Glx(x, img):
    if (x >= (img_size - 1)):
        return np.subtract(img[:, x], img[:, (x - 1)])
    elif (x < 1):
        return np.subtract(img[:, (x + 1)], img[:, x])
    else:
        return np.subtract(img[:, (x + 1)], img[:, (x - 1)])


def Gly(y, img):
    if (y >= (img_size - 1)):
        return np.subtract(img[y, :], img[(y - 1), :])
    elif (y < 1):
        return np.subtract(img[(y + 1), :], img[y, :])
    else:
        return np.subtract(img[(y + 1), :], img[(y - 1), :])


def split_cells(mag, dir):
    cell_begin = np.arange(0, img_size, CELL_SIZE_X)
    histograms = []
    theta = np.pi / NUM_BINS
    for row in cell_begin:
        hist = np.zeros(NUM_BINS)
        for i in range(row, row + CELL_SIZE_X):
            for j in range(row, row + CELL_SIZE_X):
                val = (dir[i][j] / theta)
                n = int(np.floor(val))
                print(f"dir:{dir[i][j]} n:{n} i:{i} j:{j}")
                # Cn = bin_step*(n+0.5)
                hist[n] = hist[n] + mag[i][j] * (1 - (val - n))
                hist[n + 1] = hist[n + 1] + mag[i][j] * (val - n)
        histograms.append(hist)
    return np.array(histograms).reshape(1, NUM_BINS * int(img_size / CELL_SIZE_X))


def Gmatrices(img, img_size):
    # GmagMatrix=np.zeros((img_size,img_size))
    Gx = []
    Gy = []
    for i in range(0, img_size):
        print(i)
        Gx.append(Glx(i, img))
        Gy.append(Gly(i, img))
    Gx = np.array(Gx)
    Gxmask = (Gx == 0)

    Gy = np.transpose(np.array(Gy))
    Gdir = np.nan_to_num(np.arctan(Gy / Gx))
    GdirInf = np.nan_to_num(0.5 * np.pi * (Gxmask * np.sign(Gy)))
    Gdir = Gdir + GdirInf

    Gmag = np.sqrt(np.power(Gx, 2) + np.power(Gy, 2))
    return [Gmag, Gdir]


# print(image)

def split_cells(mag, dir):
    cell_begin = np.arange(0, img_size, CELL_SIZE_X)
    histograms = []
    theta = np.pi / NUM_BINS
    for row in cell_begin:
        hist = np.zeros(NUM_BINS)
        for i in range(row, row + CELL_SIZE_X):
            for j in range(row, row + CELL_SIZE_X):
                val = ((dir[i][j] / theta)) % NUM_BINS
                n = int(np.floor(val))
                print(f"dir:{dir[i][j]} n:{n} i:{i} j:{j}")
                # Cn = bin_step*(n+0.5)
                hist[n] = hist[n] + mag[i][j] * (1 - (val - n))
                hist[(n + 1) % NUM_BINS] = hist[(n + 1) % NUM_BINS] + mag[i][j] * (val - n)
        histograms.append(hist)
    return np.array(histograms).reshape(1, NUM_BINS * int(img_size / CELL_SIZE_X))


f2 = open('../Hog/histograms_train.txt', 'w')
f3 = open('../Hog/histograms_test.txt', 'w')
it = 1
for image in imgs:
    if it % 5 == 0:
        data = Gmatrices(image, img_size)
        hist = split_cells(data[0], data[1])
        text = str(int(ppl[it-1])) + ' ' + str(hist) + '\n'
        it = it + 1
        f3.write(text)
    else:
        data = Gmatrices(image, img_size)
        hist = split_cells(data[0], data[1])
        text = str(int(ppl[it-1])) + ' ' + str(hist) + '\n'
        it = it + 1
        f2.write(text)
# data = Gmatrices(image,img_size)
# f, axarr = plt.subplots(1,3)
# axarr[0].imshow(image, interpolation='nearest')
# axarr[1].imshow(np.array(data[0]), interpolation='nearest')
# axarr[2].imshow(np.array(data[1]), interpolation='nearest')


print(split_cells(data[0], data[1]))
