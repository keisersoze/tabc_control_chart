
library(turbostat)

# Calibration parameters

calib.seed = 47631
calib.reference_sample = rnorm(100)
calib.n = 5

calib.ARL0.target = 370

calib.monitor_stat = "difference_of_means"
calib.monitor_stat.params = list()

calib.nsim = 10000
calib.is_upper_limit = FALSE

calib.eval.nsim = 10000
calib.eval.cap = 25000
calib.eval.shifts = seq(0, 1, 0.1)

# Calibration script

turbostat.setseed(calib.seed)

start.time = proc.time()
calib.limit = calibrate.conditional(
  reference_sample = calib.reference_sample,
  n = calib.n,
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  target_ARL = calib.ARL0.target,
  is_upper_limit = calib.is_upper_limit,
  nsim = calib.nsim
)

duration.time = proc.time() - start.time
print (duration.time)
print(calib.limit)


start.time = proc.time()
calib.eval.result = evaluate.conditional(
  reference_sample = calib.reference_sample,
  n = calib.n,
  limit = calib.limit,
  is_upper_limit = calib.is_upper_limit,
  shifts = calib.eval.shifts,
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  nsim = calib.eval.nsim,
  run_length_cap = calib.eval.cap
)
duration.time = proc.time() - start.time
print(duration.time)
print (calib.eval.result)

# Save results

# filename =  paste(c(calib.monitor_stat,
#                     format(calib.ARL0.target, nsmall = 0),
#                     format(calib.m, nsmall = 0),
#                     format(calib.n, nsmall = 0),
#                     format(calib.nsim, nsmall = 0),
#                     format(calib.seed, nsmall = 0)), collapse = "_")
#
# basepath = paste(c("results/calibration_results/n15/", filename, ".RData"), collapse = "")
#
# save(calib.m,
#      calib.n,
#      calib.ARL0.target,
#      calib.monitor_stat,
#      calib.monitor_stat.params,
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
