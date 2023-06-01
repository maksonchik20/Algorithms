"""
Если знаем сколько максимум элементов в массиве с положительными числами
за O(n+m)где m — число возможных значений, n — число элементов в массиве
"""

def count_sort(array, n):
    m = [0] * n
    for k in array:
        m[k] += 1
    result = []
    for i in range(len(m)):
        while m[i] != 0:
            result.append(i)
            m[i] -= 1
    return result

print(count_sort([3, 2, 5, 1, 2, 4, 5], 7))


