import cv2
import numpy as np


def makeLowPassKernel():
    filter = np.ones((3, 3), np.float32)
    for i in range(0, 3):
        for j in range(0, 3):
            filter[i, j] *= 1 / 9
    return filter


def medianFilter(img, kernelSize):
    row, col = img.shape
    kernel = np.zeros((kernelSize * kernelSize), np.uint8)
    h = int(kernelSize / 2)
    output = np.zeros((row, col, 1), np.uint8)
    for i in range(0, row):
        for j in range(0, col):
            if i < h or j < h or i >= row - h or j >= col - h:
                output[i][j] = 0
            else:
                index = 0
                for k in range(-h, h + 1):
                    for l in range(-h, h + 1):
                        kernel[index] = img[i + k, j + l]
                        index += 1
                kernel.sort()
                output[i][j] = kernel[int(kernelSize * kernelSize / 2)]
    return output


def lowPassFilter(img, kernel):
    row, col = img.shape
    mrow, mcol = kernel.shape
    h = int(mrow / 2)

    output = np.zeros((row, col), np.uint8)
    for i in range(0, row):
        for j in range(0, col):
            if i < h or j < h or i >= row - h or j >= col - h:
                output.itemset((i, j), 0)
            else:
                imgsum = 0
                for k in range(-h, h + 1):
                    for l in range(-h, h + 1):
                        res = img[i + k, j + l] * kernel[h + k, h + l]
                        imgsum += res

                if imgsum > 255:
                    output.itemset((i, j), 255)
                elif imgsum < 0:
                    output.itemset((i, j), 0)
                else:
                    output.itemset((i, j), imgsum)
    return output


image = cv2.imread("LennaInput.jpg", 0)
expectOutput = cv2.imread("LennaOutput.jpg", 0)
medianOutput = medianFilter(image, 3)
lowPassKernel = makeLowPassKernel()
lowPasOutput = lowPassFilter(image, lowPassKernel)

cv2.imshow("Awal", image)
cv2.imshow("Expected Output", expectOutput)
cv2.imshow("Median Blur", medianOutput)
cv2.imshow("Low Pass Blur", lowPasOutput)
cv2.waitKey(0)
cv2.destroyAllWindows()
