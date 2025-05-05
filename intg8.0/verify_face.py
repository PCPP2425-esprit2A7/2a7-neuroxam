print(" Script started")
import cv2
import numpy as np
import os
import sys
sys.stdout.reconfigure(encoding='utf-8')

print(" Running verify_face.py...")

# Define absolute path for face_reference.jpg
script_dir = os.path.dirname(os.path.abspath(__file__))
ref_path = os.path.join(script_dir, "face_reference.jpg")

# Load reference image
ref_img = cv2.imread(ref_path, cv2.IMREAD_GRAYSCALE)
if ref_img is None:
    print("FAIL: Reference image not found")
    exit()

# Open webcam and capture new image
cap = cv2.VideoCapture(0)
ret, frame = cap.read()
cap.release()

if not ret:
    print("FAIL: Could not capture image from webcam")
    exit()

# Convert to grayscale and resize to 200x200
ref_img = cv2.resize(ref_img, (200, 200))
current_img = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
current_img = cv2.resize(current_img, (200, 200))

# Calculate difference score
diff = cv2.absdiff(ref_img, current_img)
score = np.mean(diff)
print(f" Difference score: {score}")

# Decision
if score < 70:
    print("SUCCESS")
else:
    print("FAIL")
