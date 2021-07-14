## ----- Conversion Functions ----- ##

#Helper function:
def bitFlip(unsigned):
    index = len(unsigned)-1
    flipped = ""
    while index >= 0:
        if unsigned[index] == "0":
            flipped = "1" + flipped
        else:
            flipped = "0" + flipped
        index = index - 1
    return flipped

#Convert base-2 to base-10
def b2b10(num):
    mag = num
    index = 0
    significand = len(mag)-1
    new = 0
    while index <= len(mag)-1:
        if mag[index] == '1':
            new = new + 2**significand
        significand = significand - 1
        index = index + 1
    return new


#Convert base-10 to base-2
def b10b2(num,bitlen):
    mag = abs(num)
    binary = ""
    count = bitlen
    while mag > 0:
        r = mag % 2
        mag = mag // 2
        binary = str(r) + binary
        count = count - 1
    if count < 0:
        return "overflow error"
    while count > 0:
        binary = "0" + binary
        count = count - 1
    if num < 0:
        return "-"+binary
    else:
        return "+"+binary


#Convert base-2 to Ones-Complement
def b21c(binary):
    mag = binary[1:]
    if binary[0] == '+':
        flipped = mag
        if flipped[0] != "0":
            return "overflow error"
    else:
        flipped = bitFlip(mag)
        if flipped[0] != "1":
            return "overflow error"
    return flipped


#Convert base-2 to Twos-Complement
# !!! This function does not validate when
#   -0...0 is given as an argument.
def b22c(binary):
    mag = binary[1:]
    significand = len(mag) - 1
    carry = 0
    twos = ""
    if binary[0] == "-":
        mag = bitFlip(mag)
        carry = 1
    # --- "Add1" subroutine:
    while significand >= 0:
        if carry == 1:
            if mag[significand] == "0":
                twos = "1" + twos
                carry = 0
            if mag[significand] == "1":
                twos = "0" + twos
                carry = 1
        else:
            twos = mag[significand] + twos
        significand = significand - 1
    # --- end subroutine
    if carry > 0:
        return "overflow error"
    #not sure these are necessary:
    if binary[0] == "+":
        if twos[0] != "0":
            return "overflow error"
    elif binary[0] == "-":
        if twos[0] != "1":
            return "overflow error"
    return twos


## ----- Extranious functions ----- ##
# --- No usage of inequality besides <= 0

#Round to ceiling:
def nround(num):
    count = 0
    while not num <= 0:
        num = num - 1
        count = count + 1
    return count


#Find the minimum
def nmin(num1, num2):
    a = 0
    n1 = num1
    n2 = num2
    while a <= 0:
        n1 = n1 - 1
        n2 = n2 - 1
        if n1 <= 0:
            return num1
        if n2 <= 0:
            return num2

#Find the maximum
def nmax(num1, num2):
    a = 0
    n1 = num1
    n2 = num2
    while a <= 0:
        n1 = n1 - 1
        n2 = n2 - 1
        if n1 <= 0:
            return num2
        if n2 <= 0:
            return num1

#Find the range of three
def nrange(num1,num2,num3):
    maxx = nmax(num1, num2)
    maxx = nmax(maxx, num3)
    minn = nmin(num1, num2)
    minn = nmin(minn, num3)
    return maxx - minn

# --- TESTS --- #
print("b2b10:")
print(b2b10("00011001"))
print(b2b10("010011001"))
#25
#153

print("b10b2:")
print(b10b2(32,8))
print(b10b2(-32,8))
print(b10b2(-32,4))
print(b10b2(7,6))
'''
+00100000
-00100000
overflow error
+000111
'''

print("b21c:")
print(b21c("+00011100"))
print(b21c("-00011100"))
print(b21c("-11101010"))
print(b21c("+111"))
print(b21c("-111"))
'''
00011100
11100011
overflow error
overflow error
overflow error
'''

print("b22c:")
print(b22c("+00011100"))
print(b22c("-00011100"))
print(b22c("-11101010"))
print(b22c("+0000"))
print(b22c("+0001"))
print(b22c("-0111"))
print(b22c("-1000"))
print(b22c("-1001"))
'''
00011100
11100100
overflow error
0000
0001
1001
1000
overflow error
'''

print(nround(32.5))
print(nround(.000001))
print(nround(500))

#print(nrange(2,0,55))
nums = [100,30,8]
for i in range(0,3):
    for j in range(0,3):
        if j != i:
            for k in range(0,3):
                if k != j and k!= i:
                    print(nums[i],nums[j],nums[k])
                    print(nrange(nums[i],nums[j],nums[k]))
                    print()
