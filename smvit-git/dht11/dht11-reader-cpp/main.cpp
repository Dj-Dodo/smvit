#include <fstream>
#include <iomanip>
#include <iostream>
#include <wiringPi.h>

#define MAXTIMINGS	85
#define DHTPIN		0
int dht11_dat[5] = {0, 0, 0, 0, 0};

constexpr int STATUS_OK = 0;
constexpr int STATUS_ERR_CHCKSM = 1;
constexpr int STATUS_ERR_DATA = 2;

struct Dht11Result {
	int status = STATUS_OK;
	float temperature{};
	float humidity{};
};

float intToDecimal(unsigned int number) {
	float decimal = number;
	while (static_cast<unsigned int>(decimal / 10) > 0) {
		decimal /= 10;
	}

	return decimal / 10;
}

Dht11Result read_dht11_dat() {
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

		if (counter == 255)
			break;

		/* ignore first 3 transitions */
		if ((i >= 4) && (i % 2 == 0)) {
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if (counter > 16)
				dht11_dat[j / 8] |= 1;
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

int main() {
	if ( wiringPiSetup() == -1 ) {
		return 1;
	}

	Dht11Result data;
	int tries = 0;
	do {
		data = read_dht11_dat();
		tries++;
		if (data.status != STATUS_OK) {
			delay(100);
		}
	} while (data.status != STATUS_OK && tries < 15);

	if (data.status != STATUS_OK) {
		std::cerr << "Failed to read data" << std::endl;

		return 1;
	}

	std::cout << "Humidity = " << data.humidity << "%" << std::endl << "Temperature = " << data.temperature << " *C" << std::endl;

	std::ofstream tempFile("/tmp/temperature.txt");
	if (!tempFile) {
		std::cerr << "Failed to open temp file" << std::endl;

		return 1;
	}

	std::ofstream humFile("/tmp/humidity.txt");
	if (!humFile) {
		std::cerr << "Failed to open hum file" << std::endl;
		return 1;
	}

	tempFile << std::setprecision(4) << data.temperature << std::endl;
	humFile << std::setprecision(4) << data.humidity << std::endl;

	return 0;
}
