aggregate.calibrations = c("results/calibration_results/standard_normal/difference_of_means_norm_250_100_10_10000_47631.RData",
                           "results/calibration_results/standard_normal/mann-whitney_norm_250_100_10_10000_47631.RData",
                           "results/calibration_results/standard_normal/tac_obs_stat_norm_250_100_10_10000_47631.RData")



aggregate.m = 100
aggregate.n = 10
aggregate.ARL0.target = 250
aggregate.dist = "norm"
aggregate.dist.params = list("mean" = 0 , "sd" =  1)
aggregate.shifts = seq(0, 1, 0.1)
aggregate.nsim = 10000
aggregate.charts = rep(NA, length(aggregate.calibrations))

for (i in seq_along(aggregate.calibrations)){
  load(aggregate.calibrations[i])
  aggregate.charts[i] = calib.monitor_stat
}


arl_table = matrix(nrow=length(aggregate.shifts),ncol=(length(aggregate.charts)))
rownames(arl_table) = aggregate.shifts
colnames(arl_table) = aggregate.charts

sd_table = matrix(nrow=length(aggregate.shifts),ncol=(length(aggregate.charts)))
rownames(sd_table) = aggregate.shifts
colnames(sd_table) = aggregate.charts

for (i in seq_along(aggregate.calibrations)){
  load(aggregate.calibrations[i])

  print(sprintf("Processing chart %s", calib.monitor_stat))

  # Prevent mistakes
  if (aggregate.m != calib.m){
    stop(sprintf("Chart %s has been calibrated for m=%i and not m=%i !",
                 calib.monitor_stat,
                 calib.m,
                 aggregate.m))
  }
  if (aggregate.n != calib.n){
    stop(sprintf("Chart %s has been calibrated for n=%i and not n=%i !",
                 calib.monitor_stat,
                 calib.n,
                 aggregate.n))
  }
  if (aggregate.ARL0.target != calib.ARL0.target){
    stop(sprintf("Chart %s has been calibrated for ARL0=%i and not ARL0=%i !",
                 calib.monitor_stat,
                 calib.ARL0.target,
                 aggregate.ARL0.target))
  }
  if (aggregate.nsim != calib.nsim){
    stop(sprintf("Chart %s has been calibrated with nsim=%i and not for nsim=%i !",
                 calib.monitor_stat,
                 calib.nsim,
                 aggregate.nsim))
  }
  if (aggregate.dist != calib.dist){
    stop(sprintf("Chart %s has been calibrated for distribution \"%s\" and not for distribution \"%s\" !",
                 calib.monitor_stat,
                 calib.dist,
                 aggregate.dist))
  }

  for (j in seq_along(aggregate.shifts)){
    arl_table[j,i] = calib.eval.result$ARLs[j]
    sd_table[j,i] = calib.eval.result$SD[j]
  }
}

print(arl_table)


filename =  paste(c(format(aggregate.ARL0.target, nsmall = 0),
                    aggregate.dist,
                    format(aggregate.m, nsmall = 0),
                    format(aggregate.n, nsmall = 0),
                    format(aggregate.nsim, nsmall = 0)), collapse = "_")

basepath = paste(c("results/evaluation_results/idea/", filename, ".RData"), collapse = "")

save(aggregate.calibrations,
     aggregate.m,
     aggregate.n,
     aggregate.dist,
     aggregate.dist.params,
     aggregate.shifts,
     aggregate.charts,
     aggregate.ARL0.target,
     arl_table,
     sd_table,
     file = basepath)
