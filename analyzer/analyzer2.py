#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

if len(sys.argv) < 4:
	print("Usage: ./analyzer.py vm-name all/information inputFIle")
	sys.exit()

tree = ET.parse(sys.argv[3])
root = tree.getroot()



for child in root.findall('info'):
	name = child.find('vm-name')
	if name is None:
		print("Element not found")
	elif name.text == sys.argv[1]:
		print("\nVirtual machine: "+name.text)
		for ar in sys.argv[2:]:
			for elem in child.iter(tag=ar):
				print(elem.tag.title(), elem.text.rjust(35-len(elem.tag)))
			print("--------------------")

