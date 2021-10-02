logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

seed = 366872
turbostat.setseed(seed)
m = 100
n = 10
ARL.target = 370
monitorning.stat = "ac"
monitorning.stat.params = list("n_permutations" = 4000)
cap = 100000

calibration.nsim = 5000
calibration.lcl_seq = inverse(seq(2, 6.05, 0.0005))

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
evaluation.result = evaluate.unconditional(
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
print (evaluation.result)


filename =  paste(c(monitorning.stat,
                    format(ARL.target, nsmall = 0),
                    format(m, nsmall = 0),
                    format(n, nsmall = 0),
                    format(calibration.nsim, nsmall = 0),
                    format(seed, nsmall = 0)), collapse = "_")

basepath = paste(c("results/calibration_results/", filename, ".RData"), collapse = "")

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
     evaluation.result,
     file = basepath)
