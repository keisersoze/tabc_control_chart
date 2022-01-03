library(turbostat)

# Evaluation parameters

# eval.calibrations = c("results_new/calibration/normal/wilcoxon_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/van_de_warden_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/npc_percentiles_42_46_norm_370_100_5_10000_42.RData",
#                       "results_new/calibration/normal/npc_wilcoxon_van_de_warden_norm_370_100_5_30000_45.RData")
eval.calibrations = c("results_new/calibration/normal/cucconi_norm_500_100_5_50000_8989.RData",
                      "results_new/calibration/normal/lepage_norm_500_100_5_50000_8989.RData",
                      "results_new/calibration/normal/npc_lepage_cucconi_norm_500_100_5_50000_45.RData",
                      "results_new/calibration/normal/npc_wilcoxon_klotz_norm_500_100_5_50000_8989.RData")

# eval.calibrations = c("results/calibration_results/prefinal/mann-whitney_250_100_10_10000_324.RData",
#                       "results/calibration_results/prefinal/sum-of-sings_250_100_10_10000_324.RData")

eval.nsim = 50000
eval.location_shifts = c(0, 0.25, 0.5, 1.0, 1.5, 2.0)
eval.scale_multipliers = c(1, 1.25, 1.5, 1.75)
# eval.location_shifts = seq(0, 1, 0.1)
eval.dist = "mirrored_centered_gamma_with_shape_equal_four"
eval.dist.params = list()
eval.m = 100
eval.n = 5
eval.ARL0.target = 500
eval.seed = 6476

# Evaluation script

turbostat.setseed(eval.seed)

n_shifts = length(eval.location_shifts)
n_scale_multipliers = length(eval.scale_multipliers)
nrow = n_shifts * n_scale_multipliers
ncol = length(eval.calibrations) + 2

col_names = rep(NA, ncol)
col_names[1] = "location_shift"
col_names[2] = "scale_multiplier"

for (i in seq_along(eval.calibrations)){
  load(eval.calibrations[i])
  col_names[i + 2] = calib.chart_id
}

arl_table = matrix(nrow=nrow,ncol=ncol)
colnames(arl_table) = col_names

sd_table = matrix(nrow=nrow,ncol=ncol)
colnames(sd_table) = col_names

quantile_tables.zerofive = matrix(nrow=nrow,ncol=ncol)
colnames(quantile_tables.zerofive) = col_names

quantile_tables.five = matrix(nrow=nrow,ncol=ncol)
colnames(quantile_tables.five) = col_names

quantile_tables.ninetyfive = matrix(nrow=nrow,ncol=ncol)
colnames(quantile_tables.ninetyfive) = col_names

for (k in seq_along(eval.calibrations)){
  load(eval.calibrations[k])

  print(sprintf("Processing chart %s", calib.chart_id))

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

  for (i in seq_along(eval.scale_multipliers)){
    scale_multiplier = eval.scale_multipliers[i]
    for (j in seq_along(eval.location_shifts)){
      location_shift = eval.location_shifts[j]
      print(sprintf("Processing shift %f and scale multiplier %f", location_shift, scale_multiplier))
      arl_table[((i-1) * n_shifts) + j, 1] = location_shift
      arl_table[((i-1) * n_shifts) + j, 2] = scale_multiplier
      sd_table[((i-1) * n_shifts) + j, 1] = location_shift
      sd_table[((i-1) * n_shifts) + j, 2] = scale_multiplier
      arls = evaluate.unconditional(
        m = eval.m,
        n = eval.n,
        limit = calib.limit,
        is_upper_limit = calib.is_upper_limit,
        location_shift =location_shift,
        scale_multiplier = scale_multiplier,
        distribution_key = eval.dist,
        distribution_parameters = eval.dist.params,
        monitoring_statistic_key = calib.monitor_stat,
        monitoring_statistic_parameters = calib.monitor_stat.params,
        nsim = eval.nsim,
        run_length_cap = calib.cap
      )
      arl_table[((i-1) * n_shifts) + j, 2 + k] = mean(arls)
      sd_table[((i-1) * n_shifts) + j, 2 + k] = sd(arls)
      quantiles = as.numeric(quantile(arls, probs=c(0.05, 0.5, 0.95)))
      quantile_tables.zerofive[((i-1) * n_shifts) + j, 2 + k] = quantiles[1]
      quantile_tables.five[((i-1) * n_shifts) + j, 2 + k] = quantiles[2]
      quantile_tables.ninetyfive[((i-1) * n_shifts) + j, 2 + k] = quantiles[3]
    }
  }

  duration.time = proc.time() - start.time
  print(duration.time)
}

filename =  paste(c(format(eval.ARL0.target, nsmall = 0),
                    eval.dist,
                    format(eval.m, nsmall = 0),
                    format(eval.n, nsmall = 0),
                    format(eval.nsim, nsmall = 0),
                    format(eval.seed, nsmall = 0)), collapse = "_")

basepath = paste(c("results_new/evaluation/location_scale/", filename, ".RData"), collapse = "")

save(eval.calibrations,
     eval.m,
     eval.n,
     eval.dist,
     eval.dist.params,
     eval.location_shifts,
     eval.scale_multipliers,
     eval.seed,
     eval.ARL0.target,
     arl_table,
     sd_table,
     quantile_tables.zerofive,
     quantile_tables.five,
     quantile_tables.ninetyfive,
     file = basepath)
