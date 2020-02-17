import cv2
import matplotlib.pyplot as plt
import numpy as np


def plainHist(img):
    row, col = img.shape
    hist = [0.0] * 256
    for i in range(row):
        for j in range(col):
            hist[img[i, j]] += 1
    return np.array(hist)


def normalHist(img):
    row, col = img.shape
    hist = [0.0] * 256
    for i in range(row):
        for j in range(col):
            hist[img[i, j]] += 1
    return np.array(hist) / (row * col)


def cumulatifHist(arr):
    return [sum(arr[:i + 1]) for i in range(len(arr))]


def contrastStretching(new_img, shape):
    # cari nilai min
    min = new_img[0, 0]
    for i in range(shape[0]):
        for j in range(shape[1]):
            if new_img[i, j] < min:
                min = new_img[i, j]

    # cari nilai max
    max = new_img[0, 0]
    for i in range(shape[0]):
        for j in range(shape[1]):
            if new_img[i, j] > max:
                max = new_img[i, j]

    # contrast stretching
    for i in range(shape[0]):
        for j in range(shape[1]):
            new_img[i, j] = ((new_img[i, j] - min) / (max - min)) * 255


def histogramEqualization(img, shape):
    norHist = normalHist(img)  # cari normalized histogram
    cumHist = cumulatifHist(norHist)  # cari cumulatif histogram

    cdf = np.array(cumHist)
    transFuncVal = np.uint8(255 * cdf)
    equImg = np.zeros_like(img)
    equHist = normalHist(equImg)

    # equalization
    for i in range(shape[0]):
        for j in range(shape[1]):
            equImg[i, j] = transFuncVal[img[i, j]]

    return equImg, norHist, cumHist, equHist


img = cv2.imread('car.png', 0)
stretch_img = cv2.imread('car.png', 0)
new_img = histogramEqualization(img, img.shape)
contrastStretching(stretch_img, stretch_img.shape)

equImg, norHist, cumHist, equHist = histogramEqualization(img, img.shape)
oriHist = plainHist(img)

# show original image
cv2.imshow("original", img)
cv2.imshow("constrast streching", stretch_img)
cv2.imshow("equalized", equImg)

# plot histograms and transfer function
fig = plt.figure()
fig.add_subplot(221)
plt.plot(oriHist)
plt.title('Original histogram')  # original histogram
fig.add_subplot(222)
plt.plot(norHist)
plt.title('Normalized histogram')  # normalized histogram

fig.add_subplot(223)
plt.plot(cumHist)
plt.title('Cumulatif Histogram')  # cumulatife histogram

plt.show()

cv2.waitKey(0)
cv2.destroyAllWindows()
