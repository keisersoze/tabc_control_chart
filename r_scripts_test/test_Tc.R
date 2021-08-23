source("statistics.R")

x1 = rnorm(50, mean = 0)
x2 = rnorm(50, mean = 0)

print (Tc.pvalue2(x1,x2,10000))
print (testC(x1,x2,10000))
print (exact.tc(x1,x2))
print (wilcox.test(x1,x2, alternative = "l" ))
print (permtest.tc(x1,x2, 10000))

# nsim = 5000
# alpha = 0.05
# rejected = 0
# for(i in seq(1, nsim)){
#   x1 = rexp(50, rate = 1)
#   x2 = rexp(50, rate = 1)
#   pa = testC(x1,x2,1000)[2]
#   if (pa < alpha){
#     rejected = rejected + 1
#   }
# }
# print (rejected/ nsim)
