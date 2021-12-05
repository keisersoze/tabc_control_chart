logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

library(turbostat)

# Start parameters

calib.seed = 45
calib.m = 100
calib.n = 5

calib.nsim = 10000

# npc tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
calib.limits_seq = inverse(seq(2, 5.8, 0.001))

# npc fisher
# calib.limits_seq = seq(-2, -5, -0.001)
# calib.limits_seq = seq(-2, -11, -0.001)
# calib.limits_seq = seq(-2, -13.2, -0.0005)

# npc liptak
# calib.limits_seq = seq(1.02, 1.002, -0.0001)

# lepage
# calib.limits_seq = seq(2, 11, 0.001)

# cucconi
# calib.limits_seq = seq(2, 5.7, 0.001)

# van_de_warden
# calib.limits_seq = seq(4, 5.6, 0.001)

# mann_whitney
# calib.limits_seq = seq(400,430,1)

calib.is_upper_limit = FALSE

calib.ARL0.target = 370

calib.monitor_stat = "npc"
# calib.monitor_stat.params = list(statistic="mann_whitney")
calib.monitor_stat.params = list(
  "statistics"= list(
    "centered_wilcoxon_rank_sum",
    "van_de_warden"
  ),
  "permutation_distributions"=list(
    compute_permutation_distribution("centered_wilcoxon_rank_sum", calib.m, calib.n, 10000),
    compute_permutation_distribution("van_de_warden", calib.m, calib.n, 10000),
  ),
  "tails"=list(
    "two_sided",
    "two_sided"
  ),
  "combining_function"="tippet"
)

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 25000

calib.eval.dist = "norm"
calib.eval.dist.params = list("mean"= 0, "sd"= 1)
calib.eval.nsim = calib.nsim
calib.eval.location_shifts = seq(0, 1, 0.1)
calib.eval.scale_multipliers = c(1)
calib.eval.metrics = c("mean", "sd")

# End parameters

# Calibration

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
nrow = length(calib.eval.location_shifts) * length(calib.eval.scale_multipliers)
ncol = length(calib.eval.metrics) + 2
result_matrix = matrix(nrow=nrow,ncol=(ncol))
col_names = rep(NA, ncol)
col_names[1] = "location_shift"
col_names[2] = "scale_multiplier"
for (k in seq_along(calib.eval.metrics)){
  metric_func_key = calib.eval.metrics[k]
  col_names[k + 2] = metric_func_key
}
colnames(result_matrix) = col_names
for (i in seq_along(calib.eval.scale_multipliers)){
  scale_multiplier = calib.eval.scale_multipliers[i]
  for (j in seq_along(calib.eval.location_shifts)){
    location_shift = calib.eval.location_shifts[j]
    result_matrix[i * j, 1] = location_shift
    result_matrix[i * j, 2] = scale_multiplier
    arls = evaluate.unconditional(
      m = calib.m,
      n = calib.n,
      limit = calib.limit,
      is_upper_limit = calib.is_upper_limit,
      location_shift =location_shift,
      scale_multiplier = scale_multiplier,
      distribution_key = calib.eval.dist,
      distribution_parameters = calib.eval.dist.params,
      monitoring_statistic_key = calib.monitor_stat,
      monitoring_statistic_parameters = calib.monitor_stat.params,
      nsim = calib.eval.nsim,
      run_length_cap = calib.cap
    )
    for (k in seq_along(calib.eval.metrics)){
      metric_func = get(calib.eval.metrics[k])
      result_matrix[i * j, k + 2] = metric_func(arls)
    }
  }
}

duration.time = proc.time() - start.time
print(duration.time)
print(result_matrix)

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
