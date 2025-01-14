#include <bitset>
#include <csignal>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <linux/i2c-dev.h>
extern "C" {
	#include <i2c/smbus.h>
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define MAXTIMINGS	85
#define DHTPIN		0
int dht11_dat[5] = {0, 0, 0, 0, 0};

constexpr int STATUS_OK = 0;
constexpr int STATUS_ERR_CHCKSM = 1;
constexpr int STATUS_ERR_DATA = 2;

constexpr int ENS160_OPMODE_REGISTER = 0x10;
constexpr int ENS160_STATUS_REGISTER = 0x20;
constexpr int ENS160_AIR_QUALITY_REGISTER = 0x21;
constexpr int ENS160_TVOC_REGISTER = 0x22;
constexpr int ENS160_EOC_REGISTER = 0x24;

constexpr int STATUS_STOP = 0;
constexpr int STATUS_PREPARING = 1;
constexpr int STATUS_NORMAL = 2;
constexpr int STATUS_WARNING = 3;
constexpr int STATUS_DANGER = 4;

constexpr int LED_PIN = 3;
std::atomic_int status = STATUS_PREPARING;

struct Dht11Result {
	int status = STATUS_OK;
	float temperature{};
	float humidity{};
};

float intToDecimal(unsigned int number);
Dht11Result readDht11Data();
void readTempAndHum();
void readAirQuality();
void loop();
void ledLoop();

double lastTemp = 0;
double lastHum = 0;
int airQualityIndex = 0;
int tvoc = 0;
int eco2 = 0;

void sigHandler(int code) {
	status = 0;
}

int main() {
	std::signal(SIGINT, sigHandler);
	std::signal(SIGTERM, sigHandler);
	std::signal(SIGABRT, sigHandler);

	if ( wiringPiSetup() == -1 ) {
		std::cerr << "Failed to setup wiringPi" << std::endl;

		return 1;
	}

	std::thread ledThread(ledLoop);
	loop();
	ledThread.join();

	return 0;
}

void loop() {
	while (status.load() != 0) {
		readTempAndHum();
		readAirQuality();
		delay(2000);
	}
}

void readTempAndHum() {
	Dht11Result data;
	int tries = 0;
	do {
		data = readDht11Data();
		tries++;
		if (data.status != STATUS_OK) {
			delay(100);
		}
	} while (data.status != STATUS_OK && tries < 15);

	if (data.status != STATUS_OK) {
		std::cerr << "Failed to read data" << std::endl;

		return;
	}

	lastHum = data.humidity;
	lastTemp = data.temperature;
	std::cout << "Humidity = " << data.humidity << "%" << std::endl << "Temperature = " << data.temperature << " *C" << std::endl;

	std::ofstream tempFile("/tmp/temperature.txt");
	if (!tempFile) {
		std::cerr << "Failed to open temp file" << std::endl;

		return;
	}
	tempFile << std::setprecision(4) << data.temperature << std::endl;
	tempFile.close();

	std::ofstream humFile("/tmp/humidity.txt");
	if (!humFile) {
		std::cerr << "Failed to open hum file" << std::endl;

		return;
	}
	humFile << std::setprecision(4) << data.humidity << std::endl;
	humFile.close();
}

void readAirQuality() {
	int busFileDescriptor = open("/dev/i2c-1", O_RDWR);

	if (busFileDescriptor < 0) {
		std::cerr << "Failed to open i2c device: " << errno << std::endl;
		close(busFileDescriptor);

		return;
	}

	if (ioctl(busFileDescriptor, I2C_SLAVE, 0x53) < 0) {
		std::cerr << "Failed to acquire bus access and/or talk to slave" << std::endl;
		close(busFileDescriptor);

		return;
	}

	const auto opMode = i2c_smbus_read_byte_data(busFileDescriptor, ENS160_OPMODE_REGISTER);
	if (opMode < 0) {
		std::cerr << "Failed to read opMode" << std::endl;
		close(busFileDescriptor);

		return;
	}

	std::cout << "Operating mode = " << opMode << std::endl;

	if (opMode != 0x02) {	// if not in Standard mode
		i2c_smbus_write_byte_data(busFileDescriptor, ENS160_OPMODE_REGISTER, 0x02);
	}

	// TODO write temperature and humidity

	const auto deviceStatus = i2c_smbus_read_byte_data(busFileDescriptor, ENS160_STATUS_REGISTER);
	if (deviceStatus < 0) {
		std::cerr << "Failed to read device status" << std::endl;
		close(busFileDescriptor);

		return;
	}

	std::cout << "Device status = " << deviceStatus << std::endl;

	const std::bitset<8> statusBits(deviceStatus);
	const int validity = (statusBits[3] << 1) | statusBits[2];
	bool preparing = false;
	if (validity != 0) {
		status = STATUS_PREPARING;
		preparing = true;
	}
	std::cout << "Validity = " << validity << std::endl;

	const auto airQualityIndex = i2c_smbus_read_byte_data(busFileDescriptor, ENS160_AIR_QUALITY_REGISTER);
	if (airQualityIndex < 0) {
		std::cerr << "Failed to read air quality index" << std::endl;
		close(busFileDescriptor);

		return;
	}

	::airQualityIndex = airQualityIndex & 0b111;
	if (!preparing) {
		if (airQualityIndex > 3) {
			status = STATUS_DANGER;
		} else if (airQualityIndex > 2) {
			status = STATUS_WARNING;
		} else {
			status = STATUS_NORMAL;
		}
	}
	std::cout << "Air quality index = " << ::airQualityIndex << std::endl;

	const auto tvoc = i2c_smbus_read_word_data(busFileDescriptor, ENS160_TVOC_REGISTER);
	if (tvoc < 0) {
		std::cerr << "Failed to read tvoc" << std::endl;
		close(busFileDescriptor);

		return;
	}
	::tvoc = tvoc;
	std::cout << "TVOC = " << ::tvoc << std::endl;

	const auto eco2 = i2c_smbus_read_word_data(busFileDescriptor, ENS160_EOC_REGISTER);
	if (eco2 < 0) {
		std::cerr << "Failed to read eCO2" << std::endl;
		close(busFileDescriptor);

		return;
	}
	::eco2 = eco2;
	std::cout << "eCO2 = " << ::eco2 << std::endl;

	std::ofstream airQualityFile("/tmp/air_quality.txt");
	if (!airQualityFile) {
		std::cerr << "Failed to open air_quality file" << std::endl;
		close(busFileDescriptor);

		return;
	}
	airQualityFile << ::airQualityIndex << std::endl;
	airQualityFile.close();

	std::ofstream tvocFile("/tmp/tvoc.txt");
	if (!tvocFile) {
		std::cerr << "Failed to open tvoc file" << std::endl;
		close(busFileDescriptor);

		return;
	}
	tvocFile << ::tvoc << std::endl;
	tvocFile.close();

	std::ofstream eco2File("/tmp/eco2.txt");
	if (!eco2File) {
		std::cerr << "Failed to open eco2 file" << std::endl;
		close(busFileDescriptor);

		return;
	}
	eco2File << ::eco2 << std::endl;
	eco2File.close();
}

Dht11Result readDht11Data() {
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	/* pull pin down for 18 milliseconds */
	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	/* then pull it up for 40 microseconds */
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(40);
	/* prepare to read the pin */
	pinMode(DHTPIN, INPUT);

	/* detect change and read data */
	for (i = 0; i < MAXTIMINGS; i++) {
		counter = 0;
		while (digitalRead(DHTPIN) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 255) {
				break;
			}
		}
		laststate = digitalRead(DHTPIN);

		if (counter == 255){
			break;
		}

		/* ignore first 3 transitions */
		if ((i >= 4) && (i % 2 == 0)) {
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if (counter > 16){
				dht11_dat[j / 8] |= 1;
			}
			j++;
		}
	}

	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if (j < 40) {
		return {
			.status = STATUS_ERR_DATA,
		};
	}

	if (!(dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
		return {
			.status = STATUS_ERR_CHCKSM,
		};
	}

	return {
		.status = STATUS_OK,
		.temperature = static_cast<float>(dht11_dat[2]) + intToDecimal(dht11_dat[3]),
		.humidity = static_cast<float>(dht11_dat[0]) + intToDecimal(dht11_dat[1]),
	};
}

void ledLoop() {
	pinMode(LED_PIN, OUTPUT);
	auto status = ::status.load();
	while (status != 0) {
		switch (status) {
			case STATUS_PREPARING:
				digitalWrite(LED_PIN, HIGH);
				delay(1000);
				digitalWrite(LED_PIN, LOW);
				delay(1000);
				break;
			case STATUS_NORMAL:
				digitalWrite(LED_PIN, LOW);
				delay(1000);
				break;
			case STATUS_WARNING:
				digitalWrite(LED_PIN, HIGH);
				delay(1000);
				break;
			case STATUS_DANGER:
				digitalWrite(LED_PIN, HIGH);
				delay(500);
				digitalWrite(LED_PIN, LOW);
				delay(500);
				break;
			default:
				break;
		}
		status = ::status.load();
	}
	digitalWrite(LED_PIN, LOW);
}

float intToDecimal(unsigned int number) {
	float decimal = number;
	while (static_cast<unsigned int>(decimal / 10) > 0) {
		decimal /= 10;
	}

	return decimal / 10;
}
