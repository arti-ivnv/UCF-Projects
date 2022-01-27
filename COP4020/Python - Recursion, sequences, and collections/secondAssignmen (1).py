
def isVowel(char):
    if char.lower() in 'aeiouy':
        return True
    else:
        return False

def isThreeLetters(str):
    if len(str) > 3:
        return True
    else:
        return False

def containsLetters(str, len, str2):
    if len == 0:
        return False

    if (str[len-1] in str2) and (str[len-1].isalnum()):
        return True
    else:
        return containsLetters(str, len - 1, str2)

def word_smith(str1, str2):
    lengthy = len(str1)

    myList = str1.split()

    myList2 = [word for word in myList if ((isVowel(word[0]) or containsLetters(word, len(word), str2)) and isThreeLetters(word))]

    return len(myList2)

def base_builder(num):

    def rec_convertor(num):
        if num == 0:
            return 0
        else:
            return (num % 4) + 10 * int(rec_convertor(num/4))

    def sum(stri,n):
        if n == 0:
            return int(stri[0])
        else:
            return int(stri[n]) + sum(stri,n - 1)


    baseFour = rec_convertor(num)

    n = len(str(baseFour)) - 1
    stri = str(baseFour)

    sumOfNums = sum(stri,n)

    return (sumOfNums, baseFour)
