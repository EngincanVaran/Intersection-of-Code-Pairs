#LCD codes of dimension 2
list2k = []
for i in range(2,50):
	if(i%6==1 or i%6==2 or i%6==3 or i%6==4):
		list2k.append(int(2*i/3))
	else:
		list2k.append(int(2*i/3 - 1))
print("LCD(n,2,d(n,2):")
print(list2k)

print("")

#LCD codes of dimension 3
list3k = []
for i in range(3,50):
	if(i%7==3 or i%7==5):
		list3k.append(int(4*i/7))
	else:
		list3k.append(int(4*i/7 - 1))
print("LCD(n,3,d(n,3):")
print(list3k)

print("")