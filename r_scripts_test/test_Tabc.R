
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
  # print(ta.ob)
  # print(tb.ob)
  # print(tc.ob)

  ta.perm=vector(,B)
  tb.perm=vector(,B)
  tc.perm=vector(,B)

  # O(B * n)
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
  # print( ta.perm)
  # print( tb.perm)
  # print( tc.perm)
  # print( pv.ta.ob)
  # print( pv.tb.ob)
  # print( pv.tc.ob)
  tabc.ob=min(pv.ta.ob,pv.tb.ob,pv.tc.ob)

  tabc.perm=rep(NA, B)

  # O (Blog(B))
  if (alt == "less"){
    ta.perm.order = order(ta.perm, decreasing = FALSE)
    tb.perm.order = order(tb.perm, decreasing = FALSE)
    tc.perm.order = order(tc.perm, decreasing = FALSE)
    ta.perm.sorted = ta.perm [ta.perm.order]
    tb.perm.sorted = tb.perm [tb.perm.order]
    tc.perm.sorted = tc.perm [tc.perm.order]
  }
  if (alt=="greater") {
    ta.perm.order = order(ta.perm, decreasing = TRUE)
    tb.perm.order = order(tb.perm, decreasing = TRUE)
    tc.perm.order = order(tc.perm, decreasing = TRUE)
    ta.perm.sorted = ta.perm [ta.perm.order]
    tb.perm.sorted = tb.perm [tb.perm.order]
    tc.perm.sorted = tc.perm [tc.perm.order]
  }
  if (alt=="two.sided"){
    ta.perm = abs(ta.perm)
    tb.perm = abs(tb.perm)
    tc.perm = abs(tc.perm)
    ta.perm.order = order(ta.perm, decreasing = TRUE)
    tb.perm.order = order(tb.perm, decreasing = TRUE)
    tc.perm.order = order(tc.perm, decreasing = TRUE)
    ta.perm.sorted = ta.perm [ta.perm.order]
    tb.perm.sorted = tb.perm [tb.perm.order]
    tc.perm.sorted = tc.perm [tc.perm.order]
  }

  a.tides = 0
  b.tides = 0
  c.tides = 0

  # O (B)
  for (cp in 1:B){

    if (cp != B && ta.perm.sorted[cp] == ta.perm.sorted[cp+1] ){
      a.tides = a.tides + 1
    } else {
      while(a.tides > - 1){
        cp2 =  ta.perm.order[cp - a.tides]
        if (is.na(tabc.perm[cp2])){
          tabc.perm[cp2] = cp / B
        }
        a.tides = a.tides - 1
      }
      a.tides = 0
    }

    if (cp != B && tb.perm.sorted[cp] == tb.perm.sorted[cp+1] ){
      b.tides = b.tides + 1
    } else {
      while(b.tides > - 1){
        cp2 =  tb.perm.order[cp - b.tides]
        if (is.na(tabc.perm[cp2])){
          tabc.perm[cp2] = cp / B
        }
        b.tides = b.tides - 1
      }
      b.tides = 0
    }

    if (cp != B && tc.perm.sorted[cp] == tc.perm.sorted[cp+1] ){
      c.tides = c.tides + 1
    } else {
      while(c.tides > - 1){
        cp2 =  tc.perm.order[cp - c.tides]
        if (is.na(tabc.perm[cp2])){
          tabc.perm[cp2] = cp / B
        }
        c.tides = c.tides - 1
      }
      c.tides = 0
    }
  }

  pv.tabc=length(tabc.perm[tabc.perm<=tabc.ob])/B
  return(c(pv.tabc, tabc.ob))
}

seed = 4
set.seed(seed)
turbostat.setseed(43)
x1=rcauchy(100, location = 0)
x2=rcauchy(100, location = 0.1)

start.time = proc.time()
print(Tabc(x1,x2,"less", 100000))
duration.time = proc.time() - start.time
print (duration.time)

start.time = proc.time()
print(permtest.tabc(x1,x2, 100000))
duration.time = proc.time() - start.time
print (duration.time)
