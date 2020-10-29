

def sumStrings(x,y):
	# Padding to the same length
	lenx = len(x)
	leny = len(y)

	if (lenx < leny):
		lens = leny
		x = '0'*(lens-lenx)+x
	elif (leny < lenx):
		lens = lenx
		y = '0'*(lens-leny)+y
	else:
		lens = lenx

	result = ''
	carry = 0
	for i in range(lens):
		partialsum = int(x[lens-1-i]) + int(y[lens-1-i]) + carry
		carry = partialsum//10
		digit = partialsum - carry*10
		result = str(digit) + result

	if carry > 0:
		result = str(carry) + result

	return result

def subStrings(x,y):
	# Padding to the same length
	lenx = len(x)
	leny = len(y)

	if (lenx < leny):
		lens = leny
		x = '0'*(lens-lenx)+x
	elif (leny < lenx):
		lens = lenx
		y = '0'*(lens-leny)+y
	else:
		lens = lenx

	result = ''
	carry = 0
	for i in range(lens):
		xdigit = int(x[lens-1-i]) - carry
		ydigit = int(y[lens-1-i])
		if xdigit >= ydigit:
			digit = xdigit - ydigit
			carry = 0
		else:
			digit = 10 + xdigit - ydigit
			carry = 1

		result = str(digit) + result

	return result

def addZeros(x, n):
	return x + '0'*n

def multStrings(x,y):
	lenx = len(x)
	leny = len(y)
	# print(lenx,leny)
	if (lenx == 1):
		return str(int(x)*int(y))
	else:
		# If string of different length pad the
		# shorter one with zeros
		if (lenx < leny):
			x = '0'*(leny - lenx) + x
			lens = leny
		elif (lenx > leny):
			y = '0'*(lenx - leny) + y
			lens = lenx
		else:
			lens = lenx

		# Splitting a string in two
		a = x[0:lens//2]
		b = x[lens//2:lens]

		c = y[0:lens//2]
		d = y[lens//2:lens]

		ac = multStrings(a,c)
		bd = multStrings(b,d)

		# Doing the Gauss trick
		abcd = multStrings(sumStrings(a,b),sumStrings(c,d))
		ad_plus_bc = subStrings(subStrings(abcd,ac),bd)

		result = sumStrings(addZeros(ac,2*(lens - lens//2)), addZeros(ad_plus_bc, lens - lens//2))
		result = sumStrings(result, bd)

		return result

def main():
	x = '3141592653589793238462643383279502884197169399375105820974944592'
	y = '2718281828459045235360287471352662497757247093699959574966967627'
	result = multStrings(x,y)
	print(result)
	# Checking if the result is correct
	print(result == '8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184')


if __name__ == '__main__':
	main()




