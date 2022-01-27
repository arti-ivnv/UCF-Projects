# First Assignment (Python)
# Artem Ivanov
# ar286080

def problem1(x, y):
    return x * y

def problem2(a, b, c):
    return a * b * c

def first_a(n):
    return [x for x in range(1, n + 1) if x % 6 == 0 or x % 11 == 0]

def isMult6Or11(num):
    return ((num % 6 == 0) or (num % 11 == 0))

def first_b(n):
    return [x for x in range(1, n + 1) if (isMult6Or11(x))]

def second_a(n):
    return [x for x in range(1, n + 1) if (str(x) == str(x)[::-1]) and (str(x)[0] == "3")]

def isPalindromeThatStartsWithDigit3(x):
    return (str(x) == str(x)[::-1]) and (str(x)[0] == "3")

def second_b(n):
    return [x for x in range(1, n + 1) if isPalindromeThatStartsWithDigit3(x)]
