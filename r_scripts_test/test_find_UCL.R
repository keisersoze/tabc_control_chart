seed = 42
set.seed(seed)
turbostat.setseed(seed)
n = 10
m = 100
shifts = c(0, 0.5)
X = rcauchy(m)
ARL.target = 100
nsim = 10
nperm = 5000
plotting.stat = "c"

start.time = proc.time()
result = find_UCL(X,n,ARL.target,nsim, nperm, plotting.stat)
duration.time = proc.time() - start.time
print (duration.time)

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


start.time = proc.time()
result2 = rl.conditional(X,n,nsim,nperm,shifts, LCL,plotting.stat, 5000)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)

start.time = proc.time()
result2 = rl.conditional(X,n,nsim,nperm,shifts, LCL,plotting.stat, 5000)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)


# ARL.test2 = rl.conditional2(X,n,ARL.target,nsim,nperm,LCL,plotting.stat, 5000)
# print(ARL.test2)


