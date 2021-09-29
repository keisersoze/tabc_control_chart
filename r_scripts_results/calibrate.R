logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

seed = 46599
turbostat.setseed(seed)
m = 50
n = 5
ARL.target = 250
monitorning.stat = "ac-2"
monitorning.stat.params = list("n_permutations" = 4000)
cap = 50000

calibration.nsim = 5000
calibration.lcl_seq = inverse(seq(2, 5.30, 0.0001))

evaluation.dist = "norm"
evaluation.nsim = 5000
evaluation.shifts = c(0, 1)

# Calibration

start.time = proc.time()
rls = calibrate.unconditional(
  m = m,
  n = n,
  distribution_key = "norm",
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
  distribution_key = evaluation.dist,
  monitoring_statistic_key = monitorning.stat,
  monitoring_statistic_parameters = monitorning.stat.params,
  nsim = evaluation.nsim,
  run_length_cap = cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (result2)

save(m,
     n,
     monitorning.stat,
     monitorning.stat.params,
     calibration.nsim,
     calibration.lcl_seq,
     evaluation.dist,
     evaluation.nsim,
     evaluation.shifts,
     cap,
     seed,
     rls,
     arls,
     LCL,
     file = "results/calibration_results/ac-2_50_5_v3.RData")
