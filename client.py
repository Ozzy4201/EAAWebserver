import json, requests, time
url = "http://localhost:5000/datapost"

with open ("data.json", "r") as f:
    SData = json.load(f)
print(SData)

try: x = requests.post(url, json=SData)

except Exception as e: print(e)

else: print(x.text)

finally: pass
