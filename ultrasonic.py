import serial
import pygame

pygame.mixer.init()
pygame.mixer.music.load("aler1.mp3")

arduino = serial.Serial("COM7", 9600)  # Change COM port

is_playing = False

while True:
    data = arduino.readline().decode().strip()
    print("Arduino:", data)

    if data == "PLAY":
        if not is_playing:
            pygame.mixer.music.play(-1)  # loop forever
            is_playing = True

    elif data == "STOP":
        pygame.mixer.music.stop()
        is_playing = False
