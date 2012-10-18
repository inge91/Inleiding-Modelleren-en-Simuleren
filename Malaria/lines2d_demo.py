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
for folder in os.listdir('Test4'):
    reject = False
    for key, val in constants.iteritems():
        if '%s:%s' % (key, val) not in folder:
            reject = True
            break

    # add the folder relative to the current directory
    if not reject:
        folders.append(os.path.join('Test4', folder))

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

# lookup table to use as plotting labels
column_meanings = {
    '0': 'susceptible humans',
    '1': 'infected humans',
    '2': 'immune humans',
    '3': 'susceptible mosquitoes',
    '4': 'infected mosquitoes',
    '5': 'dead people',
}

i = 0
plots = []
for folder in folders:
    measurements = []
    for filename in os.listdir(folder):
    #    print filename
        fpath = os.path.join(folder, filename)
        measurements.append( loadtxt(fpath) )

    #print measurements
    # for simplicity, just truncate the graph to the shortest of the runs
    print measurements
    time = min(measurements, key=lambda x: x.shape[0])[:, 6]
    #print time
    # convert the time to ints for convenience
    time = [int(t) for t in time]

    # collect average and standard deviation for the wanted statistic (infected
    # humans in this case) at teach time
    for column in columns:
        averages = []
        for t in time:
            ms = []
            for measurement in measurements:
                ms.append(measurement[t, column])
        
            averages.append( average(ms) )
        
        # append the first element of the tuple returned by 'plot' to the plots
        # list, for drawing the legend later
        print len(time)
        plots.append( plot(time, averages, label=column_meanings[column])[0] )
    i += 1

xlabel('time')
ylabel('value')

# construct the legend, making sure every color is only displayed once
unique_plots = []
used_labels = []
for pl in plots:
    if pl.get_label() not in used_labels:
        used_labels.append(pl.get_label())
        unique_plots.append(pl)

legend(unique_plots, [p.get_label() for p in unique_plots])

show()
