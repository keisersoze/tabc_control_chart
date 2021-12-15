# Start parameters

calib.seed = 45
turbostat.setseed(calib.seed)
calib.m = 100
calib.n = 5

calib.nsim = 10000

# npc tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
# calib.limits_seq = inverse(seq(2, 6, 0.001))

# npc fisher
# calib.limits_seq = seq(-4.5, -5.9, -0.001)
calib.limits_seq = seq(-9.5, -12, -0.001)
# calib.limits_seq = seq(-7, -8.2, -0.001)
# calib.limits_seq = seq(-15, -18, -0.001)
# calib.limits_seq = seq(-2, -13.2, -0.0005)

# npc liptak
# calib.limits_seq = seq(1.02, 1.002, -0.0001)

# lepage
# calib.limits_seq = seq(9, 11, 0.001)

# cucconi
# calib.limits_seq = seq(4.2, 5.7, 0.001)

# van_de_warden
# calib.limits_seq = seq(4, 5.6, 0.001)

# mann_whitney
# calib.limits_seq = seq(400,430,1)

calib.is_upper_limit = FALSE

calib.ARL0.target = 500

calib.monitor_stat = "npc"
# calib.monitor_stat.params = list(statistic="lepage")
calib.monitor_stat.params = list(
  "statistics"= list(
    "centered_wilcoxon_rank_sum",
    "van_de_warden"
  ),
  "permutation_distributions"=list(
    compute_permutation_distribution("centered_wilcoxon_rank_sum", calib.m, calib.n, 10000),
    compute_permutation_distribution("van_de_warden", calib.m, calib.n, 10000)
  ),
  "tails"=list(
    "two_sided",
    "two_sided"
  ),
  "combining_function"="fisher"
)
calib.chart_id="npc_wilcoxon_van_de_warden"

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 50000

calib.eval.dist = "norm"
calib.eval.dist.params = list("mean"= 0, "sd"= 1)
calib.eval.nsim = calib.nsim
calib.eval.location_shifts = seq(0, 1, 0.1)
calib.eval.scale_multipliers = c(1)
calib.eval.metrics = c("mean", "sd")

# End parameters
