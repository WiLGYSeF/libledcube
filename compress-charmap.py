import math
import re
import sys

def getbytearrsize(size):
	return (size >> 3) + (not not (size & 7))

def compress(data, led_on="#", led_off="."):
	width = math.sqrt(len(data))
	if width != int(width):
		raise ValueError("data is not square")

	width = int(width)
	area = width * width
	bytearr = [0] * getbytearrsize(area)

	b = 0
	for d in range(area):
		if data[d] == led_on:
			val = 1
		elif data[d] == led_off:
			val = 0
		else:
			raise ValueError("unknown symbol: " + data[d])

		bytearr[b] |= (val << (7 - (d & 7)))
		if (d & 7) == 7:
			b += 1

	return bytearr

def decompress(data, width, led_on="#", led_off="."):
	area = width * width

	if len(data) != getbytearrsize(area):
		raise ValueError("data length does not match")

	r = ""
	c = 0

	for d in data:
		for i in range(7, -1, -1):
			r += led_on if d & (1 << i) else led_off

			c += 1
			if c == area:
				break

	return r

def compress_str(data, led_on="#", led_off="."):
	regex = re.compile(r'\s*"([' + led_on + led_off + ']+)"\s*')

	d = ""
	pos = 0

	while True:
		match = regex.match(data, pos)
		if match is None:
			break

		d += match.group(1)
		pos = match.end()

	if d != "":
		return compress(d, led_on, led_off)
	return compress(data, led_on, led_off)

def decompress_str(data, width, led_on="#", led_off="."):
	regex = re.compile(r'\s*{?(\s*(?:0x[0-9a-f]+,\s*)+(?:0x[0-9a-f]+)\s*)}?\s*')

	match = regex.fullmatch(data)
	if match is not None:
		numbers = map(lambda x: x.strip(), match.group(1).split(","))
		num = []

		for n in numbers:
			num.append(int(n, 16))

		return decompress(num, width, led_on, led_off)

	return decompress(data, width, led_on, led_off)

def compress_tostr(data):
	r = "{"
	for e in data:
		h = hex(e)
		if len(h) == 3:
			h = "0x0" + h[-1]

		r += h + ", "

	r = r[:-2] + "}"
	return r

def decompress_tostr(data, newline=False):
	r = ""
	if newline:
		for i in range(width):
			r += "\"" + data[i * width : (i + 1) * width] + "\"\n"
	else:
		r = "\"" + data + "\""

	return r

if __name__ == "__main__":
	compressmode = True
	width = -1
	led_on = "#"
	led_off = "."
	newline = False
	data = None
	i = 1

	while i < len(sys.argv):
		arg = sys.argv[i]
		if arg == "--compress" or arg == "-c":
			compressmode = True
		elif arg == "--decompress" or arg == "-d":
			if i == len(sys.argv) - 1:
				raise ValueError("missing argument for --decompress")

			compressmode = False
			width = int(sys.argv[i + 1])
			i += 1
		elif arg == "--led-on" or arg == "-o":
			if i == len(sys.argv) - 1:
				raise ValueError("missing argument for --led-on")

			led_on = sys.argv[i + 1][0]
			i += 1
		elif arg == "--led-off" or arg == "-f":
			if i == len(sys.argv) - 1:
				raise ValueError("missing argument for --led-off")

			led_off = sys.argv[i + 1][0]
			i += 1
		elif arg == "--newline" or arg == "-n":
			newline = True
		else:
			if data is not None:
				raise ValueError("too many arguments")

			data = arg

		i += 1

	if data is None:
		raise ValueError("no data passed")

	if compressmode:
		ret = compress_str(data, led_on, led_off)
		print(compress_tostr(ret))
	else:
		ret = decompress_str(data, width, led_on, led_off)
		print(decompress_tostr(ret, newline))
