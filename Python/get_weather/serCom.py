import serial


def serialCommunication(rain):
    ser = serial.Serial("COM7", 115200)
    ser.read()
    if rain:
        ser.write(b"r")  # rain
    else:
        ser.write(b"n")  # not rain
    ser.close()


# test
if __name__ == "__main__":
    serialCommunication(True)
