source("statistics.R")

nperm = 500
nsim = 20000

load("shared_data/first-test.RData")

# n = 5
# m = 100
# X = rcauchy(m)
# UCL = 11.25

rl.sample = c()
rl = 0
for (i in 1:nsim){
  Y = rcauchy(n)
  st = lepage.stat (X,Y)
  if (st <= UCL ){
    rl = rl + 1
  } else {
    rl.sample = append(rl.sample, rl)
    rl = 0
  }
}

print(mean(rl.sample))
plot(hist(rl.sample))
