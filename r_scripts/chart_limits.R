source("statistics.R")

# Fix the reference sample
m = 100
X = rnorm(m)

# Monte Carlo simulations
n = 50
nsim = 5000
nperm = 1000

statistics = c()
for (i in 1:nsim){
  Y = rnorm(n)
  s = Tabc (X,Y,"two.sided", nperm)
  # s = lepage.stat (X,Y)
  statistics = append(statistics, s)
}

distinct = length(unique(statistics))
plot(hist(statistics))
plot(density(statistics))
print(sprintf("Distinct: %d",  distinct))

# Find quantile corresponding to desired ARL

my_quantile <- function(x, prob) {
  if (is.unsorted(x)) x <- sort(x)
  n <- length(x)
  approx(seq(0, 1, length = n), x, prob)$y
}

ARL.target = 100
prob = 1/ARL.target

LCL = my_quantile(statistics, prob)

print(LCL)

# Simulate again to check UCL and LCL against desired ARL

rl.sample = c()
rl = 0
for (i in 1:nsim){
  Y = rnorm(n)
  st = Tabc (X,Y,"two.sided", nperm)
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

save(m, n, X, distinct, LCL, ARL.target, ARL.test, nsim, nperm,  file = "shared_data/first-test.RData")


#Simulate shift in the mean

# points = c()
# for (i in 1:5){
#   Y = rnorm(n, mean = 0 )
#   st = Tabc (X,Y,"two.sided", nperm)
#   # st = lepage.stat (X,Y)
#   points = append(points, st)
# }
# for (i in 1:5){
#   Y = rnorm(n, mean = 3 )
#   st = Tabc (X,Y,"two.sided", nperm)
#   # st = lepage.stat (X,Y)
#   points = append(points, st)
# }
# plot(seq(1,10),points)
# abline(h = UCL)

