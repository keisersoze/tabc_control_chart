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
monitorning.stat = "abc"
monitorning.stat.params = list("n_permutations" = 1000)
cap = 4000

calibration.nsim = 50
calibration.lcl_seq = inverse(seq(2, 4.60, 0.005))

evaluation.nsim = 50
evaluation.shifts = c(0, 1)

# Calibration

start.time = proc.time()
rls = calibrate.unconditional(
  m = m,
  n = n,
  distribution_key = dist,
  monitoring_statistic_key = monitorning.stat,
  monitoring_statistic_parameters = monitorning.stat.params,
  lcl_seq = calibration.lcl_seq,
  nsim = calibration.nsim,
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
result2 = evaluate.unconditional(
  m = m,
  n = n,
  LCL = LCL,
  shifts = evaluation.shifts,
  distribution_key = dist,
  monitoring_statistic_key = monitorning.stat,
  monitoring_statistic_parameters = monitorning.stat.params,
  nsim = evaluation.nsim,
  run_length_cap = cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)
