import cv2 
import numpy

inputImage = cv2.imread("LennaInput.jpg")
expectedOutput = cv2.imread("LennaOutput.jpg")
cv2.imshow("Input", inputImage)

def medianBlur(image, kernelLength):
	row, col, ch = image.shape
	output = numpy.zeros((row,col,ch), numpy.uint8)
	kernel = numpy.zeros((kernelLength*kernelLength))
	for x in range(kernelLength//2, row-kernelLength//2):
		for y in range(kernelLength//2, col-kernelLength//2):
			for i in range(kernelLength):
				for j in range(kernelLength):
					kernel[i*kernelLength+j] = image[x-i][y-j][0]
			kernel.sort()
			for c in range (ch):
				output[x][y][c] = kernel[kernelLength*kernelLength/2]
	return output

def lowPass(image, kernelLength):
	row, col, ch = image.shape
	output = numpy.zeros((row,col,ch), numpy.uint8)
	kernel = 0
	for x in range(kernelLength//2, row-kernelLength//2):
		for y in range(kernelLength//2, col-kernelLength//2):
			for i in range(kernelLength):
				for j in range(kernelLength):
					kernel += image[x-i][y-j][0]
			for c in range (ch):
				output[x][y][c] = kernel/(kernelLength*kernelLength)
			kernel = 0
	return output

inputKernel = int(raw_input())
medianBlurOutput = medianBlur(inputImage, inputKernel)
inputKernel = int(raw_input())
lowPassOutput = lowPass(medianBlurOutput, inputKernel)

cv2.imshow("MedianBlur Output", medianBlurOutput)
cv2.imshow("LowPass Output", lowPassOutput)
cv2.imshow("Expected Output", expectedOutput)
cv2.waitKey(0)