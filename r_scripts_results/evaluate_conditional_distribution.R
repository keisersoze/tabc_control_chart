library(turbostat)

# Evaluation parameters

# eval.calibrations = c("results_new/calibration/normal/wilcoxon_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/van_de_warden_pvalue_norm_370_100_5_10000_45.RData",
#                       "results_new/calibration/normal/npc_percentiles_42_46_norm_370_100_5_10000_42.RData",
#                       "results_new/calibration/normal/npc_wilcoxon_van_de_warden_norm_370_100_5_30000_45.RData")
eval.calibration = c("results_new/calibration/normal/cucconi_norm_500_100_5_50000_8989.RData")

# eval.calibrations = c("results/calibration_results/prefinal/mann-whitney_250_100_10_10000_324.RData",
#                       "results/calibration_results/prefinal/sum-of-sings_250_100_10_10000_324.RData")

eval.nsim = 50000
# eval.location_shifts = seq(0, 1, 0.1)
eval.dist = "norm"
eval.dist.params = list(mean=0, sd=1)
eval.m = 100
eval.n = 5
eval.ARL0.target = 500
eval.seed = 4367

# Evaluation script

turbostat.setseed(eval.seed)

crl_table <- as.list(numeric(7*7))
dim(crl_table) <- c(7,7)


for(i in 1:7) {
  for (j in 1:7) {
    crl_table[[i,j]] = list()
  }
}

load(eval.calibration)

res = evaluate.unconditional2(
  m = eval.m,
  n = eval.n,
  limit = calib.limit,
  is_upper_limit = calib.is_upper_limit,
  location_shift = 0,
  scale_multiplier = 1,
  distribution_key = eval.dist,
  distribution_parameters = eval.dist.params,
  monitoring_statistic_key = calib.monitor_stat,
  monitoring_statistic_parameters = calib.monitor_stat.params,
  nsim = eval.nsim,
  run_length_cap = calib.cap
)

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


