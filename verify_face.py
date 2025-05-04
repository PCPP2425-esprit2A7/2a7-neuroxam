#!/usr/bin/env python
import os
import sys
import cv2
import numpy as np

def compare_faces(img1, img2):
    """Compare histograms of two images."""
    img1 = cv2.resize(img1, (200, 200))
    img2 = cv2.resize(img2, (200, 200))
    hist1 = cv2.calcHist([img1], [0], None, [256], [0, 256])
    hist2 = cv2.calcHist([img2], [0], None, [256], [0, 256])
    score = cv2.compareHist(hist1, hist2, cv2.HISTCMP_CORREL)
    return score

def load_references(folder):
    refs = {}
    for f in os.listdir(folder):
        if f.lower().endswith(('.jpg', '.png', '.jpeg')):
            path = os.path.join(folder, f)
            img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
            if img is not None:
                refs[f] = img
    return refs

def main():
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
    # cap = cv2.VideoCapture(0)
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

    if not cap.isOpened():
        print("ERROR: No camera found", file=sys.stderr)
        sys.exit(1)

    ref_dir = os.path.join(os.path.dirname(__file__), "faces")
    refs = load_references(ref_dir)
    if not refs:
        print("ERROR: No reference images", file=sys.stderr)
        sys.exit(1)

    for _ in range(60):  # Try for ~6 seconds
        ret, frame = cap.read()
        if not ret:
            continue

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)
        if len(faces) == 0:
            continue

        (x, y, w, h) = faces[0]
        face_img = gray[y:y+h, x:x+w]

        for name, ref_img in refs.items():
            similarity = compare_faces(ref_img, face_img)
            if similarity > 0.9:  # Threshold; adjust if needed
                print(f"SUCCESS:{name}")
                cap.release()
                return

    cap.release()
    print("ERROR: Face not recognized", file=sys.stderr)

if __name__ == "__main__":
    main()
