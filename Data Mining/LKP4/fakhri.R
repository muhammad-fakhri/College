NA + 1
sum(c(NA, 1, 2))
median(c(NA, 1, 2, 3), na.rm = TRUE)
length(c(NA, 2, 3, 4))
3 == NA
NA == NA
TRUE | NA

length(c(1, 2, NULL, 4))
sum(c(1, 2, NULL, 4))
x <- NULL
c(x, 2)

pi / 0
2 * Inf
Inf - 1e+10
Inf + Inf
3 < -Inf
Inf == Inf

NaN + 1
exp(NaN)
# 1. Eksplorasi data
data = airquality
str(data)
summary(data)

# - Pakai library mice untuk mengetahui jumlah data yang missing
library(mice)
md.pattern(data)

# 2. Pembersihan data
data <- airquality
# - mengisikan nilai mean untuk missing value di atribut
data$Solar.R
data$Solar.R[is.na(data$Solar.R)] <-
  mean (data$Solar.R, na.rm = TRUE)
data$Ozone[is.na(data$Ozone)] <-
  mean (data$Ozone, na.rm = TRUE)
md.pattern(data)
data$Ozone

# - Untuk atribut dengan tipe data kategorik
#names(sort(-table(x))[1]
data$Ozone
# - CONTOH AJA
data$Ozone[is.na(data$Ozone)] = names(sort(-table(data$Ozone)))[1]
md.pattern(data)

# 3. Transformasi data
data$Month
data$bulan <- NULL
data$bulan[data$Month == 5] <- "Mei"
data$bulan[data$Month == 6] <- "Juni"
data$bulan[data$Month == 7] <- "Juli"
data$bulan[data$Month == 8] <- "Agustus"
data$bulan[data$Month == 9] <- "September"

# - Normalisasi
for (i in 1:length(data$Ozone)) {
  data$Ozone[i] = (data$Ozone[i] - min(data$Ozone)) / (max(data$Ozone) - min(data$Ozone))
}
summary(data$Ozone)

# 4. Reduksi data
# - Menghapus variabel tertentu
data$bulan <- NULL
# - Sampling data
dataBaru <- data [which(data$Month > 7 & data$Wind >= 10), ]
dataBaru[26:30, ]
nrow(dataBaru)
dataRandom <- data[sample(1:nrow(data), 50, replace = FALSE), ]
dataRandom[1:2, ]
nrow(dataRandom)

# Integrasi data
# - menggabungkan dataset dibagian kolom, syarat:jumlah baris harus sama
#total <- merge(data frameA, data frameB, by = "ID")
# - menggabungkan 2 dataset secara baris, syarat:jumlah kolom harus sama.
# - contoh penggabungan data dari tahap reduksi sampling data
dataGabung <- rbind(dataBaru, dataRandom)
dataGabung[29:32, ]
nrow(dataGabung)

# 5. Diskretisasi data
# - Contoh membagi atribut wind menjadi 3 kelompok
data$Wind <- cut (data$Wind, 3, include.lowest = TRUE)

# - Diskretisasi unsupervised
install.packages("infotheo")
library(infotheo)
dataIris = iris # Menggunakan data Iris
str(dataIris)
# - contoh melakukan diskretisasi pada atribut sepaldengan membagi menjadi 3 kategori dengan metode equalwidth
ew.Sepal <- discretize(dataIris$Sepal.Length, disc = "equalwidth", 3)
ew.Sepal <- discretize(dataIris$Sepal.Length, "equalwidth", 3)
# - contoh melakukan diskretisasi pada atribut petaldengan membagi menjadi 3 kategori dengan metode equalfrequency
ef.Petal <- discretize(dataIris$Petal.Length, disc = "equalfreq", 3)

ew.Sepal
summary(ew.Sepal)

# - Diskretisasi supervised
install.packages("discretization")
library(discretization)
