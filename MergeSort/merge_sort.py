def mergeSort(x,n):
	if n == 1:
		return x
	else:
		d = n//2
		A = x[0:d]
		B = x[d:n]

		# print(A)
		# print(B)

		mergeSort(A,d)
		mergeSort(B,d)

		i = 0
		j = 0

		for k in range(n):
			# print(k)
			if (i < d) and (j < d):
				if A[i] < B[j]:
					x[k] = A[i]
					i +=1 
				else:
					x[k] = B[j]
					j += 1
			elif (i < d):
				x[k] = A[i]
				i += 1
			elif (j < d):
				x[k] = B[j]
				j += 1

def main():
	x = [4,3,2,1,100,11,6,90]

	mergeSort(x,8)

	print(x)

if __name__ == '__main__':
	main()