logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

library(npcharts)

# Start parameters

calib.seed = 8989
npcharts.setseed(calib.seed)
calib.m = 100
calib.n = 5

calib.nsim = 10000

# npc tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
#calib.limits_seq = inverse(seq(4, 6, 0.001))

# npc fisher
# calib.limits_seq = seq(-4.5, -5.9, -0.001)
calib.limits_seq = seq(-7, -9.2, -0.001)
# calib.limits_seq = seq(-7, -8.2, -0.001)
# calib.limits_seq = seq(-15, -18, -0.001)
# calib.limits_seq = seq(-2, -13.2, -0.0005)

# npc liptak
# calib.limits_seq = seq(1.02, 1.002, -0.0001)

calib.is_upper_limit = FALSE

calib.ARL0.target = 500

calib.monitor_stat = "npc"
calib.monitor_stat.params = list(
  "statistics"= list(
    "centered_wilcoxon_rank_sum",
    "klotz_statistic"

  ),
  "permutation_distributions"=list(
    compute_permutation_distribution("centered_wilcoxon_rank_sum", calib.m, calib.n, 10000),
    compute_permutation_distribution("klotz_statistic", calib.m, calib.n, 10000)
  ),
  "tails"=list(
    "two_sided",
    "right"
  ),
  "combining_function"="fisher"
)
calib.chart_id="npc_wilcoxon_klotz"

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 50000

calib.eval.dist = "norm"
calib.eval.dist.params = list("mean"= 0, "sd"= 1)
calib.eval.nsim = calib.nsim
calib.eval.location_shifts = c(0, 0.25, 0.5, 1.0, 1.5, 2.0)
calib.eval.scale_multipliers = c(1, 1.25)
calib.eval.metrics = c("mean", "sd")

# End parameters

# Calibration

start.time = proc.time()
calib.rls = calibrate.unconditional(
  m = calib.m,
  n = calib.n,
  distribution_key = calib.dist,
  distribution_parameters = calib.dist.params,
  monitoring_statistic_type = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  limits_seq = calib.limits_seq,
  is_upper_limit = calib.is_upper_limit,
  nsim = calib.nsim,
  run_length_cap = calib.cap
)

duration.time = proc.time() - start.time
print (duration.time)

calib.arls = colMeans(calib.rls)
plot(calib.limits_seq ~ calib.arls, pch=20, cex=0.02, xlab="ARL", ylab ="UCL")
afn = approxfun(calib.arls,calib.limits_seq, ties = mean)
curve(afn, add=TRUE, col="red")
calib.limit = afn(calib.ARL0.target)
abline(h = calib.limit)
abline(v = calib.ARL0.target)
print(calib.limit)

# Evaluation

start.time = proc.time()
if (calib.is_upper_limit){
  limits = list("ucl"=calib.limit)
} else {
  limits = list("lcl"=calib.limit)
}
n_shifts = length(calib.eval.location_shifts)
n_scale_multipliers = length(calib.eval.scale_multipliers)
nrow = n_shifts * n_scale_multipliers
ncol = length(calib.eval.metrics) + 2
calib.eval.result_matrix = matrix(nrow=nrow,ncol=(ncol))
col_names = rep(NA, ncol)
col_names[1] = "location_shift"
col_names[2] = "scale_multiplier"
for (k in seq_along(calib.eval.metrics)){
  metric_func_key = calib.eval.metrics[k]
  col_names[k + 2] = metric_func_key
}
colnames(calib.eval.result_matrix) = col_names
for (i in seq_along(calib.eval.scale_multipliers)){
  scale_multiplier = calib.eval.scale_multipliers[i]
  for (j in seq_along(calib.eval.location_shifts)){
    location_shift = calib.eval.location_shifts[j]
    calib.eval.result_matrix[((i-1) * n_shifts) + j, 1] = location_shift
    calib.eval.result_matrix[((i-1) * n_shifts) + j, 2] = scale_multiplier
    res = evaluate.unconditional(
      m = calib.m,
      n = calib.n,
      limits = limits,
      location_shift =location_shift,
      scale_multiplier = scale_multiplier,
      distribution_key = calib.eval.dist,
      distribution_parameters = calib.eval.dist.params,
      monitoring_statistic_type = calib.monitor_stat,
      monitoring_statistic_parameters = calib.monitor_stat.params,
      nsim = calib.eval.nsim,
      run_length_cap = calib.cap
    )
    arls = res$run_lengths
    for (k in seq_along(calib.eval.metrics)){
      metric_func = get(calib.eval.metrics[k])
      calib.eval.result_matrix[((i-1) * n_shifts) + j, k + 2] = metric_func(arls)
    }
  }
}

duration.time = proc.time() - start.time
print(duration.time)
print(calib.eval.result_matrix)

# Save results

filename =  paste(c(calib.chart_id,
                    calib.dist,
                    format(calib.ARL0.target, nsmall = 0),
                    format(calib.m, nsmall = 0),
                    format(calib.n, nsmall = 0),
                    format(calib.nsim, nsmall = 0),
                    format(calib.seed, nsmall = 0)), collapse = "_")

# basepath = paste(c("results/calibration_results/standard_normal/", filename, ".RData"), collapse = "")

# basepath = paste(c("results_new/calibration/normal/", filename, ".RData"), collapse = "")
#
# save(calib.m,
#      calib.n,
#      calib.ARL0.target,
#      calib.chart_id,
#      calib.monitor_stat,
#      calib.monitor_stat.params,
#      calib.dist,
#      calib.dist.params,
#      calib.nsim,
#      calib.limits_seq,
#      calib.is_upper_limit,
#      calib.cap,
#      calib.seed,
#      calib.rls,
#      calib.arls,
#      calib.limit,
#      calib.eval.dist,
#      calib.eval.dist.params,
#      calib.eval.nsim,
#      calib.eval.location_shifts,
#      calib.eval.scale_multipliers,
#      calib.eval.metrics,
#      calib.eval.result_matrix,
#      file = basepath)
