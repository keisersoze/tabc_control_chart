logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

library(turbostat)

# Calibration parameters

calib.seed = 45
calib.m = 100
calib.n = 10

calib.ARL0.target = 250

calib.monitor_stat = "klotz_statistic"
calib.monitor_stat.params = list()

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 25000

calib.nsim = 10000
calib.limits_seq = seq(17, 19.5, 0.001)
calib.is_upper_limit = TRUE


calib.eval.dist = "cauchy"
calib.eval.dist.params = list("location"=0, "scale"= 1)
calib.eval.nsim = calib.nsim
calib.eval.scale_multipliers = seq(1, 1.2, 0.1)

# Calibration script

turbostat.setseed(calib.seed)

start.time = proc.time()
calib.rls = calibrate.unconditional(
  m = calib.m,
  n = calib.n,
  distribution_key = calib.dist,
  distribution_parameters = calib.dist.params,
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  limits_seq = calib.limits_seq,
  is_upper_limit = calib.is_upper_limit,
  nsim = calib.nsim,
  run_length_cap = calib.cap
)

duration.time = proc.time() - start.time
print (duration.time)

calib.arls = colMeans(calib.rls)
plot(calib.limits_seq ~ calib.arls, pch=20, cex=0.02)
afn = approxfun(calib.arls,calib.limits_seq, ties = mean)
curve(afn, add=TRUE, col="red")
calib.limit = afn(calib.ARL0.target)
abline(h = calib.limit)
abline(v = calib.ARL0.target)
print(calib.limit)

# Evaluation


start.time = proc.time()
calib.eval.result = evaluate.unconditional.scale(
  m = calib.m,
  n = calib.n,
  limit = calib.limit,
  is_upper_limit = calib.is_upper_limit,
  scale_multipliers = calib.eval.scale_multipliers,
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

# filename =  paste(c(calib.monitor_stat,
#                     calib.dist,
#                     format(calib.ARL0.target, nsmall = 0),
#                     format(calib.m, nsmall = 0),
#                     format(calib.n, nsmall = 0),
#                     format(calib.nsim, nsmall = 0),
#                     format(calib.seed, nsmall = 0)), collapse = "_")

# basepath = paste(c("results/calibration_results/standard_normal/", filename, ".RData"), collapse = "")

# basepath = paste(c("results/calibration_results/prefinal/", filename, ".RData"), collapse = "")
#
# save(calib.m,
#      calib.n,
#      calib.ARL0.target,
#      calib.monitor_stat,
#      calib.monitor_stat.params,
#      calib.dist,
#      calib.dist.params,
#      calib.nsim,
#      calib.limits_seq,
#      calib.is_upper_limit,
#      calib.eval.dist,
#      calib.eval.dist.params,
#      calib.eval.nsim,
#      calib.eval.shifts,
#      calib.cap,
#      calib.seed,
#      calib.rls,
#      calib.arls,
#      calib.limit,
#      calib.eval.result,
#      file = basepath)
