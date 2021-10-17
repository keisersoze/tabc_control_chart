load("results/evaluation_results/prefinal/250_normalized_rate_one_exponential_100_10_10000_4637.RData")

difference_of_means = arl_table[,'difference_of_means']
mann_whitney = arl_table[,'mann-whitney']
sum_of_signs = arl_table[,'sum-of-sings']
tab_obs_stat = arl_table[,'tab_obs_stat']
tac_obs_stat = arl_table[,'tac_obs_stat']
tbc_obs_stat = arl_table[,'tbc_obs_stat']
tabc_obs_stat = arl_table[,'tabc_obs_stat']





plot(1, type="n", xlab="Shift", ylab="ARL", xlim=c(0.5, 1), ylim=c(0, 5.5))

lines(eval.shifts, mann_whitney, pch=18, col="red", type="b", lty=2)

lines(eval.shifts, sum_of_signs,  pch=19, col="blue", type="b", lty=2)

lines(eval.shifts, tbc_obs_stat, pch=20, col="black", type="b", lty=2)

legend(0.65, 5, legend=c("Mann Whitney U (C aspect)", "B aspect", "T_bc obs stat"), col=c("red", "blue", "black"), lty=2, cex=0.8)


