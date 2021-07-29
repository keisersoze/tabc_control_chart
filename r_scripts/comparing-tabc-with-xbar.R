source("statistics.R")

n = 5
m = 100
X = rexp(m)
nperm2 =  1000

points = c()
Ys = matrix(data = c(rexp(10* n), rexp (10 * n, rate = 3)), nrow = 20, ncol = n, byrow=TRUE)
for (i in 1:10){
  Y = Ys[i,]
  st = Tabc (X,Y,"two.sided", nperm2)
  points = append(points, st)
}
for (i in 11:20){
  Y = Ys[i,]
  st = Tabc (X,Y,"two.sided", nperm2)
  points = append(points, st)
}

plot(seq(1,length(points)),points, ylim = (range(0,1)))

qcc(matrix(data = X, byrow = TRUE, ncol = n), type="xbar", newdata=Ys)

