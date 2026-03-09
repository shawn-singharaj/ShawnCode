"""
Shawn Singharaj - conv_num, conv_endian
Campbell Carlberg - my_datetime, conv_endian
"""


def hex_to_number(hex_str, negative):
    """
    Convert a hex string (with 0x prefix) to an integer.

    Removes "0x", uses a lookup map, and applies base-16 math.
    """
    hex_str = hex_str.upper()[2:]

    hex_map = {
        '0': 0, '1': 1, '2': 2, '3': 3, '4': 4,
        '5': 5, '6': 6, '7': 7, '8': 8, '9': 9,
        'A': 10, 'B': 11, 'C': 12, 'D': 13,
        'E': 14, 'F': 15,
    }

    number = 0
    power = 1

    for hex_char in reversed(hex_str):
        if hex_char not in hex_map:
            return None
        number += hex_map[hex_char] * power
        power *= 16

    if negative:
        number *= -1

    return number


def decimal_to_number(num_str, negative):
    """
    Convert a decimal string into an int or float.

    Supports at most one decimal point. Uses manual ASCII conversion.
    """
    if num_str.count('.') > 1:
        return None

    number = 0

    if '.' in num_str:
        decimal_places = -1
        for ch in num_str:
            if ch == '.':
                decimal_places += 1
            if decimal_places >= 0:
                decimal_places += 1

        place = 10 ** (len(num_str) - decimal_places - 1)
    else:
        place = 10 ** (len(num_str) - 1)

    for ch in num_str:
        if ch == '.':
            continue

        number += (ord(ch) - ord('0')) * place

        if '.' in num_str:
            place /= 10.0
        else:
            place //= 10

    if negative:
        number *= -1

    return number


def conv_num(num_str):
    """
    Convert a string to an int, float, or hex number.

    Supports:
        - Regular decimal strings
        - Hex strings starting with 0x or 0X
        - Leading negative sign
    """
    if not isinstance(num_str, str):
        return None

    if len(num_str) == 0:
        return None

    negative = False
    valid_chars = set("0123456789.")

    if num_str[0] == '-':
        negative = True
        num_str = num_str[1:]

    if len(num_str) >= 2 and num_str[:2].lower() == '0x':
        return hex_to_number(num_str, negative)

    for char in num_str:
        if char not in valid_chars:
            return None

    return decimal_to_number(num_str, negative)


def is_leap_year(year):
    if year % 400 == 0:
        return True
    if year % 100 == 0:
        return False
    return year % 4 == 0


def days_in_month(month, year):
    if month in {1, 3, 5, 7, 8, 10, 12}:
        return 31
    if month in {4, 6, 9, 11}:
        return 30
    if month == 2:
        return 29 if is_leap_year(year) else 28
    return 0


def my_datetime(num_sec):
    """
    Convert seconds since epoch (Jan 1, 1970) into MM-DD-YYYY format.
    """
    seconds_per_day = 86400

    days = num_sec // seconds_per_day

    year = 1970
    month = 1
    day = 1

    while days > 0:
        dim = days_in_month(month, year)

        if days >= dim - day + 1:
            days -= dim - day + 1
            day = 1
            month += 1

            if month > 12:
                month = 1
                year += 1
        else:
            day += days
            days = 0

    return f"{month:02d}-{day:02d}-{year}"


def conv_endian(num, endian='big'):
    """
    Convert an integer into a hex string formatted by endian type.

    endian:
        - "big"
        - "little"
    """
    if endian not in ('big', 'little'):
        return None

    negative = num < 0
    if negative:
        num = -num

    if num == 0:
        return "00"

    hex_chars = "0123456789ABCDEF"
    result = ""
    n = num

    while n > 0:
        result = hex_chars[n % 16] + result
        n //= 16

    if len(result) % 2 == 1:
        result = "0" + result

    bytes_list = [result[i:i + 2] for i in range(0, len(result), 2)]

    if endian == 'little':
        bytes_list.reverse()

    result = " ".join(bytes_list)

    if negative:
        result = "-" + result

    return result
