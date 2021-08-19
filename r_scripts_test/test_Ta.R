source("statistics.R")

# x1 = rnorm(50, mean = 0)
# x2 = rnorm(50, mean = 0.5)
# print (testA(x1,x2,10000))
# print (Ta.pvalue(x1,x2,10000))

nsim = 5000
alpha = 0.05
rejected = 0
x1 = rexp(50, rate = 1)
for(i in seq(1, nsim)){
  x2 = rexp(50, rate = 1)
  pa = testA(x1,x2,1000)[2]
  if (pa < alpha){
    rejected = rejected + 1
  }
}
print (rejected/ nsim)

