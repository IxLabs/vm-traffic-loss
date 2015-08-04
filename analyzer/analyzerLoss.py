#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

tree = ET.parse('current_status.xml')
root = tree.getroot()

if len(sys.argv) < 3:
	print("Usage: ./analyzer.py vm-name all/information to print")
	sys.exit()
for child in root.findall('info'):
	name = child.find('vm-name')
	if name is None:
		print("Element not found")
	elif name.text == sys.argv[1]:
		print("\nVirtual machine: "+name.text)
		for ar in sys.argv[2:]:
			for elem in tree.iter(tag=ar):
    			if elem is not None:
					print(elem.tag.title(), elem.text.rjust(35-len(elem.tag)))
			print("--------------------")

