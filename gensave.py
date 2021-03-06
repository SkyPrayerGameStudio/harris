#!/usr/bin/python2

import sys, zlib, struct, random, math

def multiply(line):
	if len(line) > 1:
		if line[0] == '*' and line[1].isdigit():
			l = line.find('*', 2)
			if l > 1:
				n = int(line[1:l])
				return n*[line[l+1:]]
	return [line]

def genids(line, i):
	if ',NOID' in line:
		z = '_'.join((salt, str(i), line))
		ha = zlib.crc32(z) & 0xffffffff
		h = hex(ha)[2:].rstrip('L')
		return line.replace('NOID', h.zfill(8))
	else:
		return line

def poisson(lamb):
	if lamb <= 0:
		return 0
	l = math.exp(-lamb)
	k = 0
	p = 1
	while p > l:
		k += 1
		p *= random.random()
	return k - 1

def gencrews(line, i, cgv=1):
	words = line.split(':')
	_, stat, cls = words[0].split()
	words = words[1].split(',')
	ms = int(words[0])
	if cgv > 1:
	    mheavy = int(words[1])
	    mlanc = int(words[2])
	    words = words[2:]
	else:
	    mheavy = 0
	    mlanc = 0
	ml = int(words[1])
	tops = int(words[2])
	ft = int(words[3])
	assi = int(words[4])
	acid = words[5]
	z = '_'.join((salt, str(i), line))
	ha = zlib.crc32(z) & 0xffffffff
	random.seed(ha)
	skill = poisson(ms)
	heavy = poisson(mheavy)
	lanc = poisson(mlanc)
	lrate = poisson(ml)
	tops = random.randint(0, tops)
	if cgv <= 1 and stat == 'Student':
	    # Account for students' HCU/LFS training
	    if ft==1:
	        heavy = tops * 3
	    elif ft==2:
	        lanc = tops * 9
	        heavy = 100
	if windows:
		return "%s %c:%s,%s,%s,%u,%u,%u,%d,00000000%s"%(stat, cls, float_to_hex(skill), float_to_hex(heavy), float_to_hex(lanc), lrate, tops, ft, assi, acid)
	else:
		return "%s %c:%u,%u,%u,%u,%u,%u,%d,00000000%s"%(stat, cls, skill, heavy, lanc, lrate, tops, ft, assi, acid)

windows = '--windows' in sys.argv

salt = ''
if '--salt' in sys.argv:
	sarg = sys.argv.index('--salt')
	try:
		salt = sys.argv[sarg+1]
	except IndexError:
		sys.stderr.write('--salt requires argument!\n')
		sys.exit(1)

def float_to_hex(value):
	f = float(value)
	bytes = struct.pack('>d', f)
	i, = struct.unpack('>q', bytes)
	return '%016x'%i

for line in sys.stdin.readlines():
	lines = multiply(line)
	for i,line in enumerate(lines):
		line = genids(line, i)
		if line.startswith("CG "):
			line = gencrews(line, i, 1)
		elif line.startswith("CG2 "):
			line = gencrews(line, i, 2)
		if windows and ':' in line:
			to_conv = {'Confid':(0,),
				       'Morale':(0,),
				       'IClass':(0,),
				       'Targ':(0,1,2,3)}
			tag, values = line.rstrip('\n').split(':', 1)
			starttag, _, resttag = tag.partition(' ')
			values = values.split(',')
			if starttag in to_conv:
				for pos in to_conv[starttag]:
					values[pos] = float_to_hex(values[pos])
				line = ':'.join((tag, ','.join(values))) + '\n'
		sys.stdout.write(line)
