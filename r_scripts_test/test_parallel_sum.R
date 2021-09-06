library(microbenchmark)

b = microbenchmark(
  parallel_random_sum(1e7, 8, 1),
  parallel_random_sum(1e7, 8, 2),
  parallel_random_sum(1e7, 8, 4),
  parallel_random_sum(1e7, 8, 8),
  parallel_random_sum(1e7, 8, 12),
  times= 1
)

print(b)
