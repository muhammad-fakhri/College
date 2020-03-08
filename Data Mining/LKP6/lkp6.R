# K-Means
iris2 <- iris
iris2$Species <- NULL
(kmeans.result <- kmeans(iris2, 3))

table(iris$Species, kmeans.result$cluster)
plot(iris2[c("Sepal.Length", "Sepal.Width")], col = kmeans.result$cluster)
points(
  kmeans.result$centers[, c("Sepal.Length", "Sepal.Width")],
  col = 1:3,
  pch = 8,
  cex = 2
)

# K-Medoid
install.packages("fpc")
library(fpc)
install.packages("factoextra")
library(factoextra)

pamk.result <- pamk(iris2)
pamk.result$nc
table(pamk.result$pamobject$clustering, iris$Species)

layout(matrix(c(1, 2), 1, 2)) # 2 graphs per page
plot(pamk.result$pamobject)
layout(matrix(1)) # change back to one graph per page

#Hierarchical clustering

# import data
data1 <- read.csv("~/Downloads/data1.csv", header = FALSE)

# Praproses
# liat pattern missing value di mice
md.pattern(data1)
# liat resume data
summary(data1)
# liat ringkasan dan tipe data dari tiap atribut
str(data1)
# mengganti missing value dengan nilai mean 
# di tiap atribut yang memiliki missing value
data1$V2[is.na(data1$V2)] <- mean (data1$V2, na.rm = TRUE)
data1$V3[is.na(data1$V3)] <- mean (data1$V3, na.rm = TRUE)
data1$V4[is.na(data1$V4)] <- mean (data1$V4, na.rm = TRUE)
data1$V5[is.na(data1$V5)] <- mean (data1$V5, na.rm = TRUE)
data1$V6[is.na(data1$V6)] <- mean (data1$V6, na.rm = TRUE)
data1$V7[is.na(data1$V7)] <- mean (data1$V7, na.rm = TRUE)

# melihat kembali pattern missing value di mice
#untuk memastikan bahwa sudah tidak ada missing value
md.pattern(data1)

# mengambil data sampel sebanyak 40 data
idx <- sample(1:dim(data1)[1], 40)
dataSample <- data1[idx, ]
dataSample$V1 <- NULL

# hierarchical clustering dengan metode average linkage
hcAverage <- hclust(dist(dataSample), method = "ave")
plot(hcAverage, hang = -1, labels = data1$V1[idx])

# hierarchical clustering dengan metode single linkage
hcSingle <- hclust(dist(dataSample), method = "single")
plot(hcSingle, hang = -1, labels = data1$V1[idx])

# hierarchical clustering dengan metode complete linkage
hcComplete <- hclust(dist(dataSample), method = "complete")
plot(hcComplete, hang = -1, labels = data1$V1[idx])
