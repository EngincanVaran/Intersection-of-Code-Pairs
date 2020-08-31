dic2k = {}
dic3k = {}
dic4k = {}
dic5k = {}

for i in range(2,31):
	if(i%6==1 or i%6==2 or i%6==3 or i%6==4):
		dic2k[i] = int(2*i/3)
		#list2k.append(int(2*i/3))
	else:
		dic2k[i] = int(2*i/3-1)

for i in range(3,31):
	if(i%7==3 or i%7==5):
		dic3k[i] = int(4*i/7)
		#list2k.append(int(2*i/3))
	else:
		dic3k[i] = int(4*i/7 - 1)

for i in range(4,31):
	if(i%15==5 or i%15==9 or i%15==13):
		dic4k[i] = int(8*i/15)
		#list2k.append(int(2*i/3))
	elif(i%15==2 or i%15==3 or i%15==4 or i%15==6 or i%15==10) :
		dic4k[i] = int(8*i/15 - 1)
	else:
		dic4k[i] = 0

for i in range(5,31):
	if(i%31==3 or i%31==5 or i%31==7 or i%31==11 or i%31==19 or i%31==20 or i%31==22 or i%31==26):
		dic5k[i] = int(16*i/31 - 1)
	elif(i%31==4):
		dic5k[i] = int(16*i/31 - 2)
	else:
		dic5k[i] = 0



for x,y in dic5k.items():
	print(x,y)

end = input()