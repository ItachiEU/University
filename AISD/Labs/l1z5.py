def findPath(n):
    orderedVertices = topSort(G)
    distances = [0] * (n+1)
    parent = [0] * (n+1)

    for v in orderedVertices:
       for neighbour of v:
          if distances[neighbour] < distances[v] + 1:
             distances[neighbour] = distances[v] + 1
             parent[neighbour] = v

    def generatePath(v):
       result = [v]
       while(parent[v] != 0):
         result.append(parent[v])
         v = parent[v]

       return result

     maxValue, bestVertex = 0,0
     for v in orderedVertices:
        if distances[v] > maxValue:
           maxValue = distances[v]
           bestVertex = v

     return reversed(generatePath(bestVertex))
