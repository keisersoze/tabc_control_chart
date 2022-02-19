# Start parameters

calib.seed = 466888
npcharts.setseed(calib.seed)
calib.m = 100
calib.n = 5

calib.nsim = 50000

# npc tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
#calib.limits_seq = inverse(seq(4, 6, 0.001))

# npc fisher
# calib.limits_seq = seq(-4.5, -5.9, -0.001)
calib.limits_seq = seq(-8.6, -9.0, -0.0005)
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
    compute_permutation_distribution("centered_wilcoxon_rank_sum", calib.m, calib.n, 15000),
    compute_permutation_distribution("klotz_statistic", calib.m, calib.n, 15000)
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
calib.eval.scale_multipliers = c(1, 1.25, 1.5, 1.75)
calib.eval.metrics = c("mean", "sd")

# End parameters
