"""CS362 Group Project
Shawn Singharaj
Campbell Carlberg"""

import unittest
from task import conv_num, conv_endian, my_datetime


class TestConvNum(unittest.TestCase):

    def test_int(self):
        self.assertEqual(conv_num('67'), 67)

    def test_float(self):
        self.assertAlmostEqual(conv_num('67.5'), 67.5)

    def test_int_string(self):
        self.assertEqual(conv_num('68'), 68)

    def test_hex_upper(self):
        self.assertEqual(conv_num('0XAD4'), 2772)

    def test_hex_mixed_case(self):
        self.assertEqual(conv_num('0xaD4'), 2772)

    def test_invalid_characters_equals(self):
        self.assertIsNone(conv_num('67 ='))

    def test_invalid_space(self):
        self.assertIsNone(conv_num('12 4'))

    def test_negative(self):
        self.assertEqual(conv_num('-67'), -67)

    def test_negative_hex(self):
        self.assertEqual(conv_num('-0Xad4'), -2772)


class TestConvEndian(unittest.TestCase):

    def test_big_endian(self):
        self.assertEqual(conv_endian(954786, 'big'), '0E 91 A2')

    def test_little_endian(self):
        self.assertEqual(conv_endian(954786, 'little'), 'A2 91 0E')

    def test_negative_little_endian(self):
        self.assertEqual(conv_endian(-954786, endian='little'), '-A2 91 0E')

    def test_negative_big_default(self):
        self.assertEqual(conv_endian(-954786), '-0E 91 A2')

    def test_invalid_endian(self):
        self.assertIsNone(conv_endian(123, 'invalid'))

    def test_zero(self):
        self.assertEqual(conv_endian(0), '00')


class TestMyDatetime(unittest.TestCase):

    def test_epoch(self):
        self.assertEqual(my_datetime(0), '01-01-1970')

    def test_mid_range(self):
        self.assertEqual(my_datetime(123456789), '11-29-1973')

    def test_large_number(self):
        self.assertEqual(my_datetime(9876543210), '12-22-2282')

    def test_very_large_number(self):
        self.assertEqual(my_datetime(201653971200), '02-29-8360')


if __name__ == '__main__':
    unittest.main()
