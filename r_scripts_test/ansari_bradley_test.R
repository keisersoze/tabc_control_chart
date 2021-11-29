
set.seed(34)

x1 = rnorm(50)
x2 = rnorm(70) * 0.4

print(ansari.test(x1, x2, alternative = "two.sided"))
print(test.ansari_bradley(x1,x2))

m = length(x1)
n = length(x2)
N = m + n
C.Rank = rank(c(x1, x2))
S2 = sum(abs(C.Rank[(m+1):N]-(N+1)/2))
print(S2)
