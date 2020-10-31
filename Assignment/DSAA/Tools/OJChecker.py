import requests
import time
url="https://acm.sustech.edu.cn/onlinejudge/"
while 1:
    try:
        r = requests.get(url,timeout=1)
        print(r.status_code)
        break
    except Exception as e:
        print(str(time.strftime("%H:%M:%S", time.localtime()))+" OJ还未修复...")
        continue
print('提示','OJ修复了，快参与内卷！')