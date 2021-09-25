logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

seed = 1
turbostat.setseed(seed)
n = 10
m = 100
dist = "norm"
ARL.target = 100
nperm = 1000
chart = "abc"
cap = 4000

calibration.nsim = 1000
calibration.lcl_seq = inverse(seq(2, 4.60, 0.01))

evaluation.nsim = 1000
evaluation.shifts = c(0, 1)

# Calibration

start.time = proc.time()
rls = calibrate.unconditional(
  m = m,
  n = n,
  dist = dist,
  nsim = calibration.nsim,
  nperm = nperm,
  lcl_seq = calibration.lcl_seq,
  chart = chart,
  run_length_cap = cap
)

duration.time = proc.time() - start.time
print (duration.time)

arls = colMeans(rls)
plot(calibration.lcl_seq ~ arls, pch=20, cex=0.02)
afn = approxfun(arls,calibration.lcl_seq)
curve(afn, add=TRUE, col="red")
LCL = afn(ARL.target)
abline(h = LCL)
abline(v = ARL.target)
print(LCL)

# Evaluation

start.time = proc.time()
result2 = rl.uncoditional(
  m = m,
  n = n,
  dist = dist,
  params = params,
  nsim = evaluation.nsim,
  nperm = nperm,
  shifts = evaluation.shifts,
  LCL = LCL,
  test =chart,
  run_length_cap = cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)
