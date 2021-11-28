# test=function(x1,x2,alt,K=1000) {
#     x = c(x1, x2)
#     ranghi = rank(x)
#     n1 = length(x1)
#     n2 = length(x2)
#     n = n1 + n2
#     t.ob = sum(ranghi[1:n1]) * 1/n1 - sum(ranghi[(n1+1):n]) * 1/n2
#     t.perm = vector(, K)
#     for (k in 1:K){
#       x.perm = sample(ranghi)
#       x1.perm = x.perm[1:n1]
#       x2.perm = x.perm[(n1 + 1):(n1 + n2)]
#       t.perm[k] = sum(x1.perm) * 1/n1 - sum(x2.perm) * 1/n2
#     }
#
#
#     plot(density(t.perm))
#     hist(t.perm, breaks = 100, main = "" , xlab = "Value of test statistic")
#     abline(v = t.ob, col = "blue", lwd = 2)
#
#
#     if (alt=="greater") pv.t=length(t.perm[t.perm>=t.ob])/K
#     if (alt=="less") pv.t=length(t.perm[t.perm<=t.ob])/K
#     if (alt=="two.sided") pv.t=length(abs(t.perm)[abs(t.perm)>=abs(t.ob)])/K
#     print(pv.t)
#
#     return(t.perm)
# }

test=function(x1,x2,alt,K=1000) {
  n1 = length(x1)
  n2 = length(x2)
  n = n1 + n2
  t.ob = sum(x1) * 1/n1 - sum(x2) * 1/n2
  t.perm = vector(, K)
  x = c(x1,x2)
  for (k in 1:K){
    x.perm = sample(x)
    x1.perm = x.perm[1:n1]
    x2.perm = x.perm[(n1 + 1):(n1 + n2)]
    t.perm[k] = sum(x1.perm) * 1/n1 - sum(x2.perm) * 1/n2
  }


  plot(density(t.perm))
  hist(t.perm, breaks = 50, main = "" , xlab = "Value of test statistic")
  abline(v = t.ob, col = "blue", lwd = 2)



  pv.l=length(t.perm[t.perm>=t.ob])/K
  pv.r=length(t.perm[t.perm<=t.ob])/K
  if (alt=="two.sided") pv.t=length(t.perm[abs(t.perm)>=abs(t.ob)])/K
  if (alt=="two.sided-2") pv.t=min(pv.l,pv.r)

  print(pv.t)

  return(t.perm)
}

set.seed(42)
x1 = rexp(25)
x2 = rexp(9) - 1

t.perm = test(x1,x2,"two.sided-2", 10000)

