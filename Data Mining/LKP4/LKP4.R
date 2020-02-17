getmode <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

library(mice)
str(forestfires)
summary(forestfires)
md.pattern(forestfires)

boxplot(forestfires)

forestfires$X[is.na(forestfires$X)] <-
  mean(forestfires$X, na.rm = TRUE)
forestfires$Y[is.na(forestfires$Y)] <-
  median(forestfires$Y, na.rm = TRUE)
forestfires$month[is.nan(forestfires$month)] <-
  getmode(forestfires$month)
forestfires$day[is.na(forestfires$day)] <- getmode(forestfires$day)
forestfires$FFMC[is.na(forestfires$FFMC)] <-
  median(forestfires$FFMC, na.rm = TRUE)
forestfires$DMC[is.na(forestfires$DMC)] <-
  median(forestfires$DMC, na.rm = TRUE)
forestfires$DC[is.na(forestfires$DC)] <-
  median(forestfires$DC, na.rm = TRUE)
forestfires$ISI[is.na(forestfires$ISI)] <-
  median(forestfires$ISI, na.rm = TRUE)
forestfires$temp[is.na(forestfires$temp)] <-
  median(forestfires$temp, na.rm = TRUE)
forestfires$RH[is.na(forestfires$RH)] <-
  median(forestfires$RH, na.rm = TRUE)
forestfires$wind[is.na(forestfires$wind)] <-
  median(forestfires$wind, na.rm = TRUE)
forestfires$rain[is.na(forestfires$rain)] <-
  median(forestfires$rain, na.rm = TRUE)
forestfires$area[is.na(forestfires$area)] <-
  median(forestfires$area, na.rm = TRUE)


md.pattern(forestfires)
summary(forestfires)

#Diskret
dcDiscretize <- discretize(forestfires$DC, "equalwidth", 4)
rhDiscretize <- discretize(forestfires$RH, "equalwidth", 3)

final <- cbind(forestfires, dcDiscretize, rhDiscretize)
final[1:10, ]

# Normalisasi atribut FFMC 
for (i in 1:length(forestfires$FFMC)) {
  forestfires$FFMC[i] = (forestfires$FFMC[i] - min(forestfires$FFMC)) /
    (max(forestfires$FFMC) - min(forestfires$FFMC))
}

# Normalisasi atribut DMC 
for (i in 1:length(forestfires$DMC)) {
  forestfires$DMC[i] = (forestfires$DMC[i] - min(forestfires$DMC)) /
    (max(forestfires$DMC) - min(forestfires$DMC))
}
forestfires[1:10,]

# membuat atribut baru yang merupakan penjumlahan FFMC dan DMC
forestfires$sumFFMC
forestfires$sumFFMC <- NULL
forestfires$sumFFMC[] <- forestfires$FFMC + forestfires$DMC
