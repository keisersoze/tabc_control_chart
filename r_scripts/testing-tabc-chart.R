source("statistics.R")
load("shared_data/normal-unbalanced.RData")

nperm2 = 1000

#Simulate location shift
points = c()
for (i in 1:5){
  Y = rnorm(n)
  st = Tabc.unbalanced (X,Y,"two.sided", nperm2)
  points = append(points, st)
}
for (i in 1:5){
  Y = rnorm(n, mean = 1)
  st = Tabc.unbalanced (X,Y,"two.sided", nperm2)
  points = append(points, st)
}
plot(seq(1,length(points)),points, ylim = (range(0,1)))
abline(h = LCL)
