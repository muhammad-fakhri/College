poke1 = read.csv("~/Downloads/pokemon1.csv",sep = ";")
poke2 = read.csv("~/Downloads/pokemon2.csv",sep = ",")

pokeGabung <- rbind(poke1, poke2)

str(pokeGabung)
summary(pokeGabung)
md.pattern(pokeGabung)

pokeGabung$HP[is.na(pokeGabung$HP)] <- mean (pokeGabung$HP,na.rm= TRUE)
pokeGabung$Defense[is.na(pokeGabung$Defense)] <- mean (pokeGabung$Defense,na.rm= TRUE)
pokeGabung$SpAtk[is.na(pokeGabung$SpAtk)] <- mean (pokeGabung$SpAtk,na.rm= TRUE)
pokeGabung$SpDef[is.na(pokeGabung$SpDef)] <- mean (pokeGabung$SpDef,na.rm= TRUE)

pokeSample<-pokeGabung[sample(1:nrow(pokeGabung),200,replace=FALSE),]
summary(pokeSample)

poke <- pokeSample
pokeSample$Name <- NULL
(kmeans.result <- kmeans(pokeSample, 4))
pamk.result <- pamk(iris2)

table(poke$Nama, kmeans.result$cluster)

plot(pokeSample[c("Attack", "Defense")], col =kmeans.result$cluster)
points(kmeans.result$centers[,c("Attack","Defense")], col = 1:3,pch = 8, cex=2)
