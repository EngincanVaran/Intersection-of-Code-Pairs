import math

k = 8
n = 25
d = 11
sum = 0

for i in range(0,k):
	sum += math.ceil( d /(2**i))

if( n < sum):
	print("NO\t" + str(sum))
else:
	print("YES\t" + str(sum))

#distance = math.floor( n * ( 2**(k-1) ) / ( (2**k) - 1 ) )
#print(distance)