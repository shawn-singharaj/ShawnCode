def remove_odds(arr):
    """ Receives a list of integers and removes all odd numbers and 
        returns a new asorted list (ascending) without making changes
        to the original list (arr). """
    sorted_arr = []
    for num in arr:
        if num % 2 == 0:
            sorted_arr.append(num)
    return sorted(sorted_arr)

arr = [1, 50, 12, 4, 5, 70, 6]

print(remove_odds(arr))
print(arr)