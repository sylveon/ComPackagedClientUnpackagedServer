#include <iostream>
#include <Unknwn.h>
#include "winrt/base.h"
#include "winrt/Windows.Foundation.h"

// {0A5A1E54-9538-4A1A-B9A6-2A2D953A3C52}
static const GUID CLSID_ServerObject =
{ 0xa5a1e54, 0x9538, 0x4a1a, { 0xb9, 0xa6, 0x2a, 0x2d, 0x95, 0x3a, 0x3c, 0x52 } };

int main()
{
    winrt::check_hresult(CoInitialize(nullptr));

    winrt::Windows::Foundation::IStringable serverObject;
    winrt::check_hresult(CoCreateInstance(CLSID_ServerObject, nullptr, CLSCTX_LOCAL_SERVER, winrt::guid_of<decltype(serverObject)>(), winrt::put_abi(serverObject)));
    std::wcout << L"Instance of server object created\n";

    std::wcout << L"The serverObject.ToString() gives " << serverObject.ToString().c_str();
}