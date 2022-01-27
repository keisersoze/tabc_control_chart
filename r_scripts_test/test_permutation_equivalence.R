
T_DM = function(x1,x2){
  return (sum(x1) * 1/length(x1) - sum(x2) * 1/length(x2))
}

T_DS = function(x1,x2){
  return (sum(x1) - sum(x2))
}

T_M = function(x1,x2){
  return (sum(x1) * 1/length(x1))
}

T_S = function(x1,x2){
  return (sum(x1))
}


test=function(x1,x2, stat, alt, K=1000) {
  n1 = length(x1)
  n2 = length(x2)
  n = n1 + n2
  t.ob = stat(x1, x2)
  t.perm = vector(, K)
  x = c(x1,x2)
  for (k in 1:K){
    x.perm = sample(x)
    x1.perm = x.perm[1:n1]
    x2.perm = x.perm[(n1 + 1):(n1 + n2)]
    t.perm[k] = stat(x1.perm, x2.perm)
  }


  plot(density(t.perm))
  hist(t.perm, breaks = 50, main = "" , xlab = "Stat")
  abline(v = t.ob, col = "blue", lwd = 2)

  pv.l=length(t.perm[t.perm>=t.ob])/K
  pv.r=length(t.perm[t.perm<=t.ob])/K
  if (alt=="two.sided") pv.t=length(t.perm[abs(t.perm)>=abs(t.ob)])/K
  if (alt=="two.sided-2") pv.t=min(pv.l,pv.r)
  if (alt=="greater") pv.t=length(t.perm[t.perm>=t.ob])/K
  if (alt=="less") pv.t=length(t.perm[t.perm<=t.ob])/K
  if (alt=="greater") pv.t=length(t.perm[t.perm>=t.ob])/K

  return(pv.t)
}

x1 = rnorm(10, mean=8, sd=1)
x2 = rnorm(5, mean=8, sd=1)
K = 100000

# p_M = test(x1, x2, T_DM, "two.sided", K)
# p_S = test(x1, x2, T_DS, "two.sided", K)
# print(p_M)
# print(p_S)

p_DM = test(x1, x2, T_DM, "greater", K)
p_DS = test(x1, x2, T_DS, "greater", K)
p_M = test(x1, x2, T_M, "greater", K)
p_S = test(x1, x2, T_S, "greater", K)
print(p_DM)
print(p_DS)
print(p_M)
print(p_S)


