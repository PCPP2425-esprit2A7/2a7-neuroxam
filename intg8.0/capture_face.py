import cv2

cap = cv2.VideoCapture(0)
while True:
    ret, frame = cap.read()
    cv2.imshow("Capture - Press Space", frame)
    key = cv2.waitKey(1)
    if key == 32:  # Space key
        cv2.imwrite("face_reference.jpg", frame)
        print("✅ Face saved.")
        break
cap.release()
cv2.destroyAllWindows()
