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

number_of_folders = (len(sys.argv) - 2)/2
folders = [] 
i = 1
while i <= number_of_folders:
    folders.append(sys.argv[i])
    i+=1
print folders
column = sys.argv[i]
print column

rates = []
while i < len(sys.argv):
    rates.append(sys.argv[i])
    i+=1

for folder in folders:
    i = 0
    measurements = []
    for filename in os.listdir(folder):
        print filename
        fpath = os.path.join(folder, filename)
        measurements.append( loadtxt(fpath) )

    print measurements
    # for simplicity, just truncate the graph to the shortest of the runs
    time = min(measurements, key=lambda x: x.shape[0])[:, 6]
    print time
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


    mpl.rcParams['legend.fontsize'] = 10

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
    z = np.linspace(-2, 2, 100)
    r = z**2 + 1
    x = r * np.sin(theta)
    y = r * np.cos(theta)

    ax.plot(time, len(time) * [rates[i]], averages)
    plt.show()
    raw_input("Press Enter...\n")
    i+=1
ax.legend()

plt.show()

