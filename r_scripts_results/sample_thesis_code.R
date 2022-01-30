library(npcharts)
calib.seed = 8989
npcharts.setseed(calib.seed)

# Calibration parameters
calib.m = 100
calib.n = 5
calib.monitor_stat.type= "npc"
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
calib.is_upper_limit = FALSE
calib.limits_seq = seq(-7, -9.2, -0.001)
calib.ARL0.target = 500
calib.chart_id="npc_wilcoxon_klotz"
calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)
calib.nsim = 10000
calib.cap = 50000

start.time = proc.time()

# Calibration
calib.rls = calibrate.unconditional(
  m = calib.m,
  n = calib.n,
  distribution_key = calib.dist,
  distribution_parameters = calib.dist.params,
  monitoring_statistic_type = calib.monitor_stat.type,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  limits_seq = calib.limits_seq,
  is_upper_limit = calib.is_upper_limit,
  nsim = calib.nsim,
  run_length_cap = calib.cap
)
calib.arls = colMeans(calib.rls)
plot(calib.limits_seq ~ calib.arls, pch=20, cex=0.02, xlab="ARL", ylab ="UCL")
afn = approxfun(calib.arls,calib.limits_seq, ties = mean)
curve(afn, add=TRUE, col="red")
calib.limit = afn(calib.ARL0.target)
abline(h = calib.limit)
abline(v = calib.ARL0.target)

# Evaluation parameters
calib.eval.dist = "laplace"
calib.eval.dist.params = list("location"= 0, "scale"= 1)
calib.eval.nsim = calib.nsim

# Evaluation
if (calib.is_upper_limit){
  limits = list("ucl"=calib.limit)
} else {
  limits = list("lcl"=calib.limit)
}
res = evaluate.unconditional(
  m = calib.m,
  n = calib.n,
  limits = limits,
  location_shift = 0,
  scale_multiplier = 1,
  distribution_key = calib.eval.dist,
  distribution_parameters = calib.eval.dist.params,
  monitoring_statistic_type = calib.monitor_stat.type,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  nsim = calib.eval.nsim,
  run_length_cap = calib.cap
)
print(mean(res$run_lengths))

duration.time = proc.time() - start.time
print(duration.time)
