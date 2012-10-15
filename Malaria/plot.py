from pylab import *
import sys, os, os.path

# some argument parsing
if len(sys.argv) < 3:
    print "Parameters: {folder to use}, {column of the matrix to use}"
    sys.exit(0)

folder = sys.argv[1]
column = sys.argv[2]

measurements = []
for filename in os.listdir(folder):
    fpath = os.path.join(folder, filename)
    measurements.append( loadtxt(fpath) )

# for simplicity, just truncate the graph to the shortest of the runs
time = min(measurements, key=lambda x: x.shape[0])[:, 6]

# convert the time to ints for convenience
time = [int(t) for t in time]

# collect average and standard deviation for the wanted statistic (infected
# humans in this case) at teach time
stddev   = []
averages = []

for t in time:
    ms = []
    for measurement in measurements:
        ms.append(measurement[t, column])

    stddev.append( std(ms) )
    averages.append( average(ms) )

errorbar(time, averages, yerr=stddev)
show()
