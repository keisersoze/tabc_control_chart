logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

## Calibration

seed = 56
turbostat.setseed(seed)
n = 5
m = 100
ARL.target = 100
nperm = 5000
plotting.stat = "a"
cap = 4000

calibration.nsim = 5000
calibration.lcl_seq = inverse(seq(2, 4.55, 0.01))

start.time = proc.time()
rls = calibrate.uncoditional(
  m = m,
  n = n,
  nsim = calibration.nsim,
  nperm = nperm,
  lcl_seq = calibration.lcl_seq,
  test = plotting.stat,
  run_length_cap = cap
)

duration.time = proc.time() - start.time
print (duration.time)

arls = colMeans(rls)
plot(calibration.lcl_seq ~ arls, pch=20, cex=0.02)
afn = approxfun(arls,calibration.lcl_seq)
curve(afn, add=TRUE, col="red")
# lines(data$x[j],lw1$fitted[j],col="red",lwd=1)
LCL = afn(ARL.target)
abline(h = LCL)
abline(v = ARL.target)
print(LCL)

# Evaluation
evaluation.nsim = 5000
evaluation.shifts = c(0)

start.time = proc.time()
result2 = rl.uncoditional(
  m = m,
  n = n,
  nsim = evaluation.nsim,
  nperm = nperm,
  shifts = evaluation.shifts,
  LCL = LCL,
  test = plotting.stat,
  run_length_cap = cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)
