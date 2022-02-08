library(MSQC)
data(carbon1)
data(carbon2)
reference.sample = as.vector(carbon1[1:30,2,1:8])
test.samples = carbon2[1:25,2,1:8]


plotChart = function (reference.sample, test.samples, calib.monitor_stat, calib.monitor_stat.params, calib.limit){
  monitoring.stats = rep(NA, nrow(test.samples))
  for (i in seq(1, nrow(test.samples))){
    if(i==10){
      test.sample = test.samples[i,] * 1.05
    } else {
      test.sample = test.samples[i,]
    }
    stat = compute_monitoring_statistic(
      reference.sample,
      test.sample,
      monitoring_statistic_type = calib.monitor_stat,
      monitoring_statistic_parameters = calib.monitor_stat.params
    )
    monitoring.stats[i] = stat
  }
  plot(seq(1,length(monitoring.stats)),monitoring.stats, ylim = (range(-15,15)))
  abline(h=calib.limit)
}


library(npcharts)

npc_wk.chart.path = "results_new/calibration/normal/npc_wilcoxon_klotz_norm_500_100_5_50000_8989.RData"
load(npc_wk.chart.path)

plotChart(
  reference.sample,
  test.samples,
  calib.monitor_stat,
  calib.monitor_stat.params,
  calib.limit
)

lepage.chart.path = "results_new/calibration/normal/lepage_norm_500_100_5_50000_8989.RData"
load(lepage.chart.path)

plotChart(
  reference.sample,
  test.samples,
  calib.monitor_stat,
  calib.monitor_stat.params,
  calib.limit
)

cucconi.chart.path = "results_new/calibration/normal/cucconi_norm_500_100_5_50000_8989.RData"
load(cucconi.chart.path)

plotChart(
  reference.sample,
  test.samples,
  calib.monitor_stat,
  calib.monitor_stat.params,
  calib.limit
)

