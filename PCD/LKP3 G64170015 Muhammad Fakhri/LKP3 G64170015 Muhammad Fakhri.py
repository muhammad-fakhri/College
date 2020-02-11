import numpy as np
import cv2


# function for convert RGB image to grayscale image
def RGBtoGrayScale(img, shape, canvas):
    for i in range(shape[0]):
        for j in range(shape[1]):
            b, g, r = img[i, j]
            gray = b * 0.114 + g * 0.587 + r * 0.299
            canvas.itemset((i, j, 0), gray)


# function for calculating average of pixel intensity in a picture
def calcAvg(canvas, shape):
    sum = 0
    for i in range(shape[0]):
        for j in range(shape[1]):
            sum = sum + canvas[i, j, 0]
    avg = sum / (shape[0] * shape[1])
    return avg


# function for change the pixel based on average of pixel intensity
def change(canvas, avg, shape):
    for i in range(shape[0]):
        for j in range(shape[1]):
            if canvas[i, j, 0] < avg:
                canvas.itemset((i, j, 0), canvas[i, j, 0] * 0.5)
            else:
                if (canvas[i, j, 0] * 2) > 255:
                    canvas.itemset((i, j, 0), 255)
                else:
                    canvas.itemset((i, j, 0), canvas[i, j, 0] * 2)


# function for substracting image 1 and image 2
def imageSub(canvas1, canvas2, canvas_res):
    for i in range(shape[0]):
        for j in range(shape[1]):
            if int(canvas1[i, j, 0]) < int(canvas2[i, j, 0]):
                canvas_res.itemset((i, j, 0), 0)
            else:
                canvas_res.itemset(
                    (i, j, 0),
                    int(canvas1[i, j, 0]) - int(canvas2[i, j, 0]))


# the imageDiff function
def imageDiff(canvas1, canvas2, shape):
    avg1 = calcAvg(canvas1, shape)
    avg2 = calcAvg(canvas2, shape)
    change(canvas1, avg1, shape)
    change(canvas2, avg2, shape)

    canvas_result = np.zeros((shape[0], shape[1], 1), np.uint8)

    imageSub(canvas1, canvas2, canvas_result)

    cv2.imshow("Result", canvas_result)
    cv2.waitKey(0)


# THIS PROGRAM START HERE
# read the original image
img1 = cv2.imread("cameraman.jpg")
img2 = cv2.imread("equalized.jpg")

# take the image dimension
shape = img1.shape

# make a empty canvas
canvas1 = np.zeros((shape[0], shape[1], 1), np.uint8)
canvas2 = np.zeros((shape[0], shape[1], 1), np.uint8)

# convert original image to gryscale
RGBtoGrayScale(img1, shape, canvas1)
RGBtoGrayScale(img2, shape, canvas2)

# call the imageDiff function
imageDiff(canvas1, canvas2, shape)
