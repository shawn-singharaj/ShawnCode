"""This file contains test cases for the credit_card_validator.py file.
Grouped by methods."""
import unittest
from credit_card_validator import credit_card_validator


class TestCase(unittest.TestCase):
    """Test cases."""

    # Tests 0 are common mistakes while inputting/error guessing.
    def test0(self):
        """Empty.
        Common mistakes while inputting/error guessing."""
        num = ""
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test0a(self):
        """One digit.
        Common mistakes while inputting/error guessing."""
        num = "0"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test0b(self):
        "Char."
        "Common mistakes while inputting/error guessing."
        num = "a"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test0c(self):
        """Too long.
        Common mistakes while inputting/error guessing."""
        num = "00000000000000000000000000000"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test0d(self):
        """Int.
        Common mistakes while inputting/error guessing."""
        num = 411111111111111
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test0e(self):
        """Same digits.
        Common mistakes while inputting/error guessing."""
        num = "111111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    # Tests 1-4 are boundary tests and luhn validators by card provider.
    def test1(self):
        """Valid Visa (Prefix 4, length 16).
        Boundary Test."""
        num = "4111111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1a(self):
        """InValid Visa (Prefix 5, length 16).
        Boundary Test."""
        num = "5111111111111118"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1b(self):
        """InValid Visa (Prefix 3, length 16).
        Boundary Test."""
        num = "3111111111111113"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1c(self):
        """InValid Visa luhn (Prefix 5, length 16).
        Boundary Test."""
        num = "5111111111111117"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1d(self):
        """InValid Visa luhn (Prefix 3, length 16).
        Boundary Test."""
        num = "3111111111111112"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1e(self):
        """Valid Visa invalid luhn (Prefix 4, length 16).
        Boundary Test."""
        num = "4111111111111112"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1f(self):
        """Valid Visa (Prefix 4, length 13).
        Boundary Test."""
        num = "4111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test1g(self):
        """Valid Visa (Prefix 4, length 19).
        Boundary Test."""
        num = "4111111111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2(self):
        """Valid Mastercard (Length 16, 51 to 55 prefix).
        Boundary Test."""
        num = "5555555555554444"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2a(self):
        """Valid Mastercard (Length 16, 51 to 55 prefix).
        Boundary Test."""
        num = "5111111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2b(self):
        """Valid Mastercard (Length 16, between 51 to 55 prefix).
        Boundary Test."""
        num = "5255555555554447"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2c(self):
        """InValid Mastercard (Length 16, 50 prefix).
        Boundary Test."""
        num = "5012345678910111"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2d(self):
        """InValid Mastercard (Length 16, 56 prefix).
        Boundary Test."""
        num = "5612345678910118"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2e(self):
        """Valid Mastercard invalid luhn(Length 16, 51 to 55 prefix).
        Boundary Test."""
        num = "5111111111111110"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2f(self):
        """Valid Mastercard invalid luhn(Length 16, 51 to 55 prefix).
        Boundary Test."""
        num = "5255555555554445"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2g(self):
        """Valid Mastercard invalid luhn (Length 16, 51 to 55 prefix).
        Boundary Test."""
        num = "555555555555440"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2h(self):
        """Valid Mastercard (Length 16, between 51 to 55 prefix).
        Boundary Test."""
        num = "5455555555554444"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2i(self):
        """Valid Mastercard (Length 13, between 51 to 55 prefix).
        Boundary Test."""
        num = "5455555555554"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test2j(self):
        """Valid Mastercard (Length 19, between 51 to 55 prefix).
        Boundary Test."""
        num = "54555555555544444444"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3(self):
        """Valid Mastercard (Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2221000000000009"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3a(self):
        """Valid Mastercard (Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2720000000000005"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3b(self):
        """Valid Mastercard (Length 16, between prefix 2221 to 2720).
        Boundary Test."""
        num = "2520000000000007"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3c(self):
        """InValid Mastercard (Length 16, prefix 2220).
        Boundary Test."""
        num = "2220000000000000"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3d(self):
        """InValid Mastercard (Length 16, prefix 2721).
        Boundary Test."""
        num = "2721000000000004"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3e(self):
        """Valid Mastercard invalid luhn(Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2221000000000000"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3f(self):
        """Valid Mastercard invalid luhn(Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2720000000000003"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3g(self):
        """Valid Mastercard invalid luhn(Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2520000000000000"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3h(self):
        """Valid Mastercard (Length 16, between prefix 2221 to 2720).
        Boundary Test."""
        num = "2465000000000004"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test3i(self):
        """Valid Mastercard (Length 16, prefix 2221 to 2720).
        Boundary Test."""
        num = "2465000000000005"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4(self):
        """Valid American Express (Length 15, prefix 34 to 37).
        Boundary Test."""
        num = "341111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4a(self):
        """Valid American Express (Length 15, between prefix 34 to 37).
        Boundary Test."""
        num = "351111111111118"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4b(self):
        """Valid American Express (Length 15, prefix 34 to 37).
        Boundary Test."""
        num = "378282246310005"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4c(self):
        """InValid American Express (Length 15, prefix 33).
        Boundary Test."""
        num = "331111111111113"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4d(self):
        """InValid American Express (Length 15, prefix 38).
        Boundary Test."""
        num = "381111111111112"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4e(self):
        """Valid American Express invalid luhn (Length 15, prefix 34 to 37).
        Boundary Test."""
        num = "341111111111110"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4f(self):
        """Valid American Express invalid luhn (Length 15, prefix 34 to 37).
        Boundary Test."""
        num = "351111111111110"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4g(self):
        """Valid American Express invalid luhn (Length 15, prefix 34 to 37).
        Boundary Test."""
        num = "378282246310000"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4h(self):
        """Valid American Express (Length 15, between prefix 34 to 37).
        Boundary Test."""
        num = "351111111111118"
        self.assertTrue(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test4i(self):
        """inValid American Express (Length 16, prefix 34 to 37).
        Boundary Test."""
        num = "3411111111111111"
        self.assertFale(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    # Tests 5-49 are error guessing.
    def test5(self):
        """Invalid Visa (Length 15 < 16, prefix 4).
        Error guessing."""
        num = "498765432112345"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test6(self):
        """Invalid American Express (Length 16 > 15, prefix 35).
        Error guessing."""
        num = "3598765432112345"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test7(self):
        """Invalid Mastercard (Length 15 < 16, prefix 50 < 51).
        Error guessing."""
        num = "50123456789101112"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test8(self):
        """Invalid prefix and length 17.
        Error guessing."""
        num = "12345678987654321"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test9(self):
        """Invalid prefix and length 18.
        Error guessing."""
        num = "0912398612647123123"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test10(self):
        """Invalid Mastercard (Length 16, prefix 2721 > 2720).
        Error guessing."""
        num = "2721123456789012"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test11(self):
        """Invalid American Express (Length 14 < 15, prefix 38).
        Error guessing."""
        num = "38123456789123"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test12(self):
        """Invalid American Express (Length 14 < 15).
        Error guessing."""
        num = "34111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test13(self):
        """Valid Visa prefix but wrong length.
        Error guessing."""
        num = "4123456789"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test18(self):
        """Whitespace around valid number.
        Error guessing."""
        num = " 4111111111111111 "
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test19(self):
        """Non digit -.
        Error guessing."""
        num = "4111-1111-1111-1111"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test14(self):
        """Input with all zeros (valid length but invalid number).
        Error guessing."""
        num = "0000000000000000"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num='{num}')"
        )

    def test15(self):
        """Input is non-numeric (letters included).
        Error guessing."""
        num = "4111a11111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num='{num}')"
        )

    def test188(self):
        """Input with spaces (should be invalid even if digits valid).
        Error guessing."""
        num = "4111 1111 1111 1111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num='{num}')"
        )

    def test20(self):
        "Char."
        "Error guessing."
        num = "aaaaaaaaaaaaaaaaa"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test21(self):
        """InValid Visa (Prefix 6, length 16).
        Error guessing."""
        num = "6111111111111116"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test22(self):
        """InValid Visa (Prefix 7, length 16).
        Error guessing."""
        num = "7111111111111114"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test23(self):
        """InValid Visa (Prefix 8, length 16).
        Error guessing."""
        num = "8111111111111112"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test24(self):
        """InValid Visa (Prefix 9, length 16).
        Error guessing."""
        num = "9111111111111110"
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test25(self):
        """Null.
        Error guessing."""
        num = None
        self.assertFalse(
            credit_card_validator(num),
            msg='Does not meet the requirements (num={})'.format(num)
        )

    def test111(self):
        """Invalid: Prefix only (3).
        Error guessing."""
        num = "3"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test211(self):
        """Invalid: Prefix only (5).
        Error guessing."""
        num = "5"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test311(self):
        """Invalid: Prefix only (50).
        Error guessing."""
        num = "50"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test411(self):
        """Invalid: Prefix only (56).
        Error guessing."""
        num = "56"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test51(self):
        """Invalid: Prefix only (2220).
        Error guessing."""
        num = "2220"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test61(self):
        """Invalid: Prefix only (2721).
        Error guessing."""
        num = "2721"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test71(self):
        """Invalid: Prefix only (33).
        Error guessing."""
        num = "33"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test81(self):
        """Invalid: Prefix only (38).
        Error guessing."""
        num = "38"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test91(self):
        """Invalid: Prefix only (4).
        Error guessing."""
        num = "4"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test34(self):
        """Invalid: Empty string.
        Error guessing."""
        num = ""
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test35(self):
        """Invalid: Too long number.
        Error guessing."""
        num = "41111111111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test36(self):
        """Valid Visa (Prefix 4, length 16).
        Error guessing."""
        num = "4111111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test37(self):
        """Valid Mastercard (Prefix 51, length 16).
        Error guessing."""
        num = "5111111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test38(self):
        """Valid Mastercard (Prefix 55, length 16).
        Error guessing."""
        num = "5555555555554444"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test39(self):
        """Valid Mastercard (Prefix 2221, length 16).
        Error guessing."""
        num = "2221000000000009"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test40(self):
        """Valid Mastercard (Prefix 2720, length 16).
        Error guessing."""
        num = "2720999999999993"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test41(self):
        """Valid American Express (Prefix 34, length 15).
        Error guessing."""
        num = "341111111111111"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test42(self):
        """Valid American Express (Prefix 37, length 15).
        Error guessing."""
        num = "378282246310005"
        self.assertTrue(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test43(self):
        """Invalid Visa (Prefix 4, wrong length 15).
        Error guessing."""
        num = "411111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test44(self):
        """Invalid Mastercard (Prefix 50).
        Error guessing."""
        num = "5011111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test45(self):
        """Invalid Mastercard (Prefix 56).
        Error guessing."""
        num = "5611111111111111"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test46(self):
        """Invalid Mastercard (Prefix 2220).
        Error guessing."""
        num = "2220000000000008"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test47(self):
        """Invalid Mastercard (Prefix 2721).
        Error guessing."""
        num = "2721999999999994"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test48(self):
        """Invalid American Express (Prefix 33).
        Error guessing."""
        num = "331111111111113"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test49(self):
        """Invalid American Express (Prefix 38).
        Error guessing."""
        num = "381111111111112"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test50(self):
        """Amex but too long (16).
        Error guessing."""
        num = "3434343434343434"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test511(self):
        """Visa prefix with short length.
        Boundary testing."""
        num = "455673758689982"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test52(self):
        """Bug 8: Valid Mastercard prefix (51), length 15, valid checksum.
        Boundary testing."""
        num = "511111111111118"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )

    def test53(self):
        """Bug 9: Prefix 2721, length 17, valid checksum.
        Boundary testing."""
        num = "27210000000000006"
        self.assertFalse(
            credit_card_validator(num),
            msg=f"Does not meet the requirements (num={num})"
        )


if __name__ == '__main__':
    unittest.main(verbosity=2)
