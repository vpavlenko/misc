#!/usr/bin/python3

# Howto:
# $ sudo apt-get install graphviz
# $ sudo apt-get install python3
# $ cat > mygraph
# 3 4
# 1 2
# 1 3
# 1 4
# 2 4
# $ gd mygraph

from sys import argv, exit
from os import execv

if len(argv) < 2:
    print('Usage: gd FILENAME')
    exit(1)

fin = open(argv[1], 'r').readlines()
fout = open('/tmp/gd', 'w')

if len(argv) > 2:
    decrease = 0
else:
    decrease = 0

print('digraph G {', file=fout)
print('''fontsize = 4.0;
ratio = auto;''', file=fout)

S = set(range(decrease + 1, decrease + 1 + int(fin[0].split()[0])))
for i in S:
    print(i + decrease, '[shape = circle, height=.1, width=.1];', file=fout)
for j, i in enumerate(fin[1:]):
    v, w = map(int, i.split())
    v += decrease
    w += decrease
    print('%d -> %d' % (w, v) + ' [ label = "' +
          '" ];', file=fout, sep='')
print('}', file=fout)

fout.close()

execv('/bin/bash', ['-v', '-c', 'dot -Tps /tmp/gd > /tmp/gd.ps && cp /tmp/gd.ps . && convert gd.ps gd.png && google-chrome gd.png &', ''])
