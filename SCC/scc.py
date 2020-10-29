import time
import resource, sys


# Defining global variables:
t = 0 # to keep track of stopping times
s = None # to keep track of a current leader

def readEdgesList(filepath):
	with open(filepath) as f:
		A = f.readlines()

	V = [] # List of vertices
	E = [] # List of edges (2-tuple of vertices)
	S = {} # Dictionary of edges starting from a given node
	inS = {} # Dictionary of edges ending at a given node

	V = list(range(875714))

	for i in range(875714):
		S[i+1] = []
		inS[i+1] = []

	i = 0
	prev_start = 0
	for x in A:
		row = x.replace('\n','').strip().split(' ')
		start = int(row[0])
		end = int(row[1])
		edge = (start, end)
		E.append(edge)

		S[start].append(edge)
		inS[end].append(edge)

	G = {}
	G['V'] = V
	G['E'] = E
	G['S'] = S
	G['inS'] = inS
	G['explored'] = [False]*len(V)
	G['stopping_time_order'] = []
	G['leader'] = [None]*len(V)

	return G


def readAdjacencyListDirected(filepath):
	'''
	This function reads file from filepath, processes it
	and outputs a graph = (set of vertices, set of edges)
	'''
	with open(filepath) as f:
		A = f.readlines()

	V = [] # List of vertices
	E = [] # List of edges (2-tuple of vertices)
	S = {} # Dictionary of edges starting from a given node
	inS = {} # Dictionary of edges ending at a given node

	for x in A:
		print(x)
		# row = x.replace('\n','').split('\t')
		row = x.replace('\n','').strip().split('\t')
		print(row)
		V.append(int(row[0]))

		S[int(row[0])] = []

		for j in range(len(row)-1):
			start = int(row[0])
			end = int(row[j+1])
			edge = (start,end)
			E.append(edge)
			S[start].append(edge)
			if end in inS:
				inS[end].append(edge)
			else: 
				inS[end] = [edge]

	G = {}
	G['V'] = V
	G['E'] = E
	G['S'] = S
	G['inS'] = inS
	G['explored'] = [False]*max(V)
	G['stopping_time_order'] = []
	G['leader'] = [None]*len(V)

	return G

def DFSLoopReversed(G):
	global t
	global s

	t = 0
	s = None
	n = len(G['V'])

	for i in range(n,1,-1):
		if not G['explored'][i-1]:
			s = i
			DFSReversed(G, i)

def DFSReversed(G, i):
	# Marking vertex as explored
	G['explored'][i - 1] = True

	# Looping through edges outgoing from i and performing
	# a recursive DFS:
	for edge in G['inS'][i]:
		j = edge[0]
		if not G['explored'][j-1]:
			DFSReversed(G, j)

	# Incrementing the stopping time and assigning it to the
	# current node
	global t
	t += 1
	G['stopping_time_order'].append(i)

def DFSLoop(G):
	global t
	global s

	t = 0
	s = None
	n = len(G['V'])

	# marking all nodes as unexplored:
	G['explored'] = [False]*n

	# Start exploring nodes according to their stopping
	# time from the first pass of DFS on the reversed graph
	for node in range(n):
		print(node)
		i = G['stopping_time_order'][n-node-1]
		print('start node:',i)
		if not G['explored'][i-1]:
			s = i
			DFS(G, i)

def DFS(G, i):
	print('exploring:', i)

	# Marking vertex as explored
	G['explored'][i - 1] = True

	# Assigning leaders
	G['leader'][i - 1] = s

	# Looping through edges outgoing from i and performing
	# a recursive DFS:
	for edge in G['S'][i]:
		j = edge[1]
		if not G['explored'][j-1]:
			DFS(G, j)

def main():
	sys.setrecursionlimit(10**6)


	# G = readAdjacencyListDirected('small_graph_3.txt')
	t = time.time()
	G = readEdgesList('scc_input.txt')
	# G = readEdgesList('small_graph_4.txt')
	print(time.time() - t)

	DFSLoopReversed(G)
	# print('Stopping time order:', G['stopping_time_order'])
	DFSLoop(G)
	# print(G)
	# print('leader:',G['leader'])

	# Calculating the sizes of SCCs:
	SCCGroups = {}
	for i in range(len(G['V'])):
		if G['leader'][i] in SCCGroups:
			SCCGroups[G['leader'][i]].append(i+1)
		else:
			SCCGroups[G['leader'][i]] = [i+1]

	SSCSizes = []
	for key in SCCGroups:
		SSCSizes.append(len(SCCGroups[key]))

	SSCSizes.sort(reverse = True)
	print(SSCSizes)



if __name__ == '__main__':
	main()









