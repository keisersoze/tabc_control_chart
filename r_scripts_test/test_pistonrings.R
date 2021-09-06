# library(qcc)
#
# data(pistonrings)
# attach(pistonrings)
# diameter <- qcc.groups(diameter, sample)

X = rcauchy(100)

seed = 42

n = 10
shifts = c(0, 0.001, 0.002, 0.003, 0.004)
ARL.target = 250
nsim = 2
nperm = 5000

plotting.stat1 = "abc"

start.time = proc.time()
plotting.stat1.calibration = find_UCL(X,n,ARL.target,nsim, nperm, plotting.stat1, seed)
duration.time = proc.time() - start.time
print (duration.time)
plotting.stat1.LCL = plotting.stat1.calibration[["LCL"]]
distribution = plotting.stat1.calibration[["distribution"]]
print (plotting.stat1.LCL)

start.time = proc.time()
plotting.stat1.evaluation = rl.conditional(X,n,nsim,nperm,shifts, plotting.stat1.LCL,plotting.stat1, 5000, seed)
duration.time = proc.time() - start.time
print(duration.time)
print (plotting.stat1.evaluation)

plotting.stat2 = "a"

start.time = proc.time()
plotting.stat2.calibration = find_UCL(X,n,ARL.target,nsim, nperm, plotting.stat2, seed)
duration.time = proc.time() - start.time
print (duration.time)
plotting.stat2.LCL = plotting.stat2.calibration[["LCL"]]
distribution = plotting.stat2.calibration[["distribution"]]
print (plotting.stat2.LCL)

start.time = proc.time()
plotting.stat2.evaluation = rl.conditional(X,n,nsim,nperm,shifts, plotting.stat2.LCL,plotting.stat2, 5000, seed)
duration.time = proc.time() - start.time
print(duration.time)
print (plotting.stat2.evaluation)

