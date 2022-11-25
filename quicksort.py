from random import randrange


def partition(unsorted, left, right):
    pivot_index = randrange(left, right)
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
    user_input = input().strip().split(' ')
    quicksort(user_input, 0, len(user_input) - 1)
    print(*user_input, sep= ' ') 
