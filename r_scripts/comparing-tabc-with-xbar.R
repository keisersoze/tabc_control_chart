
source("statistics.R")

# set.seed(42)

sam = function(n, location, scale){
  return (rLaplace(n, mu = location, b = scale))
}

n = 5
m = 100
location = 1
location.shift = -2
scale = 1
X = sam(m, location = location , scale = scale)
nperm2 =  3000

points = c()
Ys = matrix(data = c(sam(10* n , location = location, scale = scale), sam (10 * n, location = location + location.shift , scale = scale)), nrow = 20, ncol = n, byrow=TRUE)
for (i in 1:10){
  Y = Ys[i,]
  st = Tc.pvalue (X,Y)
  points = append(points, st)
}
for (i in 11:20){
  Y = Ys[i,]
  st = Tc.pvalue(X,Y)
  points = append(points, st)
}

plot(seq(1,length(points)),points, ylim = (range(0,10)))
abline(h = 8.57 )


points2 = c()
for (i in 1:10){
  Y = Ys[i,]
  st = mean (Y)
  points2 = append(points2, st)
}
for (i in 11:20){
  Y = Ys[i,]
  st = mean (Y)
  points2 = append(points2, st)
}
plot(seq(1,length(points2)),points2, ylim = (range(-5,5)))
sd = scale
UCL = location + 3 * sd
LCL = location - 3 * sd
abline(h = UCL )
abline(h = LCL )



#qcc(data= matrix (data=X, ncol =n), center = location, std.dev = scale, nsigmas = 3, type="xbar", newdata=Ys)

# set.seed(10)
#
# load(file = "shared_data/pistonring-diameters.RData")
#
# X = as.vector(head(dia, 25))
#
# points = c()
# for (i in 26:40){
#     Y = dia[i,]
#     st = Tabc.unbalanced (X,Y,"two.sided", 5000)
#     points = append(points, st)
# }
# plot(seq(1,length(points)),points, ylim = (range(0,1)))



