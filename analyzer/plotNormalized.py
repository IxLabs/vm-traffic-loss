#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt
import matplotlib.ticker as tick
import numpy as np

if len(sys.argv) < 6:
	print("Usage: ./plotNormalized.py vm-name info(to vary) info(to measure) info(normalize) input")
	sys.exit()
tree = ET.parse(sys.argv[5])
root = tree.getroot()
x = []  
y = []

def y_fmt2(x, y):
    	return '{:2.2e}'.format(x).replace('e-', 'x10^-')

def y_fmt(x, y):
    	return '{:2.2e}'.format(x).replace('e+', 'x10^')

def plotFile(vary, measure):
	global x
	global y
	fig = plt.figure()
	ax = fig.add_subplot(111)
	ax.plot(x, y)
	ax.xaxis.set_major_formatter(tick.FuncFormatter(y_fmt))
	ax.yaxis.set_major_formatter(tick.FuncFormatter(y_fmt))
	#plt.ylabel('recvErrors / total packets received')
	#plt.xlabel('Datagram length')
	#plt.text (0.7, 0.9, 'Constant bandwidth 1Gbit', transform=ax.transAxes)
	#plt.text (0.7, 0.85, '10 minutes tests', transform=ax.transAxes)
	plt.ylim(0, plt.ylim()[1]+plt.ylim()[1]/10)
	plt.grid(True)
	#plt.title ('Influence of UDP Datagram length on UDP recvErrors number')
	plt.show()
	return;

def appendStats( c, vary, measure, normalize):
	resultX = 0
	resultY = 0
	for elem in c.iter(tag=vary):
		resultX = float(elem.text)
	x.append(resultX)
	for elem in c.iter(tag=measure):
		resultY = float(elem.text)
	for elem in c.iter(tag=normalize):
		resultY = resultY / float(elem.text)
	y.append(resultY)
	return;

varyIn = sys.argv[2]
measureIn = sys.argv[3]
normalizeIn = sys.argv[4]
print normalizeIn
print sys.argv[5]
for child in root.findall('info'):
	name = child.find('vm-name')
	if name is None:
		print("Element not found")
	elif name.text == sys.argv[1]:
		appendStats( c = child, vary = varyIn, measure = measureIn, normalize = normalizeIn)
		
print x
print y
plotFile(vary = varyIn, measure = measureIn)




