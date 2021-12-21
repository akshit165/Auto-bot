from __future__ import print_function
import serial
import time
import pyzbar.pyzbar as pyzbar
import numpy as np
import cv2

# get the webcam:
cap = cv2.VideoCapture(cv2.CAP_V4L2)
#cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)
# 160.0 x 120.0
# 176.0 x 144.0
# 320.0 x 240.0
# 352.0 x 288.0
# 640.0 x 480.0
# 1024.0 x 768.0
# 1280.0 x 1024.0
time.sleep(2)

serialcomm = serial.Serial('/dev/ttyACM0', 9600)
serialcomm.timeout = 1


def decode(im):
    # Find barcodes and QR codes
    decodedObjects = pyzbar.decode(im)
    # Print results
    # for obj in decodedObjects:
    #     print('Type : ', obj.type)
    #     print('Data : ', obj.data.decode('utf-8'),'\n')
    return decodedObjects


font = cv2.FONT_HERSHEY_SIMPLEX

while (cap.isOpened()):
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Our operations on the frame come here
    im = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    decodedObjects = decode(im)

    for decodedObject in decodedObjects:
        points = decodedObject.polygon

        # If the points do not form a quad, find convex hull
        if len(points) > 4:
            hull = cv2.convexHull(np.array([point for point in points], dtype=np.float32))
            hull = list(map(tuple, np.squeeze(hull)))
        else:
            hull = points;

        # Number of points in the convex hull
        n = len(hull)
        # Draw the convext hull
        for j in range(0, n):
            cv2.line(frame, hull[j], hull[(j + 1) % n], (255, 0, 0), 3)

        x = decodedObject.rect.width
        y = decodedObject.rect.height
        #print(x, y)

        #print('Type : ', decodedObject.type)
        # print('Data : ', decodedObject.data.decode('utf-8'), '\n')
        # barCode = str(decodedObject.data.decode('utf-8'))
        # cv2.putText(frame, barCode, (x, y), font, 1, (0, 255, 255), 2, cv2.LINE_AA)


        if x & y > 100:
            #print('Type : ', decodedObject.type)
            print('Data : ', decodedObject.data.decode('utf-8'), '\n')

            barCode = str(decodedObject.data.decode('utf-8'))
            cv2.putText(frame, barCode, (x, y), font, 1, (0, 255, 255), 2, cv2.LINE_AA)
            i = barCode
            serialcomm.write(i.encode())
            time.sleep(1.5)
            print(serialcomm.readline().decode('ascii'))   
            
    # Display the resulting frame
    cv2.imshow('frame', frame)
    key = cv2.waitKey(1)
    if key & 0xFF == ord('q'):
        break
    # elif key & 0xFF == ord('s'): # wait for 's' key to save
    #     cv2.imwrite('Capture.png', frame)

# When everything done, release the capture
cap.release()
serialcomm.close()
cv2.destroyAllWindows()