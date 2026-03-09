"""This file contains test cases for the credit_card_validator.py file."""
import unittest
import random
from credit_card_validator import credit_card_validator


class TestCase(unittest.TestCase):
    """Random testing cases."""

    def test1(self):
        """Random number lengths 15"""
        for _ in range(50000):
            length = 15
            number = ''.join(str(random.randint(0, 9)) for _ in range(length))
            credit_card_validator(number)

    def test2(self):
        """Random number lengths 16"""
        for _ in range(50000):
            length = 16
            number = ''.join(str(random.randint(0, 9)) for _ in range(length))
            credit_card_validator(number)

    def test3(self):
        """Random number lengths 1-14"""
        for _ in range(50000):
            length = random.randint(1, 14)
            number = ''.join(str(random.randint(0, 9)) for _ in range(length))
            credit_card_validator(number)

    def test4(self):
        """Random number lengths 17-30"""
        for _ in range(50000):
            length = random.randint(17, 30)
            number = ''.join(str(random.randint(0, 9)) for _ in range(length))
            credit_card_validator(number)

    def test5(self):
        """4 prefix length 16"""
        for _ in range(50000):
            length = 16
            number = '4' + ''.join(
                str(random.randint(0, 9)) for _ in range(length - 1))
            credit_card_validator(number)

    def test6(self):
        """suffix 258 and length 16"""
        for _ in range(50000):
            length = 16
            number = ''.join(str(random.randint(0, 9)) for _ in range(
                length - 3)) + '258'
            credit_card_validator(number)


if __name__ == "__main__":
    unittest.main(verbosity=3)
