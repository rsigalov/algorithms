

def mergeAndCountInv(x_left, x_right, nl, nr):
	'''
	Takes as inputs left and right arrays to merge
	as well as their size
	'''
	x_merged = []
	inv = 0
	i = 0
	j = 0
	for k in range(nl+nr):
		if (i < nl) and (j < nr):
			if x_left[i] < x_right[j]:
				x_merged.append(x_left[i])
				i += 1
			else:
				x_merged.append(x_right[j])
				j += 1
				inv += nl - i
		elif (i < nl):
			x_merged.append(x_left[i])
			i += 1
		elif (j < nr):
			x_merged.append(x_right[j])
			j += 1

	return (x_merged, inv)

def sortAndCountInv(x, n):
	if n == 1:
		# In base return the same array and zero inversions
		return (x, 0) 
	else:
		# Split into two arrays:
		x_left = x[0:n//2]
		x_right = x[n//2:n]

		nl = n//2
		nr = n - nl

		# Call the function recursively on each subarray.
		(x_left, inv_left) = sortAndCountInv(x_left, nl)
		(x_right, inv_right) = sortAndCountInv(x_right, nr)
		(x, inv_split) = mergeAndCountInv(x_left, x_right, nl, nr)

		inv_total = inv_left + inv_right + inv_split

		return (x, inv_total)

def main():
	# Reading file with a column of number from 1 to 1000000
	with open('integer_array.txt') as f:
		A = f.readlines()

	A = [int(x.strip()) for x in A]

	print(sortAndCountInv(A, len(A))[1])

if __name__ == '__main__':
	main()








