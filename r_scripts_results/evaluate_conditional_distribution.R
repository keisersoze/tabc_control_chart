library(npcharts)

# Evaluation parameters

# eval.calibrations = c("results_new/calibration/normal/wilcoxon_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/van_de_warden_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/npc_percentiles_42_46_norm_370_100_5_10000_42.RData",
#                       "results_new/calibration/normal/npc_wilcoxon_van_de_warden_norm_370_100_5_30000_45.RData")

# eval.calibrations = c("results_new/calibration/normal/cucconi_norm_500_100_5_50000_8989.RData",
#                       "results_new/calibration/normal/lepage_norm_500_100_5_50000_8989.RData",
#                       "results_new/calibration/normal/npc_lepage_cucconi_norm_500_100_5_50000_45.RData",
#                       "results_new/calibration/normal/npc_wilcoxon_klotz_norm_500_100_5_50000_8989.RData")

eval.calibration = c("results_new/calibration/normal/van_de_warden_pvalue_norm_370_100_5_10000_45.RData")

eval.nsim = 50000
eval.dist = "laplace"
eval.dist.params = list(location=0, scale=1/sqrt(2))
eval.m = 100
eval.n = 5
eval.ARL0.target = 370
eval.seed = 32

# Evaluation script

npcharts.setseed(eval.seed)

crl_table <- as.list(numeric(7*7))
dim(crl_table) <- c(7,7)


for(i in 1:7) {
  for (j in 1:7) {
    crl_table[[i,j]] = list()
  }
}

load(eval.calibration)

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

if (calib.is_upper_limit){
  limits = list("ucl"=calib.limit)
} else {
  limits = list("lcl"=calib.limit)
}

start.time = proc.time()
res = evaluate.unconditional(
  m = eval.m,
  n = eval.n,
  limits = limits,
  location_shift = 0,
  scale_multiplier = 1,
  distribution_key = eval.dist,
  distribution_parameters = eval.dist.params,
  monitoring_statistic_type = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  nsim = eval.nsim,
  run_length_cap = calib.cap
)
duration.time = proc.time() - start.time
print(duration.time)

rls = res$run_lengths
reference_sample_means = res$reference_sample_means
reference_sample_sds = res$reference_sample_sds

mean_quantiles = quantile(reference_sample_means, c(0.05, 0.25, 0.45, 0.55, 0.75, 0.95, 1))
sd_quantiles = quantile(reference_sample_sds, c(0.05, 0.25, 0.45, 0.55, 0.75, 0.95, 1))

for(i in 1:eval.nsim) {
  rl = rls[i]
  reference_sample_mean = reference_sample_means[i]
  reference_sample_sd = reference_sample_sds[i]
  col_idx = 1
  while (reference_sample_mean > mean_quantiles[col_idx]) {
    col_idx = col_idx + 1
  }
  row_idx = 1
  while (reference_sample_sd > sd_quantiles[row_idx]) {
    row_idx = row_idx + 1
  }
  crl_table[[row_idx, col_idx]] = append(crl_table[[row_idx, col_idx]], rl)
}

names = c("0-5", "5-25", "25-45", "45-55", "55-75", "75-95", "95-100")

carl_table = matrix(nrow=7,ncol=7)
colnames(carl_table) = names
rownames(carl_table) =  names

csd_table = matrix(nrow=7,ncol=7)
colnames(csd_table) = names
rownames(csd_table) =  names

proportion_table = matrix(nrow=7,ncol=7)
colnames(proportion_table) = names
rownames(proportion_table) =  names


for(i in 1:7) {
  for (j in 1:7) {
    carl_table[i,j] = mean(as.numeric(crl_table[[i,j]]))
    csd_table[i,j] = sd(as.numeric(crl_table[[i,j]]))
    proportion_table[i,j] = length(crl_table[[i,j]])/eval.nsim
  }
}

filename =  paste(c(calib.chart_id,
                    format(eval.ARL0.target, nsmall = 0),
                    eval.dist,
                    format(eval.m, nsmall = 0),
                    format(eval.n, nsmall = 0),
                    format(eval.nsim, nsmall = 0),
                    format(eval.seed, nsmall = 0)), collapse = "_")

# basepath = paste(c("results_new/evaluation/location/crl/laplace_v2/", filename, ".RData"), collapse = "")
#
# save(calib.chart_id,
#      eval.calibration,
#      eval.m,
#      eval.n,
#      eval.dist,
#      eval.dist.params,
#      eval.seed,
#      eval.ARL0.target,
#      carl_table,
#      csd_table,
#      proportion_table,
#      file = basepath)


