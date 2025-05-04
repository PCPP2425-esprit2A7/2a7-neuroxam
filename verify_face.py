import cv2
import numpy as np
import os

def calculate_score(ref_img, test_img):
    ref_img = cv2.resize(ref_img, (200, 200))
    test_img = cv2.resize(test_img, (200, 200))
    diff = cv2.absdiff(ref_img, test_img)
    return np.mean(diff)

print(" Verifying face...")

# Capture current face
cap = cv2.VideoCapture(0)
ret, frame = cap.read()
cap.release()
if not ret:
    print("FAIL: Could not capture webcam image")
    exit()

test_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Look through all faces in /faces/
min_score = float("inf")
matched_user = None

for file in os.listdir("faces"):
    if file.endswith(".jpg"):
        path = os.path.join("faces", file)
        ref_img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
        if ref_img is None:
            continue

        score = calculate_score(ref_img, test_gray)
        print(f" Compared to {file}: score = {score:.2f}")

        if score < min_score:
            min_score = score
            matched_user = file

# Decide if match is good enough
if min_score < 100:  # adjust as needed
    print(f"SUCCESS:{matched_user}")  # ✅ Include username
else:
    print("FAIL")
