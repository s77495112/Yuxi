class Solution(object):
    def simplifyPath(self, path):
		stack = list()
		for p in path.split('/'):
			if(p == '..'):
				if(stack):
					stack.pop()
			elif(p and p != '.'):
				stack.append(p)
		return '/' + '/'.join(stack)
