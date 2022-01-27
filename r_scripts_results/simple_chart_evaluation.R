shifts = seq(0,1,0.1)
nsim = 50000
calib.eval.dist = "norm"
calib.eval.dist.params = list("mean"= 0, "sd"= 1)

arls = rep(NA, length(shifts))

for (i in seq_along(shifts)) {
  location_shift = shifts[i]
  res = evaluate.unconditional(
    m = 100,
    n = 5,
    limits = list(lcl=68, ucl=432),
    location_shift = location_shift,
    scale_multiplier = 1,
    distribution_key = calib.eval.dist,
    distribution_parameters = calib.eval.dist.params,
    monitoring_statistic_key = "simple_statistic",
    monitoring_statistic_parameters = list(statistic="mann_whitney"),
    nsim = nsim,
    run_length_cap = 100000
  )
  rls = res$run_lengths
  arls[i] = mean(rls)
}
