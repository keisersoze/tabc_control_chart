logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

## Calibration

seed = 2
turbostat.setseed(seed)
n = 10
m = 100
ARL.target = 250
nsim = 1000
nperm = 5000
plotting.stat = "c"
cap = 4000

lcl_seq = inverse(seq(2, 5.60, 0.01))

start.time = proc.time()
rls = calibrate.uncoditional(
  m = m,
  n = n,
  nsim = nsim,
  nperm = nperm,
  lcl_seq = lcl_seq,
  test = plotting.stat,
  run_length_cap = cap
)

duration.time = proc.time() - start.time
print (duration.time)

arls = colMeans(rls)
plot(lcl_seq ~ arls, pch=20, cex=0.02)
M = loess(lcl_seq ~ arls)
# lines(data$x[j],lw1$fitted[j],col="red",lwd=1)
abline(h = LCL)
abline(v = ARL.target)
LCL = as.vector(predict(M, data.frame(arls = ARL.target)))
print(LCL)

# Evaluation

shifts = c(0)

start.time = proc.time()
result2 = rl.uncoditional(
  m = m,
  n = n,
  nsim = nsim,
  nperm = nperm,
  shifts = shifts,
  LCL = LCL,
  test = plotting.stat,
  run_length_cap = cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)
