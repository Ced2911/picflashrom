#pragma once
#include "hidapi.h"
#include "ccrwrom.h"
#include "libusb.h"

#define W_DATA_SIZE	(USB_PACKET_SIZE - 0x6)

#pragma pack(1)
typedef struct
{
	union {
#if 0
		uint8_t bytes[USB_PACKET_SIZE+1];
#else
		uint8_t bytes[USB_PACKET_SIZE];
#endif
		struct {
			//uint8_t report;
			uint8_t command;
			uint32_t address;
			uint32_t size;
		};
		struct {
			//uint8_t w_report;
			uint8_t w_command;
			uint32_t w_address;
			uint8_t w_size;
			uint8_t w_data[W_DATA_SIZE];
		};
	};

} usb_packet_w_t;


typedef struct
{
	uint8_t bytes[USB_PACKET_SIZE];
	//uint8_t bytes[9];
} usb_packet_t;

#pragma pack()


class usb_c {
private:
	hid_device * hid_handle;
public:
	usb_c() {
		hid_handle = NULL;
	}
	uint32_t write(uint8_t * in, uint32_t size);
	uint32_t write(usb_packet_w_t & pkt, uint32_t size) {
		return write(pkt.bytes, size);
	}
	uint32_t read(uint8_t * out, uint32_t size);
	uint32_t read(usb_packet_w_t & pkt, uint32_t size) {
		return read(pkt.bytes, size);
	}
	hid_device * connect();
	void close();
};


class libusb_c {
private:
	libusb_device_handle * libusb_handle;
	libusb_context * libusb_ctx;
public:
	libusb_c() {
		libusb_handle = NULL;
	}

	uint32_t cmd(uint8_t command, uint32_t arg0 = 0, uint32_t arg1 = 0);
	uint32_t write(uint8_t * in, uint32_t size);
	uint32_t write(usb_packet_w_t & pkt, uint32_t size) {
		return write(pkt.bytes, size);
	}
	uint32_t read(uint8_t * out, uint32_t size);
	uint32_t read(usb_packet_w_t & pkt, uint32_t size) {
		return read(pkt.bytes, size);
	}
	libusb_device_handle * connect();

	void close();
};

extern libusb_c usb;