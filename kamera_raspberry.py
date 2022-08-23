import cv2

kamera = cv2.VideoCapture(0)

while True:
		ret, image = kamera.read()
		cv2.imshow('OUTPUT', image)
	

kamera.release()
cv2.destroyAllWindows()