library("fpc")
library("factoextra")
library("mice")
library("cluster")

diabet = read.csv("~/Downloads/diabet.csv",sep = ",")
diabet1 = read.csv("~/Downloads/diabet.csv",sep = ",")
str(diabet)
summary(diabet)

md.pattern(diabet)
boxplot(diabet)

diabet$mass[is.na(diabet$mass)] <- mean (diabet$mass,na.rm= TRUE)
diabet$pedi[is.na(diabet$pedi)] <- mean (diabet$pedi,na.rm= TRUE)


for (i in 1:length(diabet$plas)) {
  diabet$plas[i] = (diabet$plas[i] - min(diabet$plas)) / (max(diabet$plas) - min(diabet$plas))
}

for (i in 1:length(diabet$insu)) {
  diabet$insu[i] = (diabet$insu[i] - min(diabet$insu)) / (max(diabet$insu) - min(diabet$insu))
}

diabet$class <- NULL
diabet$skin <- NULL
diabet$age <-NULL

kmeans.result <- kmeans(diabet, 5)
plot(kmeans.result)

plot(diabet[c("plas", "insu")], col =kmeans.result$cluster)
points(kmeans.result$centers[,c("plas","insu")], col = 1:3,pch = 8, cex=2)

pamk.result <- pamk(diabet)
pam.result <- pam(diabet, 5)
plot(pam.result)
