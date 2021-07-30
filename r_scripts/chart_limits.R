source("statistics.R")

# Script parameters
m = 100
n = 10
iidsample = function(nsamples){
  return (rcauchy(nsamples))
}
X = iidsample(m)
ARL.target = 50
nsim = 5000
nperm = 1000

# Fix the reference sample
X = iidsample(m)

# Monte Carlo simulations to estimate distribution of Tabc statistic under the null
statistics = c()
for (i in 1:nsim){
  Y = iidsample(n)
  s = Tabc.unbalanced (X,Y,"two.sided", nperm)
  statistics = append(statistics, s)
}

distinct = length(unique(statistics))
plot(hist(statistics))
plot(density(statistics))
print(sprintf("Distinct: %d",  distinct))

# Find empirical quantile corresponding to desired ARL
quantile <- function(x, prob) {
  if (is.unsorted(x)) x <- sort(x)
  n <- length(x)
  approx(seq(0, 1, length = n), x, prob)$y
}
prob = 1/ARL.target # using result from Mukherjee 2011
LCL = quantile(statistics, prob)

print(LCL)

# Simulate again to check LCL against desired ARL
rl.sample = c()
rl = 0
for (i in 1:nsim){
  Y = iidsample(n)
  st = Tabc.unbalanced (X,Y,"two.sided", nperm)
  # st = lepage.stat (X,Y)
  if (st > LCL ){
    rl = rl + 1
  } else {
    rl.sample = append(rl.sample, rl)
    rl = 0
  }
}

ARL.test = mean(rl.sample)
print(ARL.test)
plot(hist(rl.sample))

# Save LCL and related info
save(m, n, X, distinct, LCL, ARL.target, ARL.test, nsim, nperm, iidsample,  file = "shared_data/cauchy-unbalanced.RData")


