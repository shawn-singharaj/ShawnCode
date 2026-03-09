"""This file contains test cases for the ccontrived_func.py file."""
import unittest
from contrived_func import contrived_func


class TestCase(unittest.TestCase):

    def test1(self):
        contrived_func(3)

    def test2(self):
        contrived_func(1)

    def test3(self):
        contrived_func(27)

    def test4(self):
        contrived_func(243)

    def test5(self):
        contrived_func(2)

    def test6(self):
        contrived_func(40)

    def test7(self):
        contrived_func(0)

    def test8(self):
        contrived_func(35)


if __name__ == '__main__':
    unittest.main(verbosity=2)
