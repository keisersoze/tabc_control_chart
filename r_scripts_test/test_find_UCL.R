n = 10
m = 100
X = rnorm(m)
ARL.target = 100
nsim = 1000
nperm = 1000
plotting.stat = "abc"

result = find_UCL(X,n,ARL.target,nsim, nperm, plotting.stat)
LCL = result[["LCL"]]
distribution = result[["distribution"]]
print (LCL)

# ntests = nsim * ARL.target
# rl.sample = c()
# rl = 0
# for (i in 1:ntests){
#   Y = rnorm(n)
#   st = permtest.tabc (X,Y, nperm)[2]
#   # st = lepage.stat (X,Y)
#   if (st > LCL ){
#     rl = rl + 1
#   } else {
#     rl.sample = append(rl.sample, rl)
#     rl = 0
#   }
# }

ARL.test = rl.conditional(X,n,nsim,nperm,LCL,plotting.stat, 5000)
print(ARL.test)

# ARL.test2 = rl.conditional2(X,n,ARL.target,nsim,nperm,LCL,plotting.stat, 5000)
# print(ARL.test2)


