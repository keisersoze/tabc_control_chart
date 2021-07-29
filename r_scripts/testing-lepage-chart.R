source("statistics.R")

n = 11
m = 100
X = rcauchy(m)
UCL = 11.25

points = c()
Ys = matrix(data = c(rcauchy(10* n), rcauchy (10 * n, location = 2)), nrow = 20, ncol = n, byrow=TRUE)
for (i in 1:10){
  Y = Ys[i,]
  st = lepage.stat (X,Y)
  points = append(points, st)
  phase2.data = append(phase2.data, c(Y))
  
}
for (i in 11:20){
  Y = Ys[i,]
  st = lepage.stat (X,Y)
  points = append(points, st)
  phase2.data = append(phase2.data, c(Y))
}

plot(seq(1,length(points)),points, ylim = (range(0,20)))
abline(h = UCL)

qcc(matrix(data = X, byrow = TRUE, ncol = n), type="xbar", newdata=Ys)

# UCL = 10.2
# 
# data(pistonrings)
# diameter <- qcc.groups(diameter, sample)
# X = as.vector(head(diameter, 25))
# 
# points = c()
# for (i in 26:40){
#     Y = diameter[i,]
#     st = lepage.stat (X,Y)
#     points = append(points, st)
# }
# plot(seq(1,length(points)),points, ylim = (range(0,20)))
# abline(h = UCL)



