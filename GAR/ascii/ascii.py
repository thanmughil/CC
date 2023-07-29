import cv2
import os

# ASCII characters to represent different brightness levels
ASCII_CHARS = ' .:-=+*%#@'

def resize_image(image, new_width=450):
    height, width = image.shape
    aspect_ratio = height / float(width)
    new_height = int(new_width * aspect_ratio)
    resized_image = cv2.resize(image, (new_width, new_height))
    return resized_image

def pixel_to_ascii(image):
    ascii_str = ''
    for i in range(0,len(image),2):
        for pixel in image[i]:
            ascii_str += ASCII_CHARS[int((pixel*9)/255)]
        ascii_str += '\n'
    return ascii_str

def main():
    #video_path = 'bad-apple.mp4'
    cap = cv2.VideoCapture(0)

    while True:
        ret, frame = cap.read()

        if not ret:
            break

        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        resized_frame = resize_image(gray_frame)
        
        ascii_str = pixel_to_ascii(resized_frame)

        # Display the ASCII frame in the console
        print(ascii_str)

        # To display in a GUI window
        # cv2.imshow('ASCII Video', resized_frame)#cv2.putText(gray_frame, ascii_str, (10, 30), cv2.FONT_HERSHEY_PLAIN, 1, (255, 255, 255), 2))

        # Press 'q' to exit
        #if cv2.waitKey(1) & 0xFF == ord('q'):
            #break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
