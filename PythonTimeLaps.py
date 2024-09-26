import os
import time
from datetime import datetime
url="http://bawndotest.mattmoose.net/api/images/plantId/2"
api="http://bawndotest.mattmoose.net/api/images/plantId/2"
#files=open('test.jpg', 'rb')
#dropbox Email: Trevarian@outlook.com
#dropbox Pass: H3

FRAMES = 1
TIMEBETWEEN = 7

frameCount = 0
os.system("ls")
os.system("mkdir Timelaps")

while frameCount < FRAMES:
    imageNumber = str(frameCount).zfill(7)
    imageTime = datetime.now().strftime("%m_%d_%Y-%H_%M_%S")
    os.system("libcamera-still -o Timelaps/image%s.png --width 420 --height 380"%(imageTime))
    frameCount += 1
    file= "Timelaps/image%s.png"%(imageTime)
    os.system('curl -X POST "http://brawndotest.mattmoose.net/api/images/plantId/2" -F "image=@/home/yooz/Documents/Timelaps/image%s.png"'%(imageTime))
    time.sleep(TIMEBETWEEN - 6)
    #data = (open(file,'rb').read())
    #r = requests.post(url,data=data)
    #response = requests.post(url, files ={'media': files})
    ##if response.ok:
    ##    print(resonse.text)
    ##else:
    ##    print("Not Quite")
    #requests.post(url, files=files)
    #os.system("curl -d /home/yooz/Documents/Timelaps/image%s.png http://bawndotest.mattmoose.net/api/images/plantId/2"%(imageTime)) 
    #os.system("scp http:bawndotest.mattmoose.net/api/images/plantId/2:Timelaps/image%s.png "%(imageTime))
    #os.system('curl -X POST "http://brawndotest.mattmoose.net/api/images/plantId/2" -F "image=@/home/yooz/Documents/Timelaps/image%s.png"'%(imageTime))
    #(--header "Content-Type: file/image")
    #time.sleep(TIMEBETWEEN - 6)
    
    ###with open("Timelaps/image%s.png"%(imageTime), "rb") as f:
        ###im_bytes = f.read()
    ###im_b64= base64.b64encode(im_bytes).decode("utf8")
    ###headers={'Content-type': 'application/json', 'Accept': 'text/plain', 'transfer-encoding': 'chunked'}
    ###payload= json.dumps({"image": im_b64, "other_key": "value"})
    ###response = requests.post(api, data=payload, headers=headers)
    
    #try:
    #   data.response.joson()
    #  print(data)
    #except requests.exceptions.RequestException:
    #   print(response.text)