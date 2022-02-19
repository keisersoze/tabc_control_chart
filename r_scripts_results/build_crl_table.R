library(xtable)

load("results_new/evaluation/location_scale/crl/laplace/v2_npc_lepage_cucconi_500_laplace_100_5_50000_42367.RData")

options(scipen = 999) #disable scientific notation

ndigits = 1
ndigits_quantiles = 0


for (i in 1:ncol(carl_table)) {
  for (j in 1:nrow(carl_table)) {
    carl = as.numeric(carl_table[[j, i]])
    csd = csd_table[[j, i]]
    proportion_nr = proportion_table[[j, i]]


    round_carl = round(carl, digits = ndigits)
    round_csd = round(csd, digits = ndigits)
    proportion = round(proportion_nr, digits = 4)

    # if ((i == 1 && j ==7)||(j == 1 && i ==7) ){
    #   print(proportion_nr)
    #   carl_table[j,i] = paste(
    #     "\\tabularCenterstack{c}{\\textit{$\\leq$0.00006}\\\\-}",
    #     sep = ""
    #   )
    # }else
    if (round_carl <= 900 && round_carl >= 250){
      carl_table[j,i] = paste(
        "\\cellcolor{blue!25} \\tabularCenterstack{c}{\\textit{",
        as.character(proportion, scientific = FALSE),
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
        as.character(proportion, scientific = FALSE),
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
