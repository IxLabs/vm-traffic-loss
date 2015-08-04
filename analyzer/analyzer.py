#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

tree = ET.parse('info_settings_out.xml')
root = tree.getroot()

def printme( c, info):
	if info != 'all':
		#print( c.tag, info)
		subElement = c.find(str(info))
		if subElement is None:
			print("Cannot find info: "+info)
			return;
		else:
			children = list(subElement)
			if len(children) == 0:
				print(subElement.tag.title(), subElement.text.rjust(35-len(subElement.tag)))
			else:
				print("\n"+subElement.tag.title())
				for i in children:
					printme( c = subElement, info = i.tag)
	else:
		children = list(c)
		for i in children:
			if i.tag != 'vm-name':
				print("\n--------------------\n")
				printme( c = c, info = i.tag)

	return;

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
			printme( c = child, info = ar)
			print("--------------------")

