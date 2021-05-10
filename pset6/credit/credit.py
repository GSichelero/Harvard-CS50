def get_credit_number():
    try:
        credit_number = int(input("What is your credit card's number?\n"))
    except:
        get_credit_number()
    return credit_number

def main():
    card = get_credit_number()
    str_card = str(card)
    digits_count = len(str_card)
    total_sum = 0

    if digits_count in {13, 15, 16} and digits_count >= 0:
        i = digits_count - 2
        while i >= 0:
            digit_to_multiply = int(str_card[i]) * 2
            if digit_to_multiply > 9:
                digit_to_multiply = int(str(digit_to_multiply)[0]) + int(str(digit_to_multiply)[1])
            total_sum = total_sum + digit_to_multiply
            i = i - 2

        j = digits_count - 1
        while j >= 0:
            digit_not_to_multiply = int(str_card[j])
            total_sum = total_sum + digit_not_to_multiply
            j = j - 2

        if int(str(total_sum)[-1]) == 0:
            if str_card[0] == "4":
                print("VISA")
                return 0
            elif str_card[0:2] == "34" or str_card[0:2] == "37":
                print("AMEX")
                return 0
            elif str_card[0:2] == "51" or str_card[0:2] == "52" or str_card[0:2] == "53" or str_card[0:2] == "54" or str_card[0:2] == "55":
                print("MASTERCARD")
                return 0
            else:
                print("INVALID")
                return 1
        else:
            print("INVALID")
            return 1
    else:
        print("INVALID")
        return 1

if __name__ == "__main__":
    main()