#include "usb.h"
#ifdef WIN32
#include <Windows.h>
#else
#define Sleep(x) #error("ooops Sleep")
#endif


hid_device * usb_c::connect() {
	wchar_t wstr[MAX_STR];
	int res = 0;
	hid_handle = NULL;

	if (hid_init() == 0) {
		hid_handle = hid_open(USB_VID, USB_PID, NULL);
		if (hid_handle) {
			res = hid_set_nonblocking(hid_handle, true);

			// Read the Manufacturer String
			if (hid_get_manufacturer_string(hid_handle, wstr, MAX_STR) == 0) {
				DBGPrintf(L"Manufacturer String: %s\n", wstr);
			}

			// Read the Product String
			if (hid_get_product_string(hid_handle, wstr, MAX_STR) == 0) {
				DBGPrintf(L"Product String: %s\n", wstr);
			}

			return hid_handle;
		}
	}
	DBGPrintf(L"Error device not found....\n");
	return NULL;
}

uint32_t usb_c::write(uint8_t * in, uint32_t size) {
	int res = 0;
	int retries = 5;
	while (res < 1) {
		res = hid_write(hid_handle, in, size);
		if (res == -1 ) {
			DBGPrintf(L"usb_write error...\n");
			return 0;
		}
		if (retries == 0) {
			DBGPrintf(L"usb_write error timeout...\n");
			return 0;
		}
		if (res < 1) {
			retries--;
			Sleep(10);
		}
	}

	return (uint32_t)res;
}

uint32_t usb_c::read(uint8_t * out, uint32_t size) {
	int res = 0;
	int retries = 500;
	while (res < 1) {
		res = hid_read(hid_handle, out, size);
		if (res == -1) {
			DBGPrintf(L"usb_read error...\n");
			return 0;
		}
		if (retries == 0) {
			DBGPrintf(L"usb_read error timeout...\n");
			return 0;
		}
		if (res < 1) {
			retries--;
			Sleep(10);
		}
	}
	return (uint32_t)res;
}

void usb_c::close() {
	hid_exit();
}



libusb_device_handle * libusb_c::connect() {
	wchar_t wstr[MAX_STR];
	int res = 0;
	libusb_handle = NULL;
	libusb_device_descriptor deviceDescriptor;
	libusb_device** list;
	ssize_t numberOfDevices;

	if (libusb_init(&libusb_ctx) == 0) {
		
		numberOfDevices = libusb_get_device_list(NULL, &list);
		//Now search through every item in the list, to see if any of them match
		//our device with matching VID/PID
		for (ssize_t i = 0; i < numberOfDevices; i++)
		{
			//Fetch the device descriptor for a device in the list
			libusb_get_device_descriptor(list[i], &deviceDescriptor);
			//Check if the VID/PID in the device descriptor match the one we are looking for
			if ((deviceDescriptor.idVendor == USB_VID) && (deviceDescriptor.idProduct == USB_PID))
			{
				//Now try to open the device.
				if (libusb_open(list[i], &libusb_handle) == 0)
				{
					if (libusb_claim_interface(libusb_handle, 0) == 0)
					{
						libusb_free_device_list(list, 1);


						// libusb_set_debug(libusb_ctx, 4);
						return  libusb_handle;
					}
				}
				else
				{
					//Something went wrong if we get to here...
					libusb_close(libusb_handle);
					libusb_handle = NULL;
				}
			}
		}

		//Free up the resources associated with the device list, now that we are done using it
		libusb_free_device_list(list, 1);

	}
	DBGPrintf(L"Error device not found....\n");
	return NULL;
}

uint32_t libusb_c::cmd(uint8_t command, uint32_t arg0, uint32_t arg1) {
	int res = 0;
	uint32_t requestType = 0;
	int transfered = 0;
	uint32_t data[2] = {arg0, arg1};

	res = libusb_control_transfer(libusb_handle, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_OUT, command, 0, 0, (uint8_t*)data, sizeof(data), 10000);

	if (res != sizeof(data)) {
		DBGPrintf(L"usb_cmd error... %d\n", res);
		return 0;
	}

	return (uint32_t)transfered;
}

uint32_t libusb_c::write(uint8_t * in, uint32_t size) {
	int res = 0;
	int transfered = 0;
	res = libusb_bulk_transfer(libusb_handle, 0x01, in, size, &transfered, 10000);

	if (res != 0) {
		DBGPrintf(L"usb_write error...\n");
		return 0;
	}

	return (uint32_t)transfered;
}

uint32_t libusb_c::read(uint8_t * out, uint32_t size) {
	int res = 0;
	int transfered = size;
	res = libusb_bulk_transfer(libusb_handle, 0x81, out, size, &transfered, 10000);

	if (res != 0) {
		DBGPrintf(L"usb_read error...\n");
		return 0;
	}
	return (uint32_t)transfered;
}

void libusb_c::close() {
	libusb_close(libusb_handle);
}

libusb_c usb;

//usb_c usb;

