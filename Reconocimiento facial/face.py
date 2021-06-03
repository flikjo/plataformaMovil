
import cv2
import mediapipe as mp 
from envioCmmd import enviar
mp_drawing = mp.solutions.drawing_utils
mp_face_mesh = mp.solutions.face_mesh

# For webcam input:
drawing_spec = mp_drawing.DrawingSpec(thickness=1, circle_radius=1)
cap = cv2.VideoCapture(0)
contUp=0
contLeft=0
contRight=0
contUnder=0
with mp_face_mesh.FaceMesh(
    max_num_faces=1,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5) as face_mesh:
  while cap.isOpened():
    success, image = cap.read()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      continue

    # Flip the image horizontally for a later selfie-view display, and convert
    # the BGR image to RGB.
    image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
    # To improve performance, optionally mark the image as not writeable to
    # pass by reference.
    image.flags.writeable = False
    results = face_mesh.process(image)

    # Draw the face mesh annotations on the image.
    image.flags.writeable = True
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

    heinght, width, _ =image.shape
    
    if results.multi_face_landmarks:
      index=[1]
      for face_landmarks in results.multi_face_landmarks:
        a=int(width/2)
        b=int(heinght/2)
        
        cv2.circle(image,(a,b),60,(255,0,0),1)
        for (i, points) in enumerate(face_landmarks.landmark):
          if i in index:
            #x=points.x
            #y=points.y
            
            x=int(points.x*width)
            y=int(points.y*heinght)
            cv2.circle(image,(x,y),1,(255,0,0),2)
            #print(x , y)

            if(y<182):
              if(contUp==0):
                print("Arriba")
                #enviar(1)
                contUp=10
            elif(y>182):
              contUp=0
             # print(x , y)
            if(y>297):
              if(contUnder==0):
                print("Abajo")
                #enviar(0)
                contUnder=1
            elif(y<297):
              contUnder=0
            if(x<255):
              if(contLeft==0):
                print("Izquierda")
                #enviar(2)
                contLeft=1
            elif(x>255):
                contLeft=0
            if(x>385):
              if(contRight==0):
                print("Derecha")
                #enviar(3)
                contRight=1
            elif(x<385):
                contRight=0
                
       # mp_drawing.draw_landmarks(
       #     image=image,
       #     landmark_list=face_landmarks,
       #     connections=mp_face_mesh.FACE_CONNECTIONS,
       #     landmark_drawing_spec=drawing_spec,
       #     connection_drawing_spec=drawing_spec)

    cv2.imshow('MediaPipe FaceMesh', image)
    if cv2.waitKey(5) & 0xFF == 27:
      break
cap.release()
#cv2.destroyAllWindows()