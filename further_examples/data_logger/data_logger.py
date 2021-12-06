from datetime import datetime
import serial
import time

# file name for the output csv file
FOUT_NAME = "output"

# setup up time interval between recordings in seconds and number of datapoints
TIME_INTERVAL = 10
NUM_DATA_POINTS = 8

# port where the device can be found
PORT = "/dev/ttyACM1"

# open the serial device
dev = serial.Serial(PORT, 9600)


def read_device() -> float:
    """Sub routine to read serial device and returning result as a float."""
    dev.write(b"?")
    result = dev.readline()
    return float(result.decode("utf-8").rstrip())


# empty lists for timestamps and data
timestamps = []
data = []

# start recording
print("Start recording...")
for it in range(NUM_DATA_POINTS):
    # get a timestamp
    timestamps.append(datetime.now())
    data.append(read_device())

    # print the result
    print(f"Data point #{it+1}: {data[it]}")

    if not it == NUM_DATA_POINTS - 1:  # last datapoint was just recorded
        # wait for the time interval to elapse
        time.sleep(TIME_INTERVAL)  # sleep for given time interval


print("Finished recording!")

# now we have all the data, save them as a csv file
with open(FOUT_NAME + ".csv", "w") as fout:
    fout.writelines("Timestamp,Result\r\n")
    for it, timestamp in enumerate(timestamps):
        dat = data[it]
        fout.writelines(f"{timestamp},{dat}\r\n")
