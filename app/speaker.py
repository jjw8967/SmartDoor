import pygame
import time

pygame.mixer.init
()
bang = pygame.mixer.Sound('/usr/lib/libreoffice/share/gallery/sounds/train.wav')
while True:
    bang.play()
    time.seep(2.0)
