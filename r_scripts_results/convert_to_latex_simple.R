library(xtable)

load("results_new/evaluation/location/370_laplace_100_5_50000_121212.RData")

ndigits = 1
ndigits_quantiles = 0


for (i in 1:(ncol(arl_table)-2)) {
  for (j in 1:nrow(arl_table)) {
    arl = as.numeric(arl_table[[j, i + 2]])
    sd = as.numeric(sd_table[[j, i + 2]])
    quantiles.zerofive = as.numeric(quantile_tables.zerofive[[j, i + 2]])
    quantiles.five = as.numeric(quantile_tables.five[[j, i + 2]])
    quantiles.ninetyfive = as.numeric(quantile_tables.ninetyfive[[j, i + 2]])

    round_arl = round(arl, digits = ndigits)
    round_sd = round(sd, digits = ndigits)
    quantiles.zerofive.round = round(quantiles.zerofive, digits = ndigits_quantiles)
    quantiles.five.round = round(quantiles.five, digits = ndigits_quantiles)
    quantiles.ninetyfive.round = round(quantiles.ninetyfive, digits = ndigits_quantiles)
    arl_table[j,i +2] = paste(
      "\\makecell{",
      as.character(round_arl),
      " [",
      as.character(round_sd),
      "]\\\\",
      as.character(quantiles.zerofive.round),
      ", ",
      as.character(quantiles.five.round),
      ", ",
      as.character(quantiles.ninetyfive.round),
      "}",
      sep = ""
    )
  }
}

print(xtable(arl_table),include.rownames=FALSE, sanitize.text.function=identity)
