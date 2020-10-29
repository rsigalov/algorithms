import random
import time
from copy import deepcopy


def readAdjacencyList(filepath):
	'''
	This function reads file from filepath, processes it
	and outputs a graph = (set of vertices, set of edges)
	'''
	with open(filepath) as f:
		A = f.readlines()

	V = [] # List of vertices
	E = [] # List of edges (2-tuple of vertices)
	S = {} # Dictionary of edges of each node

	for x in A:
		row = x.split('\t')
		V.append(int(row[0]))

		S[int(row[0])] = []

		for j in range(len(row)-1):
			if row[1+j] != '\n':
				E.append((int(row[0]),int(row[1+j])))

				edge_min = min(int(row[0]),int(row[1+j]))
				edge_max = max(int(row[0]),int(row[1+j]))
				edge = (edge_min,edge_max)
				S[int(row[0])].append(edge)

	# Removing double counting of edges, i.e. leaving
	# only edges (v1, v2) where v1 < v2:
	E = [x for x in E if x[0] < x[1]]

	return (V,E,S)

def modifyAbsorptionDict(absorbtionDict, edge):
	absorber = min(edge)
	absorbed = max(edge)

	if absorbed in absorbtionDict.keys():
		# if absorbed nodes absorbed somebody before, reassing
		# previously absorbed nodes to the current absorber
		old_absorbed = absorbtionDict[absorbed]

		if absorber in absorbtionDict.keys():
			absorbtionDict[absorber] += [absorbed] + old_absorbed
		else:
			absorbtionDict[absorber] = [absorbed] + old_absorbed

		absorbtionDict.pop(absorbed)
	else:
		if absorber in absorbtionDict.keys():
			absorbtionDict[absorber] += [absorbed]
		else:
			absorbtionDict[absorber] = [absorbed]


def contractEdge(G, edge):
	'''
	Takes a graph as an input and an edge
	'''

	# print('Before:',G)
	# print('Edge to remove', edge)

	absorber = min(edge)
	absorbed = max(edge)

	# Removing absorbed vertex from the graph
	G[0].remove(absorbed)

	# List of edges associated with the absorbed vertex
	absorbed_edges = [x for x in G[2][absorbed]]
	# print('Absrobed edges:', absorbed_edges)

	# Removing a dictionary key associated with the absorbed node
	G[2].pop(absorbed, None)

	# Removing absorbed edges from graph:
	for x in absorbed_edges:
		# Removing from the list of edges
		# print(x)
		G[1].remove(x)

		# Removing from dictionaries of other nodes:
		if x[0] == absorbed:
			edge_remove_min = min((absorbed, x[1]))
			edge_remove_max = max((absorbed, x[1]))
			edge_remove = (edge_remove_min, edge_remove_max)
			# print(G[2][x[1]])
			G[2][x[1]].remove(edge_remove)
		else:
			edge_remove_min = min((absorbed, x[0]))
			edge_remove_max = max((absorbed, x[0]))
			edge_remove = (edge_remove_min, edge_remove_max)
			# print(G[2][x[0]])
			# print(edge_remove)
			G[2][x[0]].remove(edge_remove)

	# Adding edges to the absorber vertex. Modifying the list
	# so we don't add self-edges
	absorbed_edges = [x for x in absorbed_edges if x != (absorber,absorbed)]
	for x in absorbed_edges:
		if x[0] == absorbed:
			edge_add_min = min((absorber, x[1]))
			edge_add_max = max((absorber, x[1]))
			edge_add = (edge_add_min, edge_add_max)
			G[1].append(edge_add)
			G[2][absorber].append(edge_add)
			G[2][x[1]].append(edge_add)
		else:
			edge_add_min = min((absorber, x[0]))
			edge_add_max = max((absorber, x[0]))
			edge_add = (edge_add_min, edge_add_max)
			G[1].append(edge_add)
			G[2][absorber].append(edge_add)
			G[2][x[0]].append(edge_add)

def randomContraction(G):
	absorbtionDict = {}

	# random.seed(19960202)

	while len(G[0]) > 2:
		edge = random.choice(G[1])
		contractEdge(G, edge)
		modifyAbsorptionDict(absorbtionDict, edge)

	edgeCrossings = len(G[1])

	return (edgeCrossings, absorbtionDict)


def main():
	# G = readAdjacencyList('kragerMinCut.txt')
	G = readAdjacencyList('small_graph.txt')
	print('Number of nodes:', len(G[0]))
	print('Number of edges:', len(G[1]))
	print()
	
	N = 200
	edgeCrossingsMin = len(G[1])

	for i in range(N):
		# Gcopy = (list(G[0]), list(G[1]), dict(G[2]))
		Gcopy = deepcopy(G)

		# t = time.time()
		contractionResult = randomContraction(Gcopy)
		# print(time.time() - t, contractionResult[0])

		if contractionResult[0] < edgeCrossingsMin:
			edgeCrossingsMin = contractionResult[0]
			absorbtionDict = contractionResult[1]

	print('Min Edge Crossings:', edgeCrossingsMin)

if __name__ == '__main__':
	main()

