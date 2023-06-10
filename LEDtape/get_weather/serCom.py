import serial


def serialCommunication(rain):
    with serial.Serial("", 9600, timeout=1) as ser:
        if rain:
            val = "1"  # rain
        else:
            val = "0"  # not rain
        data = bytes(val, "utf-8")
        ser.write(data)

        ser.close()


if __name__ == "__main__":
    serialCommunication(True)

print("Hello, world!")
