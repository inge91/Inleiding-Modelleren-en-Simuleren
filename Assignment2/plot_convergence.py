#!/usr/bin/env python

from pylab import *
from argparse import ArgumentParser

parser = ArgumentParser()
parser.add_argument('filenames', metavar='filenames', type=str, nargs='+',
                   help='filenames containing the tables to plot')
args = parser.parse_args()

for filename in args.filenames:
    # load and plot the data
    data = loadtxt(filename, delimiter=',')
    plot(data[:, 0], data[:, 1], label=filename)

    # add the necessary information for a healthy plot
    xlabel("# iteration")
    ylabel("function value")

legend()
show()
