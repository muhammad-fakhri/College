import array

import cv2
import numpy as np


def getMax(a, b, c):
    max = a
    if b > max:
        max = b
    if c > max:
        max = c
    return max


def getMin(a, b, c):
    min = a
    if b < min:
        min = b
    if c < min:
        min = c
    return min


def RGBtoHSV(img):
    row, col, ch = img.shape
    output = np.zeros((row, col, ch), np.uint8)
    for i in range(row):
        for j in range(col):
            b, g, r = img[i, j]

            # Change R G B to [0,1] range value
            r, g, b = r / 255.0, g / 255.0, b / 255.0
            cmax = getMax(r, g, b)
            cmin = getMin(r, g, b)
            diff = cmax - cmin

            # determine H value
            if cmax == cmin:
                h = 0
            elif cmax == r:
                h = (60 * ((g - b) / diff) + 360) % 360
            elif cmax == g:
                h = (60 * ((b - r) / diff) + 120) % 360
            elif cmax == b:
                h = (60 * ((r - g) / diff) + 240) % 360

            # determine S value
            if cmax == 0:
                s = 0
            else:
                s = (diff / cmax) * 100

            # determine V value
            v = cmax * 100
            output.itemset((i, j, 0), h)
            output.itemset((i, j, 1), s)
            output.itemset((i, j, 2), v)
    return output


def RGBtoYCbCr(img):
    row, col, ch = img.shape
    output = np.zeros((row, col, ch), np.uint8)
    for i in range(row):
        for j in range(col):
            b, g, r = img[i, j]

            # calculate y, Cb, and Cr value
            y = 16 + (65.738 * r / 256) + (129.057 * g / 256) + (25.064 * b / 256)
            Cb = 128 - (37.945 * r / 256) - (74.494 * g / 256) + (112.439 * b / 256)
            Cr = 128 + (112.439 * r / 256) - (94.154 * g / 256) - (18.285 * b / 256)

            # set y, Cb, and Cr value to output
            output.itemset((i, j, 0), y)
            output.itemset((i, j, 1), Cr)
            output.itemset((i, j, 2), Cb)
    return output


def filter(img, min, max):
    row, col, ch = img.shape
    output = np.zeros((row, col, 1), np.uint8)
    for i in range(row):
        for j in range(col):
            y, Cb, Cr = img[i, j]

            # if y, Cb, and Cr value is inside the threshold
            if (y >= min[0] and y <= max[0]) and \
                    (Cb >= min[1] and Cb <= max[1]) and \
                    (Cr >= min[2] and Cr <= max[2]):
                output.itemset((i, j, 0), 255)
            # if y, Cb, and Cr value is outside the threshold
            else:
                output.itemset((i, j, 0), 0)
    return output


def masking(sourceImage, maskImage):
    row, col, ch = sourceImage.shape
    output = np.zeros((row, col, 3), np.uint8)
    for i in range(row):
        for j in range(col):

            # if pixel in maskImage is 255
            if maskImage[i, j] == 255:
                for k in range(ch):
                    output.itemset((i, j, k), sourceImage[i, j, k])

            # if pixel in maskImage is 0
            elif maskImage[i, j] == 0:
                for k in range(ch):
                    output.itemset((i, j, k), 0)
    return output


# read source image
image = cv2.imread("FACE DETECTION.png")

# convert RGB to HSV
hsvImage = RGBtoHSV(image)
cv2.imwrite("RGBtoHSV.png", hsvImage)


# prepare threshold array
min = array.array('i', [0, 133, 77])  # Min threshold
max = array.array('i', [235, 173, 127])  # Max threshold

# convert image from RGB to YCbCr
yCbCrImage = RGBtoYCbCr(image)

# generate a "Mask Image" to locate the position of the face
skinMask = filter(yCbCrImage, min, max)

# masking out the original image using previous skin mask
finalOutput = masking(image, skinMask)

# put the output into a new picture
cv2.imwrite("OutputFaceDetection.png", finalOutput)
