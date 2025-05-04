import cv2
import os

name = input("Enter user name (e.g., khaled): ")
path = f"faces/{name}.jpg"

if not os.path.exists("faces"):
    os.makedirs("faces")

cap = cv2.VideoCapture(0)
while True:
    ret, frame = cap.read()
    cv2.imshow("Capture - Press Space", frame)
    key = cv2.waitKey(1)
    if key == 32:  # spacebar
        cv2.imwrite(path, frame)
        print(f"✅ Face saved to {path}")
        break

cap.release()
cv2.destroyAllWindows()
