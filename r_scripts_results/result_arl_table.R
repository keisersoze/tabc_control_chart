logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}


# Params
seed = 56
turbostat.setseed(seed)
n = 5
m = 100
dist = "cauchy"
params = c(0,1)
ARL.target = 370
nperm = 3000
charts = c("abc", "a", "b", "c")
cap = 4000

# Calibration specific params
calibration.nsim = 5000
calibration.lcl_seq = inverse(seq(2, 6.0, 0.005))

# Evaluation specific params
evaluation.nsim = 5000
evaluation.shifts = c(0, 0.25, 0.5, 0.75, 1)

arl_table = matrix(nrow=length(evaluation.shifts),ncol=(length(charts)))
rownames(arl_table) = evaluation.shifts
colnames(arl_table) = charts

sd_table = matrix(nrow=length(evaluation.shifts),ncol=(length(charts)))
rownames(sd_table) = evaluation.shifts
colnames(sd_table) = charts

lcl_vector = rep(NA, length(charts))
names(lcl_vector) = charts

for(i in seq_along(charts)){
  chart = charts[i]
  print(sprintf("Processing chart %s", chart))


  ## Calibration
  start.time = proc.time()
  rls = calibrate.uncoditional(
    m = m,
    n = n,
    dist = dist,
    params = params,
    nsim = calibration.nsim,
    nperm = nperm,
    lcl_seq = calibration.lcl_seq,
    test = chart,
    run_length_cap = cap
  )
  duration.time = proc.time() - start.time
  print(duration.time)
  arls = colMeans(rls)
  afn = approxfun(arls,calibration.lcl_seq)
  LCL = afn(ARL.target)
  lcl_vector[i] = LCL
  print(LCL)

  # Evaluation
  start.time = proc.time()
  result = rl.uncoditional(
    m = m,
    n = n,
    dist = dist,
    params = params,
    nsim = evaluation.nsim,
    nperm = nperm,
    shifts = evaluation.shifts,
    LCL = LCL,
    test = chart,
    run_length_cap = cap
  )
  duration.time = proc.time() - start.time
  print(duration.time)
  for (j in seq_along(evaluation.shifts)){
    arl_table[j,i] = result$ARLs[j]
    sd_table[j,i] = result$SD[j]

  }
  print(result)

}

save(m,
     n,
     ARL.target,
     nperm,
     charts,
     calibration.nsim,
     calibration.lcl_seq,
     evaluation.nsim,
     evaluation.shifts,
     cap,
     seed,
     arl_table,
     sd_table,
     lcl_vector,
     dist,
     params,
     file = "results/OOC_performance_test/cauchy5000.RData")

