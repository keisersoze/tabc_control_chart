logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

library(turbostat)

# Calibration parameters

calib.seed = 324
calib.m = 100
calib.n = 10

calib.ARL0.target = 250

calib.monitor_stat = "sum-of-sings"
# calib.monitor_stat.params = list("n_permutations" = 3500)
calib.monitor_stat.params = list()

calib.cap = 25000

calib.nsim = 10000
# calib.lcl_seq = inverse(seq(20, 50, 0.1))
calib.limits_seq = seq(0, 9 , 1)
calib.upper_limit = TRUE

calib.eval.dist = "norm"
calib.eval.dist.params = list("mean" = 0 , "sd" = 1)
calib.eval.nsim = 10000
calib.eval.shifts = c(0, 0.25, 0.5, 0.75, 1)

# Calibration script

turbostat.setseed(calib.seed)

start.time = proc.time()
calib.rls = calibrate.unconditional(
  m = calib.m,
  n = calib.n,
  distribution_key = "norm",
  distribution_parameters = list("mean" = 0 , "sd" = 1),
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  limits_seq = calib.limits_seq,
  upper_limit = calib.upper_limit,
  nsim = calib.nsim,
  run_length_cap = calib.cap
)

duration.time = proc.time() - start.time
print (duration.time)

calib.arls = colMeans(calib.rls)
plot(calib.limits_seq ~ calib.arls, pch=20, cex=0.02)
afn = approxfun(calib.arls,calib.limits_seq)
curve(afn, add=TRUE, col="red")
calib.limit = afn(calib.ARL0.target)
abline(h = calib.limit)
abline(v = calib.ARL0.target)
print(calib.limit)

# Evaluation

start.time = proc.time()
calib.eval.result = evaluate.unconditional(
  m = calib.m,
  n = calib.n,
  limit = calib.limit,
  upper_limit = calib.upper_limit,
  shifts = calib.eval.shifts,
  distribution_key = calib.eval.dist,
  distribution_parameters = calib.eval.dist.params,
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  nsim = calib.eval.nsim,
  run_length_cap = calib.cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (calib.eval.result)

# Save results

filename =  paste(c(calib.monitor_stat,
                    format(calib.ARL0.target, nsmall = 0),
                    format(calib.m, nsmall = 0),
                    format(calib.n, nsmall = 0),
                    format(calib.nsim, nsmall = 0),
                    format(calib.seed, nsmall = 0)), collapse = "_")

basepath = paste(c("results/calibration_results/", filename, ".RData"), collapse = "")

save(calib.m,
     calib.n,
     calib.ARL0.target,
     calib.monitor_stat,
     calib.monitor_stat.params,
     calib.nsim,
     calib.limits_seq,
     calib.upper_limit,
     calib.eval.dist,
     calib.eval.dist.params,
     calib.eval.nsim,
     calib.eval.shifts,
     calib.cap,
     calib.seed,
     calib.rls,
     calib.arls,
     calib.limit,
     calib.eval.result,
     file = basepath)
