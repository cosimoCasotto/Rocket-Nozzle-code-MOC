#!/usr/bin/python3

import matplotlib
import matplotlib.pyplot as plt
import numpy as np 
import argparse

parser = argparse.ArgumentParser( description="Simple plotting of nozzles" )
parser.add_argument( '--file',  type=str,  default='./output.txt', help='Name of file to plot')
parser.add_argument( '--png',   type=str,  default='./output.png', help='Name of output PNG')
parser.add_argument( '--color', type=str,  default='blue', help='Color of nozzle')
args = parser.parse_args()

fileName = args.file
pngFile  = args.png 

# 'agg' stands for Anti-Grain Geometry
#matplotlib.use( 'agg' )           
# plt.close('all')

dataMAT  = np.loadtxt(fileName, skiprows=1)
x = dataMAT[:,1]
y = dataMAT[:,2] 
x[np.isnan(x) | np.isinf(x)] = 0
y[np.isnan(y) | np.isinf(y)] = 0


plt.figure(figsize=(6,10))
plt.scatter(x,y,  color='red')
plt.scatter(x,-y, color='red')
#plt.grid()
# Add minor ticks
plt.minorticks_on()

# Customize the minor grid
plt.grid(which='minor', linestyle=':', linewidth=0.3, color='gray')
plt.xlabel('x position')
plt.savefig( pngFile )
plt.show()
plt.close()
