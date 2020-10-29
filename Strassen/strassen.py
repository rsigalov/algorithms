import numpy as np


def matPrint(X, n):
	for i in range(n):
		for j in range(n):
			print(X[i][j], end = ' ')
		print()

def matAdd(X, Y, n):
	'''
	Adding square matrices of equal dimension
	'''

	SUM = []
	for i in range(n):
		row = []
		for j in range(n):
			row.append(X[i][j] + Y[i][j])
		SUM.append(row)

	return SUM

def matSubtract(X, Y, n):
	'''
	Subtracting square matrices of equal dimension
	'''

	SUM = []
	for i in range(n):
		row = []
		for j in range(n):
			row.append(X[i][j] - Y[i][j])
		SUM.append(row)

	return SUM


def matMult(X, Y, n):
	if n == 1:
		return [[X[0][0] * Y[0][0]]]
	else:
		# Splitting matrices into (nearly havles):
		d = n//2
		A = [[X[i][j] for j in range(d)] for i in range(d)]
		B = [[X[i][j] for j in range(d,n)] for i in range(d)]
		C = [[X[i][j] for j in range(d)] for i in range(d,n)]
		D = [[X[i][j] for j in range(d,n)] for i in range(d,n)]

		E = [[Y[i][j] for j in range(d)] for i in range(d)]
		F = [[Y[i][j] for j in range(d,n)] for i in range(d)]
		G = [[Y[i][j] for j in range(d)] for i in range(d,n)]
		H = [[Y[i][j] for j in range(d,n)] for i in range(d,n)]

		# Doing 7 recursive calls according to Strassen's Algorithm
		P1 = matMult(A, matSubtract(F,H,d),d)
		P2 = matMult(matAdd(A,B,d),H,d)
		P3 = matMult(matAdd(C,D,d),E,d)
		P4 = matMult(D, matSubtract(G,E,d),d)
		P5 = matMult(matAdd(A,D,d),matAdd(E,H,d),d)
		P6 = matMult(matSubtract(B,D,d),matAdd(G,H,d),d)
		P7 = matMult(matSubtract(A,C,d),matAdd(E,F,d),d)

		# Combining results of recursive calls:
		XY11 = matAdd(matSubtract(matAdd(P4,P5,d),P2,d),P6,d)
		XY12 = matAdd(P1,P2,d)
		XY21 = matAdd(P3,P4,d)
		XY22 = matSubtract(matSubtract(matAdd(P1,P5,d),P3,d),P7,d)

		XY1 = [XY11[i] + XY12[i] for i in range(d)]
		XY2 = [XY21[i] + XY22[i] for i in range(d)]
		XY = XY1 + XY2

		return XY

def main():
	X = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
	Y = [[17,18,19,20],[21,22,23,24],[25,26,27,28],[29,30,31,32]]

	# print(Y[1][3])

	matPrint(X, 4)
	print()
	matPrint(Y, 4)
	print()
	# matPrint(matAdd(X,Y,4),4)
	# print()
	# matPrint(matSubtract(X,Y,4),4)

	matPrint(matMult(X, Y, 4),4)
	print()
	matPrint(np.array(X).dot(np.array(Y)),4)

if __name__ == '__main__':
	main()










