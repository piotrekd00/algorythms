from random import randint, randrange
from sys import setrecursionlimit
from timeit import default_timer

def partition(unsorted, left, right):
    pivot_index = randrange(right)
    unsorted[left], unsorted[pivot_index] = unsorted[pivot_index], unsorted[left]
    pivot = unsorted[right]
    current_index = left
    for i in range(left, right):
        if unsorted[i] < pivot:
            unsorted[current_index], unsorted[i] = unsorted[i], unsorted[current_index]
            current_index += 1
    unsorted[right], unsorted[current_index] = unsorted[current_index], unsorted[right]
    return current_index


def quicksort(unsorted, left, right):
    if left < right:
        pivot_index = partition(unsorted, left, right)
        quicksort(unsorted, left, pivot_index - 1)
        quicksort(unsorted, pivot_index + 1, right)


if __name__ == '__main__':
    setrecursionlimit(100000)
    user_input = int(input())
    unsorted_list = [randint(0, 100) for _ in range(user_input)]
    start = default_timer()
    quicksort(unsorted_list, 0, len(unsorted_list) - 1)
    end = default_timer()
    print((end - start)*1000)
