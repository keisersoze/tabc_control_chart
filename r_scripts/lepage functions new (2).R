rm(list = ls(all = TRUE))
source("statistics.R")


Lepage = function(x, y){
  m = length(x)
  n = length(y)
  N = m + n
  C.Rank = rank(c(x, y))
  S1 = sum(C.Rank[(m+1):N])
  S2 = sum(abs(C.Rank[(m+1):N]-(N+1)/2))
  if ((N %% 2) ==  0)
       Lepage.stat = (S1-n*(N+1)/2)^2/(m*n*(N+1)/12)+(S2-n*N/4)^2/ (m*n*((N)^2-4)/(48*(N-1)))
  else Lepage.stat = (S1-n*(N+1)/2)^2/(m*n*(N+1)/12)+(S2-(n*((N)^2-1))/(4*N))^2/ (m*n*(N+ 1)*((N)^2+3)/(48*(N)^2))
  return(Lepage.stat)
}


Cond.RL.Lepage = function(m, n, crit = "ARL0", p = 0.5, UCLs = seq(2, qchisq(0.9999, 2), 0.5), w = 5000, force.w = FALSE){
  Phase1sample = rnorm(m)
  if (force.w == FALSE && crit == "PRL0" && p <= 0.1 ) w = 200
  if (force.w == FALSE && crit == "PRL0" && p > 0.1 && p <= 0.3) w = 500
  if (force.w == FALSE && crit == "PRL0" && p > 0.3 && p <= 0.5) w = 900
  z = as.numeric(vapply(1:w, function(i){Tc.pvalue(Phase1sample, rnorm(n))}, FUN.VALUE = numeric(1)))
  C.RL = as.numeric(vapply(1:length(UCLs), function(i){if (max(z) > UCLs[i]) min(which(z > UCLs[i])) else w}, FUN.VALUE = numeric(1)))
  return(C.RL)
}



UCL.Lepage = function(m, n, crit = "ARL0", p = 0.5, target = c(250, 370.4, 500), UCLs = seq(2, qchisq(0.9999, 2), 0.5), w = 5000, force.w = FALSE, sim = 1000, seed.no = 17031861){
  set.seed(seed.no)
  RL = vapply(1:sim, function(i){Cond.RL.Lepage(m, n, crit, p, UCLs, w, force.w)}, FUN.VALUE = numeric(length(UCLs)))

  if (crit == "ARL0") {
  summary = rowMeans(RL)
  M = loess(UCLs ~ summary)
  }

  if (crit == "PRL0") {
  Q = function(RLs){quantile(RLs, p)}
  summary = as.vector(apply(RL, 1, Q))
  summary = summary[summary < w]
  M = loess(UCLs[1:length(summary)] ~ summary)
  }

  UCL = as.vector(predict(M, data.frame(summary = target)))
  output = list("Criterium" = crit, "p" = p, "Target.values" = target, "UCLs" = UCL)

  return(output)
}

start.time = proc.time()
print(UCL.Lepage(100, 5 , sim = 100, w = 3000, UCL = seq (3, 5.5 , 0.05 )))
duration = proc.time() - start.time

print (duration)
