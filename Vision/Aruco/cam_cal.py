import numpy as np
import cv2, time

cv2.namedWindow("Image Feed")
cv2.moveWindow("Image Feed", 159, -25)

cap = cv2.VideoCapture(0)

# setup camera
cap.set(CV.CAP_PROP_FRAME_WIDTH, 640)
cap.set(CV.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(CV.CAP_PROP_FPS, 30)    # look up frame rate for full FOV for specific camera

prep_frame_time = time.time();

while True:
    ret, frame = cap.read()   # Read the camera frame                                        
