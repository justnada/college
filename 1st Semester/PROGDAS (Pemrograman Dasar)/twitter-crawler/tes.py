from datetime import datetime

s = 'Sat Oct 29 13:32:16 +0000 2022'
print(datetime.strptime(s, '%a %b %d %H:%M:%S %z %Y').strftime('%Y-%m-%d %H:%M:%S'))