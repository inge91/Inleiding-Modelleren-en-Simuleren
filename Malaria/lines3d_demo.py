import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from pylab import *
import matplotlib.pyplot as plt
import sys, os, os.path
# some argument parsing
if len(sys.argv) < 4:
    print "Parameters: {folder to use}, {column of the matrix to use}"
    sys.exit(0)

mpl.rcParams['legend.fontsize'] = 10
fig = plt.figure()
ax = fig.gca(projection='3d')
folders = [] 
i = 1
while( sys.argv[i] != "stop"):
    folders.append(sys.argv[i])
    i += 1
i += 1

columns = []
while(sys.argv[i] != "stop"):
    columns.append(int(sys.argv[i]))
    i+=1

i += 1

rates = []
while(i < len(sys.argv)):
    rates.append(double(sys.argv[i]))
    i+=1

print folders
print "\n"
print columns
print "\n"
print rates

i = 0
print "len folders"
print len(folders)
for folder in folders:
    measurements = []
    for filename in os.listdir(folder):
    #    print filename
        fpath = os.path.join(folder, filename)
        measurements.append( loadtxt(fpath) )

    #print measurements
    # for simplicity, just truncate the graph to the shortest of the runs
    time = min(measurements, key=lambda x: x.shape[0])[:, 6]
    #print time
    # convert the time to ints for convenience
    time = [int(t) for t in time]

    # collect average and standard deviation for the wanted statistic (infected
    # humans in this case) at teach time
    for column in columns:
        stddev   = []
        averages = []
        for t in time:
            ms = []
            for measurement in measurements:
                ms.append(measurement[t, column])
        
            stddev.append( std(ms) )
            averages.append( average(ms) )
        
        print averages
        print i
        print rates
        ax.plot(time, len(time) * [rates[i]], averages)
    i+=1

ax.legend()
plt.show()
raw_input("Press Enter...\n")

