library(xtable)

load("results_new/evaluation/location_scale/crl/cucconi_500_norm_100_5_50000_4367.RData")

ndigits = 1
ndigits_quantiles = 0


for (i in 1:ncol(carl_table)) {
  for (j in 1:nrow(carl_table)) {
    carl = as.numeric(carl_table[[j, i]])
    csd = csd_table[[j, i]]
    proportion = proportion_table[[j, i]]


    round_carl = round(carl, digits = ndigits)
    round_csd = round(csd, digits = ndigits)
    proportion = round(proportion, digits = 4)

    if (round_carl <= 900 && round_carl >= 250){
      carl_table[j,i] = paste(
        "\\cellcolor{blue!25} \\tabularCenterstack{c}{\\textit{",
        as.character(proportion),
        "}\\\\",
        as.character(round_carl),
        " [",
        as.character(round_csd),
        "]}",
        sep = ""
      )
    } else {
      carl_table[j,i] = paste(
        "\\tabularCenterstack{c}{\\textit{",
        as.character(proportion),
        "}\\\\",
        as.character(round_carl),
        " [",
        as.character(round_csd),
        "]}",
        sep = ""
      )
    }

  }
}

print(xtable(carl_table, align = "|r|c|c|c|c|c|c|c|"), hline.after=seq(-1, nrow(carl_table), 1), sanitize.text.function=identity)
