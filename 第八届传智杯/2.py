import sys

s = input().strip()

result = []
pos = 0
length = 1

while pos + length <= len(s):
    substring = s[pos:pos+length]
    decimal = int(substring, 2)
    result.append(decimal)

    pos += length

    length = (length % 10) + 1

print(len(result))
if result:
    print(' '.join(map(str, result)))
else:
    print('')

