n = int(input("Enter the n value: "))

dic2k = {}
dic3k = {}

for i in range(2,n):
	if(i%6==1 or i%6==2 or i%6==3 or i%6==4):
		dic2k[i] = int(2*i/3)
		#list2k.append(int(2*i/3))
	else:
		dic2k[i] = int(2*i/3-1)

for i in range(3,n):
	if(i%7==3 or i%7==5):
		dic3k[i] = int(4*i/7)
		#list2k.append(int(2*i/3))
	else:
		dic3k[i] = int(4*i/7 - 1)

Menu = "MENU \n1. Show the table for 2 dimension. \n2. Show the table for 3 dimension. \n"
print(Menu)
choose = input("Please enter what you want to do: ")

if(choose == "1"):
	print("LCD(n,2,d(n,2):")
	for x,y in dic2k.items():
		print(x,y)
elif(choose == "2"):
	print("LCD(n,3,d(n,3):")
	for x,y in dic3k.items():
		print(x,y)

end = input()