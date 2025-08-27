union SensorData {
	long int temperature;
	long int humidity;
	long int pressure;
};

union PacketPayload {
	char text[256];
	unsigned char binary[256];
	struct ImageData {
		int width;
		int height;
		unsigned char data[1024];
	} image;
};

union Item {
	struct {
		int damage;
		int range;
		int size;
	} weapon;
	struct {
		int healingAmount;
		int duration;
	} potion;
	struct {
		int doorID;
	} key;
};

int main()
{
	// Q: How many bytes will an instance of SensorData require?

	// A: 8 bytes

	// Q: Which is the correct order, from least to greatest, of the memory
	//    requirements of the given unions?

	// A: SensorData, Item, Packetpayload
}
