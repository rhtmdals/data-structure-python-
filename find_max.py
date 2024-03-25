array = []

for j in range(10):
    array.append(int(input()))
    
def find_max_recursive(array, max, index):
    if index > 9:
        return max
    
    if max < array[index]:
        max = array[index]
        print(max)
        index += 1
        return find_max_recursive(array, max, index)

    else:
        index += 1
        return find_max_recursive(array, max, index)
    
def find_max_iterative(array, max):
    for i in range(10):
        if max < array[i]:
            max = array[i]
    return max

print("재귀버전 최대값 탐색", find_max_recursive(array, 0, 0))
print("반복버전 최대값 탐색", find_max_iterative(array, 0))