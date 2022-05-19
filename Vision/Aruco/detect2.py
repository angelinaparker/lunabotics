import numpy as np
import cv2
import cv2.aruco as aruco

marker_size = 100

with open('camera_cal.npy', 'rb') as f:
  camera_matrix = np.load(f)
  camera_distortion = np.load(f)
 
aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4x4_250)

cap = cv2.VideoCapture(0)

cap.set(2, camera_width)
cap.set(4, camera_height)
cap.set(5, camera_frame_rate)

ret, frame = cap.read()     # grab frame

gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Find aruco marker in the image
corners, ids, rejected = aruco.detectMarkers(gray_frame, aruco_dict, camera_matrix, camera_distortion)

if ids is not None:
  aruco.drawDetectedMarkers(frame, corners)
  
  # get pose of marker, rotation and translation vectors
  rvec_list_all, tvec_list_all, _objPoints = aruco.estimatePoseSingleMarkers(corners, marker_size, camera_matrix, camera_distortion)
  
  print(tvec_list_all)
  
cv2.imshow('frame', frame)

cv2.waitKey(0)

cap.release()
cv2.destroyAllWindows()
