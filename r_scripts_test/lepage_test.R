Lepage = function(x, y){
  m = length(x)
  n = length(y)
  N = m + n
  C.Rank = rank(c(x, y))
  S1 = sum(C.Rank[(m+1):N])
  S2 = sum(abs(C.Rank[(m+1):N]-(N+1)/2))
  if ((N %% 2) ==  0)
    Lepage.stat = (S1-n*(N+1)/2)^2/(m*n*(N+1)/12)+(S2-n*N/4)^2/ (m*n*((N)^2-4)/(48*(N-1)))
  else Lepage.stat = (S1-n*(N+1)/2)^2/(m*n*(N+1)/12)+(S2-(n*((N)^2-1))/(4*N))^2/ (m*n*(N+ 1)*((N)^2+3)/(48*(N)^2))
  return(Lepage.stat)
}

set.seed(42)
x1 = rnorm(10)
x2 = rnorm(21)

print(test.lepage(x1,x2))

print(Lepage(x1,x2))
