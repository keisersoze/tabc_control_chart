# Start parameters

calib.seed = 8989
turbostat.setseed(calib.seed)
calib.m = 100
calib.n = 5

calib.nsim = 50000

# lepage
calib.limits_seq = seq(10.7, 11.6, 0.001)


calib.is_upper_limit = TRUE

calib.ARL0.target = 500

calib.monitor_stat = "simple_statistic"
calib.monitor_stat.params = list(statistic="lepage")

calib.chart_id="lepage"

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
