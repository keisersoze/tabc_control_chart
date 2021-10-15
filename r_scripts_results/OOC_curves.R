load("results/evaluation_results/prefinal/250_normalized_rate_one_exponential_100_10_10000_4637.RData")

difference_of_means = arl_table[,'difference_of_means']
mann_whitney = arl_table[,'mann-whitney']
sum_of_signs = arl_table[,'sum-of-sings']
tab_obs_stat = arl_table[,'tab_obs_stat']
tac_obs_stat = arl_table[,'tac_obs_stat']
tbc_obs_stat = arl_table[,'tbc_obs_stat']
tabc_obs_stat = arl_table[,'tabc_obs_stat']





plot(1, type="n", xlab="", ylab="", xlim=c(0.5, 1), ylim=c(0, 5.5))

lines(eval.shifts, mann_whitney, col = "red")

lines(eval.shifts, sum_of_signs, col = "blue")

lines(eval.shifts, tbc_obs_stat, col = "green")


