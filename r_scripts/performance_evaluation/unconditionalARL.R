source("statistics.R")

## Params

n = 5
m = 100

shift.seq = seq(0, 2, 0.5)

nSim = 1000

getsample = function(n, shift){
  scale = 1
  location = 1
  return (rLaplace(n, mu = location + shift, b = scale))
}

chart.plotting.stat = function(sample.ref, sample.test){
  return (Tc.pvalue (sample.ref,sample.test))
}

chart.UCL = 4.891907


##

run.lengths = vector(,length(shift.seq))
for (shift.index in seq_along(shift.seq) ){
  shift.value = shift.seq[shift.index]
  run.lengths.cond = vector(,nSim)
  for (sim in seq(1, nSim)){
    sample.ref = getsample(m, 0)
    run.length = 0
    repeat{
      sample.test =  getsample(n, shift.value)
      stat = chart.plotting.stat(sample.ref, sample.test)
      if(stat > chart.UCL ){
        break
      } else{
        run.length = run.length +1
      }
    }
    run.lengths.cond[sim] = run.length
  }
  run.lengths[shift.index] = mean(run.lengths.cond)
}

print (shift.seq)
print (run.lengths)
