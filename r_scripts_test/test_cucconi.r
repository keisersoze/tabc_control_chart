# cucconi=function(x1,x2,B=10000)
# {cucconi.stat=function(x1,x2)
#  {cuc=function(x1,x2)
#  {vett=c(x1,x2)
#   enne1=length(x1)
#   enne2=length(x2)
#   enne=length(vett)
#   ranghi=rank(vett)
#   erre2=ranghi[(enne1+1):enne]
#   media=enne2*(enne+1)*(2*enne+1)
#   scarto=(enne1*enne2*(enne+1)*(2*enne+1)*(8*enne+11)/5)^0.5
#   u=(6*sum(erre2^2)-media)/scarto
#   v=(6*sum((enne+1-1*erre2)^2)-media)/scarto
#   ro=2*(enne^2-4)/(2*enne+1)/(8*enne+11)-1
#   cuc=(u^2+v^2-2*u*v*ro)/2/(1-ro^2)}
#  media=.5*(cuc(x1,x2)+cuc(x2,x1))}
#
# n1=length(x1)
# n2=length(x2)
# cucconi.obs=cucconi.stat(x1,x2)
# cucconi.perm=vector(,B)
# x=c(x1,x2)
#
# for (b in 1:B)
# {x.perm=sample(x)
#  x1.perm=x.perm[1:n1]
#  x2.perm=x.perm[(n1+1):(n1+n2)]
#  cucconi.perm[b]=cucconi.stat(x1.perm,x2.perm)}
#
# pvalue=length(cucconi.perm[cucconi.perm>=cucconi.obs])/B
#
# output=list(obs.value=cucconi.obs,p.value=pvalue,cucconi.perm=cucconi.perm)
# }
#
# x1 = rnorm(100)
# x2 = rnorm(20, 0.5)
# o=cucconi(x1,x2)
# print(o[["p.value"]])
# hist(o[["cucconi.perm"]])

cuc=function(x1,x2){
  vett=c(x1,x2)
  enne1=length(x1)
  enne2=length(x2)
  enne=length(vett)
  ranghi=rank(vett)
  erre2=ranghi[(enne1+1):enne]
  media=enne2*(enne+1)*(2*enne+1)
  scarto=(enne1*enne2*(enne+1)*(2*enne+1)*(8*enne+11)/5)^0.5
  u=(6*sum(erre2^2)-media)/scarto
  v=(6*sum((enne+1-1*erre2)^2)-media)/scarto
  ro=2*(enne^2-4)/(2*enne+1)/(8*enne+11)-1
  cuc=(u^2+v^2-2*u*v*ro)/2/(1-ro^2)
}

set.seed(32)
x1 = rnorm(100)
x2 = rnorm(20, 0.5)
print(test.cucconi(x1,x2))
print(cuc(x1,x2))
