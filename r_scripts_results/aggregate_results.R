aggregate.calibrations = c("results/calibration_results/standardized_laplace/difference_of_means_laplace_250_100_10_10000_47631.RData",
                          "results/calibration_results/standardized_laplace/mann-whitney_laplace_250_100_10_10000_47631.RData")



aggregate.m = 100
aggregate.n = 10
aggregate.ARL0.target = 250
aggregate.dist = "laplace"
aggregate.dist.params = list("mean" = 0 , "sd" =  1)
aggregate.shifts = seq(0, 1, 0.1)
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
