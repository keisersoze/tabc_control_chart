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

Tabc.pvalue=function(x1,x2,alt,B=1000){
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
  return(pv.tabc)
}

Tabc.unbalanced=function(x1,x2,alt,B=1000){
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
  
  pv.ta.ob.r=length(ta.perm[ta.perm>=ta.ob])/B
  pv.tb.ob.r=length(tb.perm[tb.perm>=tb.ob])/B
  pv.tc.ob.r=length(tc.perm[tc.perm>=tc.ob])/B
  
  pv.ta.ob.l=length(ta.perm[ta.perm<=ta.ob])/B
  pv.tb.ob.l=length(tb.perm[tb.perm<=tb.ob])/B
  pv.tc.ob.l=length(tc.perm[tc.perm<=tc.ob])/B
  
  pv.ta.ob=min(pv.ta.ob.r,pv.ta.ob.l)
  pv.tb.ob=min(pv.tb.ob.r,pv.tb.ob.l)
  pv.tc.ob=min(pv.tc.ob.r,pv.tc.ob.l)
  
  tabc.ob=min(pv.ta.ob,pv.tb.ob,pv.tc.ob)
  
  return (tabc.ob)
}



lepage.stat=function(x1,x2){
  enne1=length(x1)
  enne2=length(x2)
  enne=enne1+enne2
  e.w=enne1*(enne+1)/2
  v.w=enne1*enne2*(enne+1)/12
  e.a=enne1*(enne+2)/4
  v.a=enne1*enne2*(enne+2)*(enne-2)/48/(enne-1)
  w.o=as.numeric(wilcox.test(x1,x2,exact=FALSE)[1])+enne1*(enne1+1)/2
  a.o=as.numeric(ansari.test(x1,x2,exact=FALSE,alternative="two.sided")[1])
  wp.o=(w.o-e.w)^2/v.w
  ap.o=(a.o-e.a)^2/v.a
  lepage=wp.o+ap.o
}


Tabc.pvalue.log=function(x1,x2,alt,B=1000){
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
  return(-log(pv.tabc + 0.01))
}


Tc.stat = function(x, y){
  m = length(x)
  n = length(y)
  N = m + n
  C.Rank = rank(c(x, y))  
  S1 = sum(C.Rank[(m+1):N])
  S1.mean = n*(N+1)/2
  S1.var = (m*n*(N+1)/12)
  S1.standard = (S1-S1.mean)^2/ S1.var
  return(S1.standard)
}

