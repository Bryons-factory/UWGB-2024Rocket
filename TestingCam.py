Python 3.12.1 (tags/v3.12.1:2305ca5, Dec  7 2023, 22:03:25) [MSC v.1937 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> from gpiozero import Button
... from picamera import PiCamera
... from datetime import datetime
... from signal import pause
... 
... button = Button(2)
... camera = PiCamera()
... 
... def capture():
...     timestamp = datetime.now().isoformat()
...     camera.capture('/home/raspberrypi/%s.jpg' % timestamp)
... 
... button.when_pressed = capture
... 
