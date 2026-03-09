# hex to decimal conversion with hex map dict thing
def hex_to_number(hex_str, negative):
    hex_str = hex_str.upper()[2:]

    hex_map = {
        '0': 0, '1': 1, '2': 2, '3': 3, '4': 4,
        '5': 5, '6': 6, '7': 7, '8': 8, '9': 9,
        'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15
        }

    number = 0
    power = 1

    for hex in reversed(hex_str):
        if hex not in hex_map:
            return None
        number += hex_map[hex] * (power)
        power *= 16

    if negative:
        number *= -1

    return number


# move to helper function, use conv_num to find out if valid and if its a hex
def decimal_to_number(num_str, negative):
    if num_str.count('.') > 1:
        return None

    number = 0

    # if string has a decimal, count how many decimal places and where to
    # start counting by 10^x in arithmetic conversion
    if '.' in num_str:
        decimal_places = -1
        for num in num_str:
            if num == '.':
                decimal_places += 1

            if decimal_places >= 0:
                decimal_places += 1

        place = 10 ** (len(num_str) - decimal_places - 1)
    else:
        place = 10 ** (len(num_str) - 1)

    for num in num_str:
        if num == '.':
            continue
        number += (ord(num) - ord('0')) * place

        # If string has a '.', number will return as a float
        if '.' in num_str:
            place /= 10

        # if string is a normal integer, it wil return as an int
        else:
            place //= 10

    if negative:
        number *= -1

    return number


def conv_num(num_str):
    """ Takes in a string and converts into a base 10 number,
    and returns it. """

    negative = False
    valid_chars = set("0123456789.")

    if num_str[0] == '-':
        negative = True
        num_str = num_str[1:]

    if num_str[:2] == '0x' or num_str[:2] == '0X':
        return hex_to_number(num_str, negative)

    for char in num_str:
        if char not in valid_chars:
            return None

    return decimal_to_number(num_str, negative)


print(conv_num('25.'))
print(conv_num('-67'))
print(conv_num('0Xad4'))
print(conv_num('0xaD4'))
print(conv_num('-0Xad4'))
print(conv_num(25))
