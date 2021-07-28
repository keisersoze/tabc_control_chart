Tabc=function(x1,x2,alt,B=1000){
  x=c(x1,x2)
  n1=length(x1)
  n2=length(x2)
  n=n1+n2
  mediana=median(x) 
  ranghi=rank(x)
  ta.ob=sum(x1)-sum(x2)
  tb.ob=length(x1[x1>=mediana])-length(x2[x2>=mediana])
  tc.ob=sum(ranghi[1:n1])-sum(ranghi[(n1+1):n])
  ta.perm=vector(,B)
  tb.perm=vector(,B)
  tc.perm=vector(,B)
  tabc.perm=vector(,B)
  
  for (b in 1:B){
    x.perm=sample(x)
    x1.perm=x.perm[1:n1]
    x2.perm=x.perm[(n1+1):(n1+n2)]
    ranghi.perm=rank(x.perm)
    ta.perm[b]=sum(x1.perm)-sum(x2.perm)
    tb.perm[b]=length(x1.perm[x1.perm>=mediana])-length(x2.perm[x2.perm>=mediana])
    tc.perm[b]=sum(ranghi.perm[1:n1])-sum(ranghi.perm[(n1+1):n])
  }
  
  if (alt=="greater") {
    pv.ta.ob=length(ta.perm[ta.perm>=ta.ob])/B
    pv.tb.ob=length(tb.perm[tb.perm>=tb.ob])/B
    pv.tc.ob=length(tc.perm[tc.perm>=tc.ob])/B
  }
  if (alt=="less") {
    pv.ta.ob=length(ta.perm[ta.perm<=ta.ob])/B
    pv.tb.ob=length(tb.perm[tb.perm<=tb.ob])/B
    pv.tc.ob=length(tc.perm[tc.perm<=tc.ob])/B
  }
  if (alt=="two.sided") {
    pv.ta.ob=length(abs(ta.perm)[abs(ta.perm)>=abs(ta.ob)])/B
    pv.tb.ob=length(abs(tb.perm)[abs(tb.perm)>=abs(tb.ob)])/B
    pv.tc.ob=length(abs(tc.perm)[abs(tc.perm)>=abs(tc.ob)])/B
  }
  
  tabc.ob=min(pv.ta.ob,pv.tb.ob,pv.tc.ob)

  return (tabc.ob)
}

# Fix the reference sample of size m=100
m = 300
X = rnorm(m)

# Monte carlo simulation with n = 10
n = 80
nsim = 2000
nperm = 1000
statistics = c()
for (i in 1:nsim){
  Y = rnorm(n)
  s = Tabc (X,Y,"two.sided", nperm)
  statistics = append(statistics, s)
}

plot(hist(statistics))
plot(density(statistics))

# Find quantile corresponding to desired ARL

my_quantile <- function(x, prob) {
  if (is.unsorted(x)) x <- sort(x)
  n <- length(x)
  approx(seq(0, 1, length = n), x, prob)$y
}

ARL = 200
prob = 1/ARL

UCL = my_quantile(statistics, 1 - prob)

print(UCL)

# Simulate again to check UCL and LCL against desired ARL
rl.sample = c()
rl = 0
for (i in 1:nsim){
  Y = rnorm(n)
  st = Tabc (X,Y,"two.sided", nperm)
  if (st < UCL ){
    rl = rl + 1
  } else {
    rl.sample = append(rl.sample, rl)
    rl = 0
  }
}

print(mean(rl.sample))
plot(hist(rl.sample))


