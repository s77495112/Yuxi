class Solution(object):
    def singleNonDuplicate(self, nums):
        return reduce(operator.ixor, numsi)

class Solution(object):
    def singleNonDuplicate(self, nums):
		left, right = 0, len(nums) - 1
		while(left < right):
			mid = (left + right) // 2	
			if(nums[mid] == nums[mid^1]):
				left = mid + 1
			else:
				right = mid
		return nums[left]