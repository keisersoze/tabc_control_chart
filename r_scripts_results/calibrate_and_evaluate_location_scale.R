logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

library(turbostat)

# Start parameters

calib.seed = 45678
turbostat.setseed(calib.seed)
calib.m = 50
calib.n = 5

calib.nsim = 50000
# Tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
# calib.limits_seq = inverse(seq(2, 6.7, 0.001))
# Fisher
# calib.limits_seq = seq(-2, -5, -0.001)
# calib.limits_seq = seq(-2, -13.2, -0.0005)
# calib.limits_seq = seq(-2, -13.2, -0.0005)
# Liptak
calib.limits_seq = seq(1.5, 1.0102, -0.0001)


calib.is_upper_limit = FALSE

calib.ARL0.target = 500

calib.monitor_stat = "npc"
# calib.monitor_stat.params = list()
calib.monitor_stat.params = list(
  "statistics"= list(
    "lepage",
    "cucconi"
  ),
  "permutation_distributions"=list(
    compute_permutation_distribution("cucconi", calib.m, calib.n, 500000),
    compute_permutation_distribution("lepage", calib.m, calib.n, 500000)
  ),
  "tails"=list(
    "two_sided",
    "two_sided"
  ),
  "combining_function"="liptak"
)

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 50000

calib.eval.dist = "laplace"
calib.eval.dist.params = list("location"= 0, "scale"= 1)
calib.eval.nsim = calib.nsim
# calib.eval.location_shift_scale_multiplier_list = list(c(0.25,1.25), c(0.5,1.5))
calib.eval.location_shift_scale_multiplier_list = list(c(0,1), c(0.25, 1), c(0.5, 1), c(0.75, 1), c(1, 1), c(0, 1.25), c(0, 1.5), c(0.25,1.25), c(0.5,1.5))
# calib.eval.location_shift_scale_multiplier_list = list(c(0,1), c(-0.25, 1), c(-0.5, 1), c(-0.75, 1), c(-1, 1), c(0, 0.75), c(0, 0.5))
# calib.eval.location_shift_scale_multiplier_list = list(c(0,1), c(0, 1.1), c(0, 1.2), c(0, 1.3), c(0, 1.4))
# calib.eval.location_shift_scale_multiplier_list = list(c(0,1), c(0.25, 1), c(0.5, 1), c(0, 0.9), c(0, 0.8), c(0, 0.7), c(0, 0.6), c(0, 0.5))

# End parameters

# Calibration

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
calib.eval.result = evaluate.unconditional.location_scale(
  m = calib.m,
  n = calib.n,
  limit = calib.limit,
  is_upper_limit = calib.is_upper_limit,
  location_scale_changes = calib.eval.location_shift_scale_multiplier_list,
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
