from merge_sort import *
import random
from matplotlib import pyplot as plt
import time


def dist(p,q):
	return ((p[0]-q[0])**2 + (p[1]-q[1])**2)**0.5

def closestSplitPair(Px,Py,delta,n):
	xbar = Px[n//2-1][0]
	Sy = []
	for p in Py:
		if (p[0] >= xbar-delta) and (p[0] <= xbar + delta):
			Sy += [p]

	best_delta = delta
	best_pair = None

	if len(Sy) < 8:
		for j in range(1,len(Sy)-1):
			p = Sy[0]
			q = Sy[j]
			current_dist = dist(p,q)
			if current_dist < best_delta:
				best_delta = current_dist
				best_pair = (p,q)
	else:
		for i in range(len(Sy)-7):
			for j in range(1,8):
				p = Sy[i]
				q = Sy[i+j]
				current_dist = dist(p,q)
				if current_dist < best_delta:
					best_delta = current_dist
					best_pair = (p,q)

	return best_pair

def closestPair(Px,Py,n):
	if n == 2:
		return (Px[0],Px[1])
	else:
		d = n//2
		Qx = Px[0:d]
		Rx = Px[d:n]
		xbar = Px[d-1][0]


		Qy = []
		Ry = []
		for p in Py:
			if p[0] <= xbar:
				Qy += [p]
			else:
				Ry += [p]

		(p1,q1) = closestPair(Qx,Qy,d)
		(p2,q2) = closestPair(Rx,Ry,d)

		# Calculating between p1 and q1, p2 and q2:
		dist1 = dist(p1,q1)
		dist2 = dist(p2,q2)
		if dist1 < dist2:
			delta = dist1
			best_pair = (p1,q1)
		else:
			delta = dist2
			best_pair = (p2,q2)

		best_split = closestSplitPair(Px,Py,delta,d)

		if best_split is not None:
			(p3,q3) = best_split
			if dist(p3,q3) < delta:
				best_pair = (p3,q3)

		return best_pair

def main():
	n = 2**10
	random.seed(1)
	l1 = [random.random() for i in range(n)]
	l2 = [random.random() for i in range(n)]

	P = []
	for i in range(n):
		P.append((l1[i],l2[i]))

	x_sorted = [x[0] for x in P]
	y_sorted = [x[1] for x in P]

	t0 = time.time()

	mergeSort(x_sorted,n)
	mergeSort(y_sorted,n)

	Px = []
	Py = []
	for i in range(n):
		Px += [p for p in P if p[0] == x_sorted[i]]
		Py += [p for p in P if p[1] == y_sorted[i]]

	(p,q) = closestPair(Px,Py,n)

	print('Recursive:',time.time() - t0)


	t0 = time.time()
	# Comparing with Brute Force:
	best_pair = (P[0],P[1])
	best_dist = dist(P[0],P[1])

	for i in range(n):
		for j in range(n):
			if i != j:
				if dist(P[i],P[j]) < best_dist:
					best_dist = dist(P[i],P[j])
					best_pair = (P[i],P[j])

	print('Brute Force:', time.time() - t0)

	plt.scatter([x[0] for x in P],[x[1] for x in P])
	plt.scatter([p[0],q[0]],[p[1],q[1]], color = 'red')
	plt.scatter([best_pair[0][0],best_pair[1][0]],[best_pair[0][1],best_pair[1][1]], color = 'green')
	plt.show()

if __name__ == '__main__':
	main()





