import re

m1 = open('密文.txt', 'rb').read()
s = m1.split()
flag = ""
for j in range(256):
    flag = ""
    for i in s:
        flag += chr(int(i, 16) ^ j)
    if "flag" in flag:
        print(flag)
