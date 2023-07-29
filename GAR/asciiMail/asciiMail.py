import cv2
import numpy as np
import msvcrt
import tkinter as tk
from tkinter import simpledialog
import datetime

def get_current_time_string():
    current_time = datetime.datetime.now()
    time_string = current_time.strftime("%Y-%m-%d %H:%M:%S")
    time_string = time_string.replace(':','-')
    return time_string

def get_user_input():
    root = tk.Tk()
    root.withdraw()  # Hide the main window

    root.option_add("*Dialog.msg.font", "Helvetica 32")  # Set the font size
    root.option_add("*Dialog.msg.width", 1600)

    name = simpledialog.askstring("Input", "Enter your name:", parent=root)
    email = simpledialog.askstring("Input", "Enter your email:", parent=root)
    time_string = get_current_time_string()
    name += f" {time_string}"

    return name, email

# ASCII characters to represent different brightness levels
ASCII_CHARS = ' .:-=+*%#@'

def resize_image(image, new_width=480):
    height, width = image.shape
    aspect_ratio = height / float(width)
    new_height = int(new_width * aspect_ratio)
    resized_image = cv2.resize(image, (new_width, new_height))
    return resized_image

def pixel_to_ascii(image,step=2):
    # if step == 1:
    #     image = resize_image(image, 960)
    ascii_str = ''
    for i in range(0,len(image),step):
        for pixel in image[i]:
            ascii_str += ASCII_CHARS[int((pixel*9)/255)]
        ascii_str += '\n'
    return ascii_str

def main():
    #black_img = cv2.imread("bg.jpg")
    #video_path = 'bad-apple.mp4'
    cap = cv2.VideoCapture(0)

    while True:
        ret, frame = cap.read()

        if not ret:
            break

        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray_frame = cv2.flip(gray_frame,1)
        resized_frame = resize_image(gray_frame)
        
        ascii_str = pixel_to_ascii(resized_frame)

        # Display the ASCII frame in the console
        print(ascii_str)

        #cv2.imshow('ASCII Video', resized_frame)#cv2.putText(gray_frame, ascii_str, (10, 30), cv2.FONT_HERSHEY_PLAIN, 1, (255, 255, 255), 2))

        # Press 'q' to exit
        if msvcrt.kbhit():
            try:
                char = msvcrt.getch().decode('utf-8')
            except:
                continue

            if char.lower() == 's':
                ascii_str = pixel_to_ascii(gray_frame,1)
                asciiList = list(ascii_str.splitlines())

                # Define the font and font scale
                font = cv2.FONT_HERSHEY_SIMPLEX
                font_scale = 0.5

                # Calculate the size of a character to fit within the image
                char_size = cv2.getTextSize("A", font, font_scale, 1)[0]
                char_width, char_height = char_size

                height, width = len(asciiList)*char_size[1],len(asciiList[0])*char_size[0]
                plain_image = np.zeros((height, width, 3), dtype=np.uint8)

                # Write each character onto the plain image
                y = char_height
                for row in ascii_str.splitlines():
                    x = char_width
                    for char in row:
                        plain_image = cv2.putText(plain_image, char, (x, y), font, font_scale, (255, 255, 255), 1, cv2.LINE_AA)
                        x += char_width
                    y += char_height

                output, mail = get_user_input()
                print(output)
                with open('mailList.txt','a') as file:
                    file.write(f"{output}\t{mail}\n")


                cv2.imwrite(f"{output}.jpg",plain_image)
                # cv2.imwrite("orgimg.jpg",frame)
                # cv2.imwrite("bwimg.jpg",gray_frame)

                flag = input("Continue (Y/N)? : ").upper()
                if flag == 'N':
                    cap.release()
                    cv2.destroyAllWindows()
                    break

if __name__ == "__main__":
    main()
