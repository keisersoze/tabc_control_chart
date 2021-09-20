logrange = function(x) {
  return (-log((1 - x) / exp(10)  + x))
}

inverse = function(x) {
  return (-(exp(-x) *  (exp(x) - exp(10))) / (exp(10) - 1))
}

# Params

seed = 56
turbostat.setseed(seed)
n = 10
m = 100
nperm = 1500
cap = 4000
evaluation.nsim = 2500

charts = c("a", "b", "c", "ab", "ac", "bc", "abc")

distributions = list(
  list("norm", c(0,1)),
  list("cauchy", c(0,1)),
  list("laplace", c(0,1))
)

calibration.dist.family =  "norm"
calibration.dist.params = c(0,1)
calibration.arl_target = 70
calibration.nsim = 2500
calibration.lcl_seq = inverse(seq(2, 5.0, 0.005))

# End params

# Prepare output

distributions.labels = rep(NA, length(distributions))
for (i in seq_along(distributions)) {
  distribution = distributions[[i]]
  distribution.family = distribution[[1]]
  distribution.params = distribution[[2]]
  params.string = paste(distribution.params, collapse=" ")
  distributions.labels[i] = sprintf("%s %s", distribution.family, params.string)
}

arl_table = matrix(nrow=length(distributions),ncol=(length(charts)))
rownames(arl_table) = distributions.labels
colnames(arl_table) = charts

# Calibrate charts

print("Calibration...")
lcl_vector = rep(NA, length(charts))
for (i in seq_along(charts)) {
  chart = charts[i]
  print(chart)
  start.time = proc.time()
  rls = calibrate.uncoditional(
    m = m,
    n = n,
    dist = calibration.dist.family,
    params = calibration.dist.params,
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
  LCL = afn(calibration.arl_target)
  lcl_vector[i] = LCL
  print(LCL)
}

# Evaluation

print("Evaluation...")
for (i in seq_along(charts)) {
  chart = charts[i]
  print(chart)
  for (j in seq_along(distributions)) {
    distribution = distributions[[j]]
    distribution.family = distribution[[1]]
    distribution.params = distribution[[2]]

    # Evaluation
    start.time = proc.time()
    result = rl.uncoditional(
      m = m,
      n = n,
      dist = distribution.family,
      params = distribution.params,
      nsim = evaluation.nsim,
      nperm = nperm,
      shifts = c(0),
      LCL = lcl_vector[i],
      test = chart,
      run_length_cap = cap
    )

    duration.time = proc.time() - start.time
    print(duration.time)
    arl_table[j,i] = result$ARLs[1]
    print(result)
  }
}

print(arl_table)



