import numpy as np




def main():
	f = open('median_maintenance_input.txt', 'r') 

	x = np.zeros(10000)

	lines = f.readlines() 
	for i,line in enumerate(lines):
		x[i] = int(line)

	for i in range(1,20,1):
		xtmp = np.sort(x[:i])
		if i % 2 == 0: # if even
			median = xtmp[i//2]
		else:
			median = xtmp[(i+1)//2]
		print(median)


if __name__ == '__main__':
	main()