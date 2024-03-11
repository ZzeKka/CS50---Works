import math

credit_number = int(input("Number: "))
number = credit_number
count, double_sum, single_sum = 0, 0, 0

while number != 0:
    if (count % 2 == 0):
        single_sum += (number % 10)
    else:
        digit_sum_number = (2 * (number % 10))
        while digit_sum_number != 0:
            double_sum = double_sum + (digit_sum_number % 10)
            digit_sum_number = math.floor(digit_sum_number/10)
    number = math.floor(number/10)
    count += 1

# Check card type
final_sum = double_sum + single_sum
if final_sum % 10 == 0:
    if (count == 13 or count == 16) and (math.floor(credit_number / 10**(count-1)) == 4):
        print("VISA")
    elif (count == 16 and (math.floor(credit_number / 10**(count-2))) >= 51) and (math.floor(credit_number / 10**(count-2)) <= 55):
        print("MASTERCARD")
    elif ((count == 15 and ((math.floor(credit_number / 10**(count-2)) == 34)) or (math.floor(credit_number / 10**(count-2)) == 37))):
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")
