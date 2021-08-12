source("statistics.R")
load("shared_data/cauchy-unbalanced.RData")

nperm2 = 10000

#Simulate location shift
points1 = c()
points2 = c()
for (i in 1:10){
  Y = rcauchy(n)
  tabc = Tabc.unbalanced (X,Y,"two.sided", nperm2)
  lep = lepage.stat (X,Y)
  points1 = append(points1, tabc)
  points2 = append(points2, lep)
}
for (i in 1:5){
  Y = rcauchy(n, location = 1)
  tabc = Tabc.unbalanced (X,Y,"two.sided", nperm2)
  lep = lepage.stat (X,Y)
  points1 = append(points1, tabc)
  points2 = append(points2, lep)
}
plot(seq(1,length(points1)),points1, ylim = (range(0,1)), xlab = "samples", ylab = "Tabc stat" )
abline(h = LCL)

plot(seq(1,length(points2)),points2, ylim = (range(0,15)))
abline(h = 10)
