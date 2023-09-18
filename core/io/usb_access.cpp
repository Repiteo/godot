/**************************************************************************/
/*  usb_access.cpp                                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "usb_access.h"

#include "core/variant/typed_array.h"
// #include "thirdparty/libusb/libusb.h"

USBAccess::CreateFunc USBAccess::create_func = nullptr;

thread_local Error USBAccess::last_usb_open_error = OK;

Ref<USBAccess> USBAccess::_open(uint16_t p_vendor, uint16_t p_product) {
	Error err = OK;
	Ref<USBAccess> ua = open(p_vendor, p_product, &err);
	last_usb_open_error = err;
	if (err) {
		return Ref<USBAccess>();
	}
	return ua;
}

Ref<USBAccess> USBAccess::open(uint16_t p_vendor, uint16_t p_product, Error *r_error) {
	Ref<USBAccess> ret = create_func();
	ret->vendor_id = p_vendor;
	ret->product_id = p_product;

	Error err = ret->open_internal();

	if (r_error) {
		*r_error = err;
	}
	if (err != OK) {
		ret.unref();
	}

	return ret;
}

TypedArray<Dictionary> USBAccess::get_ports() {
	TypedArray<Dictionary> ports;
	// libusb_context *context = nullptr;
	// libusb_device **list = nullptr;

	// libusb_init(&context);
	// int count = libusb_get_device_list(context, &list);

	// for (int i = 0; i < count; ++i) {
	// 	Dictionary dict;
	// 	ports.append(dict);

	// 	libusb_device *device = list[i];
	// 	libusb_device_descriptor desc;

	// 	dict["bus_number"] = libusb_get_bus_number(device);
	// 	dict["port_number"] = libusb_get_port_number(device);
	// 	dict["device_address"] = libusb_get_device_address(device);
	// 	dict["speed"] = libusb_get_device_speed(device);

	// 	int error = libusb_get_device_descriptor(device, &desc);
	// 	ERR_CONTINUE_MSG(error != LIBUSB_SUCCESS, libusb_error_name(error));

	// 	dict["bLength"] = desc.bLength;
	// 	dict["bDescriptorType"] = desc.bDescriptorType;
	// 	dict["bcdUSB"] = desc.bcdUSB;
	// 	dict["bDeviceClass"] = desc.bDeviceClass;
	// 	dict["bDeviceSubClass"] = desc.bDeviceSubClass;
	// 	dict["bDeviceProtocol"] = desc.bDeviceProtocol;
	// 	dict["bMaxPacketSize0"] = desc.bMaxPacketSize0;
	// 	dict["idVendor"] = desc.idVendor;
	// 	dict["idProduct"] = desc.idProduct;
	// 	dict["bcdDevice"] = desc.bcdDevice;
	// 	dict["iManufacturer"] = desc.iManufacturer;
	// 	dict["iProduct"] = desc.iProduct;
	// 	dict["iSerialNumber"] = desc.iSerialNumber;

	// 	TypedArray<Dictionary> configurations;
	// 	for (int j = 0; j < desc.bNumConfigurations; j++) {
	// 		Dictionary config;
	// 		configurations.append(config);

	// 		libusb_config_descriptor *conf;
	// 		error = libusb_get_config_descriptor(device, j, &conf);
	// 		ERR_CONTINUE_MSG(error != LIBUSB_SUCCESS, libusb_error_name(error));

	// 		config["bLength"] = conf->bLength;
	// 		config["bDescriptorType"] = conf->bDescriptorType;
	// 		config["wTotalLength"] = conf->wTotalLength;
	// 		config["bConfigurationValue"] = conf->bConfigurationValue;
	// 		config["iConfiguration"] = conf->iConfiguration;
	// 		config["bmAttributes"] = conf->bmAttributes;
	// 		config["MaxPower"] = conf->MaxPower;

	// 		TypedArray<Dictionary> interfaces;
	// 		for (int k = 0; k < conf->bNumInterfaces; k++) {
	// 			Dictionary interface;
	// 			interfaces.append(interface);

	// 			const libusb_interface *intr = &conf->interface[k];
	// 			TypedArray<Dictionary> interfaceDescriptors;
	// 			for (int l = 0; l < intr->num_altsetting; l++) {
	// 				Dictionary interfaceDescriptor;
	// 				interfaceDescriptors.append(interfaceDescriptor);

	// 				const libusb_interface_descriptor *intrDesc = &intr->altsetting[l];

	// 				interfaceDescriptor["bLength"] = intrDesc->bLength;
	// 				interfaceDescriptor["bDescriptorType"] = intrDesc->bDescriptorType;
	// 				interfaceDescriptor["bInterfaceNumber"] = intrDesc->bInterfaceNumber;
	// 				interfaceDescriptor["bAlternateSetting"] = intrDesc->bAlternateSetting;
	// 				interfaceDescriptor["bInterfaceClass"] = intrDesc->bInterfaceClass;
	// 				interfaceDescriptor["bInterfaceSubClass"] = intrDesc->bInterfaceSubClass;
	// 				interfaceDescriptor["bInterfaceProtocol"] = intrDesc->bInterfaceProtocol;
	// 				interfaceDescriptor["iInterface"] = intrDesc->iInterface;

	// 				TypedArray<Dictionary> endpoints;
	// 				for (int m = 0; m < intrDesc->bNumEndpoints; m++) {
	// 					Dictionary endpoint;
	// 					endpoints.append(endpoint);

	// 					const libusb_endpoint_descriptor *end = &intrDesc->endpoint[m];

	// 					endpoint["bLength"] = end->bLength;
	// 					endpoint["bDescriptorType"] = end->bDescriptorType;
	// 					endpoint["bEndpointAddress"] = end->bEndpointAddress;
	// 					endpoint["bmAttributes"] = end->bmAttributes;
	// 					endpoint["wMaxPacketSize"] = end->wMaxPacketSize;
	// 					endpoint["bInterval"] = end->bInterval;
	// 					endpoint["bRefresh"] = end->bRefresh;
	// 					endpoint["bSynchAddress"] = end->bSynchAddress;

	// 					PackedByteArray extra;
	// 					for (int n = 0; n < end->extra_length; n++) {
	// 						extra.append(end->extra[n]);
	// 					}
	// 					endpoint["extra"] = extra;
	// 				}
	// 				interfaceDescriptor["Endpoints"] = endpoints;

	// 				PackedByteArray extra;
	// 				for (int m = 0; m < intrDesc->extra_length; m++) {
	// 					extra.append(intrDesc->extra[m]);
	// 				}
	// 				interfaceDescriptor["extra"] = extra;
	// 			}
	// 			interface["Descriptor"] = interfaceDescriptors;
	// 		}
	// 		config["Interfaces"] = interfaces;

	// 		PackedByteArray extra;
	// 		for (int k = 0; k < conf->extra_length; k++) {
	// 			extra.append(conf->extra[k]);
	// 		}
	// 		config["extra"] = extra;
	// 	}
	// 	dict["Configurations"] = configurations;
	// }

	// libusb_free_device_list(list, 1);
	// libusb_exit(context);

	return ports;
}

void USBAccess::_bind_methods() {
	ClassDB::bind_static_method("USBAccess", D_METHOD("open", "vendor_id", "product_id"), &USBAccess::_open);
	ClassDB::bind_static_method("USBAccess", D_METHOD("get_open_error"), &USBAccess::get_open_error);

	ClassDB::bind_method(D_METHOD("close"), &USBAccess::close);

	ClassDB::bind_static_method("USBAccess", D_METHOD("get_ports"), &USBAccess::get_ports);

	ClassDB::bind_method(D_METHOD("get_vendor_id"), &USBAccess::get_vendor_id);
	ClassDB::bind_method(D_METHOD("get_product_id"), &USBAccess::get_product_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "vendor_id"), "", "get_vendor_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "product_id"), "", "get_product_id");
}
