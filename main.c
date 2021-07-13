#undef UNICODE
#define COBJMACROS
#include <stdio.h>
#include <winsock.h>
#include <ws2bth.h>
#include "common.h"
#include <windows.devices.bluetooth.h>
#include <windows.devices.bluetooth.rfcomm.h>
#include <roapi.h>

struct bthgenhandler {
	struct stdifaceopts;
	__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CBluetooth__CBluetoothDevice; struct stdiftrailer;
	char* markend; //struct bthfromaddrhandlerextrndata { __x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDevice* resdevice; };
};

const char szbthgenhandler[sizeof(struct bthgenhandler)];

HRESULT bthgetRfcommsrvcsInvoke(struct bthgenhandler* This,
	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceServicesResult* asyncInfo,
	AsyncStatus asyncStatus) {

	__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommDeviceServicesResult* results;

	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceServicesResult_GetResults(asyncInfo, &results);

	__FIVectorView_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceService* services;

	__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommDeviceServicesResult_get_Services(results, &services);

	UINT32 nsrvs;

	__FIVectorView_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceService_get_Size(services, &nsrvs);

	__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommDeviceService* srvc;

	__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommServiceId* srvcid;

	GUID srvcguid;

	wchar_t chhGUID[260];

	for (UINT32 i = 0; i < nsrvs; ++i)
		__FIVectorView_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceService_GetAt(services, i, &srvc),
		__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommDeviceService_get_ServiceId(srvc, &srvcid),
		__x_ABI_CWindows_CDevices_CBluetooth_CRfcomm_CIRfcommServiceId_get_Uuid(srvcid, &srvcguid),
		StringFromGUID2(&srvcguid, chhGUID, _countof(chhGUID) - 1),
		printf("%ls\n", chhGUID);

	return S_OK;

	SOCKET sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

	SOCKADDR_BTH addrbth = { AF_BTH, 0x889E337B5EACULL,  {0x2BF5B4D3, 0x00A2, 0x4411, {0x88, 0xE1, 0xD1, 0x7D, 0x1B, 0x63, 0x9B, 0xE5}}, BT_PORT_ANY };

	//setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (BOOL[1]) { 1 }, sizeof (BOOL));

	int res = connect(sock, &addrbth, sizeof addrbth);

	printf("%d\n", WSAGetLastError());

	/*const char strformat[] = "hello %d world!";

	char str[sizeof strformat];

	sprintf(str, strformat, n);

	res = send(sock, str, sizeof strformat - 1, 0);*/
	return S_OK;
}

HRESULT bthfromaddrhandlerInvoke(struct bthgenhandler* This,
	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CBluetoothDevice* asyncInfo,
	AsyncStatus asyncStatus) {

	__x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDevice* resdevice;

	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CBluetoothDevice_GetResults(asyncInfo, &resdevice);

	__x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDevice3* resdevice3;

	IUnknown_QueryInterface(resdevice, &IID___x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDevice3, &resdevice3);

	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceServicesResult* asyncop;

	__x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDevice3_GetRfcommServicesAsync(resdevice3, &asyncop);

	static __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CBluetooth__CBluetoothDeviceVtbl bthfromaddrhandlervtbl = { QueryInterface, AddRef, Release, bthgetRfcommsrvcsInvoke };

	static const IID* bthgetRfcommsrvcsimplements[] = { &IID_IUnknown, &IID___FIAsyncOperationCompletedHandler_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceServicesResult, 0 };

	static struct bthgenhandler bthgetRfcommsrvcshandler = { 0, &bthfromaddrhandlervtbl, bthgetRfcommsrvcsimplements, 1, &bthgetRfcommsrvcshandler, };

	/*struct bthgenhandler* bthgetRfcommsrvcshandlercopy = malloc(sizeof bthgetRfcommsrvcshandler);

	*bthgetRfcommsrvcshandlercopy = bthgetRfcommsrvcshandler;

	bthgetRfcommsrvcshandlercopy->shouldbefreed = 1;

	bthgetRfcommsrvcshandlercopy->pBase = bthgetRfcommsrvcshandlercopy;*/

	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CRfcomm__CRfcommDeviceServicesResult_put_Completed(asyncop, &bthgetRfcommsrvcshandler.lpVtbl);

	return S_OK;
}

int main()
{
	WSADATA wsadat; WSAStartup(MAKEWORD(2, 2), &wsadat);

	RoInitialize(RO_INIT_MULTITHREADED);

	__x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDeviceStatics* pBTHStatics;

	activateclassdirect(RuntimeClass_Windows_Devices_Bluetooth_BluetoothDevice, pBTHStatics, IID___x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDeviceStatics);

	/*WSADATA wsadat; WSAStartup(MAKEWORD(2, 2), &wsadat);

	SOCKET sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

	SOCKADDR_BTH addrbth = { AF_BTH, 0x889E337B5EACULL,  {0x2BF5B4D3, 0x00A2, 0x4411, {0x88, 0xE1, 0xD1, 0x7D, 0x1B, 0x63, 0x9B, 0xE5}}, BT_PORT_ANY };

	int res = connect(sock, &addrbth, sizeof addrbth);

	printf("%d\n", WSAGetLastError());

	res = send(sock, "hello 5 world!", sizeof "hello 2 world!" - 1, 0);*/
	static __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CBluetooth__CBluetoothDeviceVtbl bthfromaddrhandlervtbl = { QueryInterface, AddRef, Release, bthfromaddrhandlerInvoke };

	static const IID* bthfromaddrhandlerimplements[] = { &IID_IUnknown, &IID___FIAsyncOperationCompletedHandler_1_Windows__CDevices__CBluetooth__CBluetoothDevice, 0 };

	struct bthgenhandler bthfromaddrhandler = { 0, &bthfromaddrhandlervtbl, bthfromaddrhandlerimplements, 1, &bthfromaddrhandler, };

	__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CBluetoothDevice* bthdeviceop;

	for (int i = 0; i < 1; ++i)

		__x_ABI_CWindows_CDevices_CBluetooth_CIBluetoothDeviceStatics_FromBluetoothAddressAsync(pBTHStatics, 0x889E337B5EACULL, &bthdeviceop),

		__FIAsyncOperation_1_Windows__CDevices__CBluetooth__CBluetoothDevice_put_Completed(bthdeviceop, &bthfromaddrhandler.lpVtbl);
	//CreateThread(0, 0, thread, i, 0, 0);
	Sleep(INFINITE);
}
