Tb = function(x1, x2, B=1000){
  x=c(x1,x2)
  n1=length(x1)
  n2=length(x2)
  n=n1+n2
  mediana=median(x)
  tb.ob=length(x1[x1>=mediana])-length(x2[x2>=mediana])
  tb.perm=vector(,B)

  # O(B * n)
  for (b in 1:B){
    x.perm=sample(x)
    x1.perm=x.perm[1:n1]
    x2.perm=x.perm[(n1+1):(n1+n2)]
    tb.perm[b]=length(x1.perm[x1.perm>=mediana])-length(x2.perm[x2.perm>=mediana])
  }

  pvalue=length(tb.perm[tb.perm<=tb.ob])/B
  return (c(tb.ob,pvalue))
}


seed = 42
set.seed(seed)
x1 = rnorm(50, mean = 0)
x2 = rnorm(50, mean = 0)

start.time = proc.time()
print (Tb(x1,x2,100000))
duration.time = proc.time() - start.time
print(duration.time)

start.time = proc.time()
print (permtest.tb(x1,x2, 100000))
duration.time = proc.time() - start.time
print(duration.time)
