library(turbostat)

# Evaluation parameters

eval.calibrations = c("results/calibration_results/a_370_100_10_50_34256.RData",
                      "results/calibration_results/c_370_100_10_50_34256.RData")

eval.nsim = 10
eval.shifts = c(0, 0.25, 0.5, 0.75, 1)
eval.dist = "normalized_rate_one_exponential"
eval.dist.params = list()
eval.m = 100
eval.n = 10
eval.ARL0.target = 370
eval.seed = 4637

# Evaluation script

turbostat.setseed(calib.seed)

eval.charts = rep(NA, length(eval.calibrations))

for (i in seq_along(eval.calibrations)){
  load(eval.calibrations[i])
  eval.charts[i] = calib.monitor_stat
}

arl_table = matrix(nrow=length(eval.shifts),ncol=(length(eval.charts)))
rownames(arl_table) = eval.shifts
colnames(arl_table) = eval.charts

sd_table = matrix(nrow=length(eval.shifts),ncol=(length(eval.charts)))
rownames(sd_table) = eval.shifts
colnames(sd_table) = eval.charts

for (i in seq_along(eval.calibrations)){
  load(eval.calibrations[i])

  print(sprintf("Processing chart %s", calib.monitor_stat))

  # Prevent mistakes
  if (eval.m != calib.m){
    stop(sprintf("Chart %s has been calibrated for m=%i and not m=%i !",
                 calib.monitor_stat,
                 calib.m,
                 eval.m))
  }
  if (eval.n != calib.n){
    stop(sprintf("Chart %s has been calibrated for n=%i and not n=%i !",
                 calib.monitor_stat,
                 calib.n,
                 eval.n))
  }
  if (eval.ARL0.target != calib.ARL0.target){
    stop(sprintf("Chart %s has been calibrated for ARL0=%i and not ARL0=%i !",
                 calib.monitor_stat,
                 calib.ARL0.target,
                 eval.ARL0.target))
  }

  # Evaluation
  start.time = proc.time()
  result = evaluate.unconditional(
    m = calib.m,
    n = calib.n,
    LCL = calib.LCL,
    shifts = eval.shifts,
    distribution_key = eval.dist,
    distribution_parameters = eval.dist.params,
    monitoring_statistic_key = calib.monitor_stat,
    monitoring_statistic_parameters = calib.monitor_stat.params,
    nsim = eval.nsim,
    run_length_cap = calib.cap
  )
  duration.time = proc.time() - start.time
  print(duration.time)
  for (j in seq_along(eval.shifts)){
    arl_table[j,i] = result$ARLs[j]
    sd_table[j,i] = result$SD[j]
  }
  print(result)
}

filename =  paste(c(format(eval.ARL0.target, nsmall = 0),
                    format(eval.m, nsmall = 0),
                    format(eval.n, nsmall = 0),
                    format(eval.nsim, nsmall = 0),
                    format(eval.seed, nsmall = 0)), collapse = "_")

basepath = paste(c("results/evaluation_results/", filename, ".RData"), collapse = "")

save(eval.calibrations,
     eval.m,
     eval.n,
     eval.dist,
     eval.dist.params,
     eval.shifts,
     eval.seed,
     eval.charts,
     eval.ARL0.target,
     arl_table,
     sd_table,
     file = basepath)
