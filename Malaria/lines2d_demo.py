import matplotlib as mpl
import numpy as np
from pylab import *
import sys, os, os.path, subprocess, re

# some argument parsing
if len(sys.argv) < 4:
    print "Parameters: {variable parameter}, {values for the constant parameters} {columns of the matrix to use}"
    sys.exit(0)

# argument parsing
folders = [] 
rates = []

variable = sys.argv[1]
constants = sys.argv[2:8]
columns = sys.argv[8:]

# turn the constants into a dict
constants = dict( zip(constants[::2], constants[1::2]))

# parse the folders
for folder in os.listdir('Test'):
    reject = False
    for key, val in constants.iteritems():
        if '%s:%s' % (key, val) not in folder:
            reject = True
            break

    # add the folder relative to the current directory
    if not reject:
        folders.append(os.path.join('Test', folder))

# get the values for variable parameter in the same order as in the folders list
for folder in folders:
    re_string = r'%s:([0-9\.]+)' % variable
    rates.append( float(re.search(re_string, folder).groups()[0]) )

# sort the folders by their rates
ratesAndFolders = zip(rates, folders)
ratesAndFolders = sorted(ratesAndFolders)
rates, folders = zip(*ratesAndFolders)

if(len(columns) == 1):
    colors = ['r']
elif(len(columns) == 2):
    colors = ['r', 'g']
elif(len(columns) == 3):
    colors = ['r', 'g', 'b']
elif(len(columns) == 4):
    colors = ['r', 'g', 'b', 'c']

rcParams['axes.color_cycle'] = colors

hold(True)

i = 0
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
        
        plot(time, averages)
    i+=1

legend()
show()
