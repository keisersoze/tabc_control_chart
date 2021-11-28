library(qcc)

data(pistonrings)
str(pistonrings)
head(pistonrings)
attach(pistonrings)
diameter.new <- qcc.groups(diameter, sample)
head(diameter)


##################################################################
# Shewhart x-bar chart

# A Shewhart chart is automatically plotted when an object of class `qcc' is created,
# unless the qcc function is called with the argument plot=FALSE.

# default is 3 sigma limits, to change add nsigmas=2.7
qcc(diameter.new[1:25,], type="xbar")

# Shewhart x-bar chart chart for both calibration data and new data, but all the
# statistics and the control limits are solely based on the first 25 samples
q1 <- qcc(diameter.new[1:25,], type="xbar", newdata=diameter.new[26:40,])

# Unless we provide the argument add.stats=FALSE, at the bottom of the plot some
# summary statistics are shown, together with the number of points beyond control
# limits and the number of violating runs (a run has length 5 by default).

qcc(diameter.new[1:25,], type="xbar", newdata=diameter.new[26:40,], add.stats=FALSE, chart.all=FALSE, ylab="Monitoring statistic", xlab="Group", title = "xbar Control chart for Piston rings dataset")

