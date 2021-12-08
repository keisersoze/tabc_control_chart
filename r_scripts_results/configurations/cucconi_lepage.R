# Start parameters

calib.seed = 45
turbostat.setseed(calib.seed)
calib.m = 50
calib.n = 5

calib.nsim = 10000

# npc tippet
# calib.limits_seq = inverse(seq(2, 9.5, 0.001))
# calib.limits_seq = inverse(seq(2, 6, 0.001))

# npc fisher
# calib.limits_seq = seq(-2, -5, -0.001)
calib.limits_seq = seq(-5, -12, -0.001)
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

calib.ARL0.target = 500

calib.monitor_stat = "npc"
# calib.monitor_stat.params = list(statistic="mann_whitney")
calib.monitor_stat.params = list(
  "statistics"= list(
    "cucconi",
    "lepage"
  ),
  "permutation_distributions"=list(
    compute_permutation_distribution("cucconi", calib.m, calib.n, 10000),
    compute_permutation_distribution("lepage", calib.m, calib.n, 10000)
  ),
  "tails"=list(
    "two_sided",
    "two_sided"
  ),
  "combining_function"="fisher"
)

calib.dist = "norm"
calib.dist.params = list("mean" = 0 , "sd" =  1)

calib.cap = 25000

calib.eval.dist = "norm"
calib.eval.dist.params = list("mean"= 0, "sd"= 1)
calib.eval.nsim = calib.nsim
calib.eval.location_shifts = c(0, 0.25, 0.5, 1.0, 1.5, 2.0)
calib.eval.scale_multipliers = c(1, 1.25, 1.5)
calib.eval.metrics = c("mean", "sd")

# End parameters

# location_shift scale_multiplier     mean           sd
# [1,]           0.00             1.00 502.5348 1184.4615958
# [2,]           0.25             1.00 291.2945  680.3964761
# [3,]           0.50             1.00  88.1397  232.0738275
# [4,]           1.00             1.00   8.3561   13.5820448
# [5,]           1.50             1.00   2.1934    2.0773608
# [6,]           2.00             1.00   1.2192    0.5642546
# [7,]           0.00             1.25  77.7813  133.2137578
# [8,]           0.25             1.25  58.8287   97.7551961
# [9,]           0.50             1.25  28.8957   45.4305626
# [10,]           1.00             1.25   6.6954    8.0166854
# [11,]           1.50             1.25   2.3784    2.0292918
# [12,]           2.00             1.25   1.3960    0.7981527
# [13,]           0.00             1.50  26.7453   35.6769549
# [14,]           0.25             1.50  22.1198   28.4065158
# [15,]           0.50             1.50  14.8241   19.4774766
# [16,]           1.00             1.50   5.4874    6.1793090
# [17,]           1.50             1.50   2.5033    2.1519415
# [18,]           2.00             1.50   1.5598    1.0105078
