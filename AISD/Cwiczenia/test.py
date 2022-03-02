test = [10, 9, 8, 8, 6, 5, 4, 3, 2, 1, 7]

def partition(arr, l, r):
	pivotIndex = l
	pivot = arr[r]
	for i in range(l, r+1):
		if arr[i] < pivot:
			arr[i], arr[pivotIndex] = arr[pivotIndex], arr[i]
			pivotIndex += 1
	arr[pivotIndex], arr[r] = arr[r], arr[pivotIndex]

	return pivotIndex

def quickSort(arr, l, r):
	if l >= r:
		return
	p = partition(arr, l, r)
	quickSort(arr, l, p-1)
	quickSort(arr, p+1, r)

quickSort(test, 0, len(test)-1)
print(test)