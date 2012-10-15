import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from pylab import *
import matplotlib.pyplot as plt
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


mpl.rcParams['legend.fontsize'] = 10

fig = plt.figure()
ax = fig.gca(projection='3d')
theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
z = np.linspace(-2, 2, 100)
r = z**2 + 1
x = r * np.sin(theta)
y = r * np.cos(theta)

ax.plot(time, len(time) * [0.3], averages)
ax.legend()

plt.show()

