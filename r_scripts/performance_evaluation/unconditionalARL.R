source("statistics.R")

## Params

n = 10
m = 100

shift.seq = c(0)

nSim = 10000

# getsample = function(n, shift){
#   scale = 1
#   location = 0
#   return (rnorm(n, mean = location + shift, sd = scale))
# }

getsample = function(n, shift){
  scale = 5
  location = 2
  return (rLaplace(n, mu = location + shift, b = scale))
}


chart.plotting.stat = function(sample.ref, sample.test){
  return (permtest.tb(sample.ref,sample.test,1000)[2])
}

# chart.UCL = 4.891907
chart.LCL = 1/20
chart.UCL = NULL

cap = 5000


##
stops = 0
run.lengths = vector(,length(shift.seq))
for (shift.index in seq_along(shift.seq) ){
  shift.value = shift.seq[shift.index]
  run.lengths.cond = vector(,nSim)
  print(sprintf("Elaboration shift: %f", shift.value))
  for (sim in seq(1, nSim)){
    # print(sim)
    sample.ref = getsample(m, 0)
    run.length = 0
    repeat{
      sample.test =  getsample(n, shift.value)
      stat = chart.plotting.stat(sample.ref, sample.test)
      if((!is.null(chart.UCL) && stat > chart.UCL) ||
         (!is.null(chart.LCL) && stat < chart.LCL)){
        break
      } else if(run.length > cap){
        stops = stops + 1
        break
      } else{
        run.length = run.length +1
      }
    }
    run.lengths.cond[sim] = run.length
  }
  run.lengths[shift.index] = mean(run.lengths.cond)
}

print (sprintf("Stops: %d", stops))
print (shift.seq)
print (run.lengths)

