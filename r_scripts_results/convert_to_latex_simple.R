library(xtable)

load("results/evaluation_results/prefinal/250_laplace_100_10_10000_4637_corrected.RData")

print(xtable(arl_table))
