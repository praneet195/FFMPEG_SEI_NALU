import os
import re
import sys
import cv2
import time
import hashlib 
import glob
import json
import SEINalExtractor as e
import np_opencv_module as npcv
import binascii as bn
import string
from string import printable



if __name__=="__main__":
	while(True):
		printable = set(string.printable)
		frame_num=0
		fmv=e.FMV(2,sys.argv[1])
		frame_dict={}
		fmv.connect(True)
		# print(fmv.getFPS())
		t1=time.time()
		frame_num=fmv.extract_frame_with_sei()
		while(frame_num==fmv.get_current_frame_number()):
			frame_num=fmv.extract_frame_with_sei()
			cvmat=fmv.getMAT()
			#pkt_data=fmv.getPacketData();
			sei=fmv.getSEI()
			sei=sei.strip()
			sei=filter(lambda x: x in printable, sei)
			print(" SEI MARKER: "+bn.unhexlify(sei)+"\n")
			cv2.imshow("Live Feed", cvmat)
			k = cv2.waitKey(10) & 0xFF
			if k == ord('q'):
				print("Exiting: You pressed 'q'")
		break
	
