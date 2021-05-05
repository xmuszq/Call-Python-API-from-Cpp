import cv2
import mediapipe as mp

def face_detect(img):
    ans =[0]
	## the input image is a format with cv2 read
    mp_face_detection = mp.solutions.face_detection
    mp_drawing = mp.solutions.drawing_utils	
    with mp_face_detection.FaceDetection(
        min_detection_confidence=0.5) as face_detection:
		# Convert the BGR image to RGB and process it with MediaPipe Face Detection.
        results = face_detection.process(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))

    if not results.detections:
      return ans
    detection = results.detections[0]
    nose_tip = mp_face_detection.get_key_point(
          detection, mp_face_detection.FaceKeyPoint.NOSE_TIP)
    print('nose tip ', nose_tip)
    ans.append(0.5);ans.append(0.5)
    return ans


"""

file_list=['/home/zhen/Projects/img_samples/2.jpg']
image = cv2.imread(file_list[0]);print('img shape in py ', image.shape)
ans = face_detect(image)


mp_face_detection = mp.solutions.face_detection
mp_drawing = mp.solutions.drawing_utils
file_list=['/home/zhen/Projects/img_samples/2.jpg']
# For static images:
with mp_face_detection.FaceDetection(
    min_detection_confidence=0.5) as face_detection:
  for idx, file in enumerate(file_list):
    image = cv2.imread(file)
    # Convert the BGR image to RGB and process it with MediaPipe Face Detection.
    results = face_detection.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

    # Draw face detections of each face.
    if not results.detections:
      continue
    annotated_image = image.copy()
 
    for detection in results.detections:
      print('Nose tip:')
      nt = mp_face_detection.get_key_point(
          detection, mp_face_detection.FaceKeyPoint.NOSE_TIP)
      print(nt)
      mp_drawing.draw_detection(annotated_image, detection)
    cv2.imwrite('/home/zhen/Projects/img_samples/out/annotated_image' + str(idx) + '.png', annotated_image)
"""
