source("statistics.R")

# set.seed(1)
# 
# n = 5
# m = 100
# X = rcauchy(m)
# nperm2 =  1000
# 
# points = c()
# Ys = matrix(data = c(rcauchy(10* n), rcauchy (10 * n, location = 10)), nrow = 20, ncol = n, byrow=TRUE)
# for (i in 1:10){
#   Y = Ys[i,]
#   st = Tabc (X,Y,"two.sided", nperm2)
#   points = append(points, st)
# }
# for (i in 11:20){
#   Y = Ys[i,]
#   st = Tabc (X,Y,"two.sided", nperm2)
#   points = append(points, st)
# }
# 
# plot(seq(1,length(points)),points, ylim = (range(0,1)))
# 
# qcc(matrix(data = X, byrow = TRUE, ncol = n), type="xbar", newdata=Ys)

set.seed(10)

load(file = "shared_data/pistonring-diameters.RData")

X = as.vector(head(dia, 25))

points = c()
for (i in 26:40){
    Y = dia[i,]
    st = Tabc.unbalanced (X,Y,"two.sided", 5000)
    points = append(points, st)
}
plot(seq(1,length(points)),points, ylim = (range(0,1)))



