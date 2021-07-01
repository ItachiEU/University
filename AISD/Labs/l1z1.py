
def maxPath(root):
    return helper(root)[0]


def helper(node):
    ''' 
       returns a pair of values: (maxClosedPath, maxOpenPath)
    '''
    if node is None:
        return 0, 0
    if node.left is None and node.right is None:
        return 0, 0

    maxDoneLeft, maxOpenLeft = helper(node.left)
    maxDoneRight, maxOpenRight = helper(node.right)

    add = 0
    if root.left:
        add += 1
    if root.right:
        add += 1

    maxClosedPath = max(maxDoneLeft, maxDoneRight,
                        add + maxOpenLeft + maxOpenRight)
    maxOpenPath = max(maxOpenLeft, maxOpenRight) + 1

    return maxClosedPath, maxOpenPath
