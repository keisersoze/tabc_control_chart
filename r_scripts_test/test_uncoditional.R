logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

## Calibration

seed = 42
turbostat.setseed(seed)
n = 10
m = 100
ARL.target = 250
nsim = 200
nperm = 5000
plotting.stat = "c"

lcl_seq = inverse(seq(2, 5.70, 0.01))
cap = 4000

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

summary = colMeans(rls)
M = loess(lcl_seq ~ summary)
plot(M)
LCL = as.vector(predict(M, data.frame(summary = ARL.target)))
print(LCL)

# Evaluation

shifts = c(0, 0.01, 0.02, 0.05)

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
