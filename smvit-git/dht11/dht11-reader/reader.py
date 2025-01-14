import RPi.GPIO as GPIO
import dht11

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()

instance = dht11.DHT11(pin = 17)
result = instance.read()

if result.is_valid():
    with open('/tmp/temp', 'w') as temp:
        temp.write(str(result.temperature))
    with open('/tmp/humidity', 'w') as humidity:
        humidity.write(str(result.humidity))
    print("Temperature: %-3.1f C" % result.temperature)
    print("Humidity: %-3.1f %%" % result.humidity)
else:
    print("Error: %d" % result.error_code)
