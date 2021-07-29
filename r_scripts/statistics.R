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
