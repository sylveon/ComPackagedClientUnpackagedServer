#include <iostream>
#include <Unknwn.h>
#include "winrt/base.h"
#include "winrt/Windows.Foundation.h"

struct ServerObject : winrt::implements<ServerObject, winrt::Windows::Foundation::IStringable>
{
    winrt::hstring ToString()
    {
        std::cout << "Client called server ToString";
        return L"Some instance of ServerObject";
    }
};

struct Factory : winrt::implements<Factory, IClassFactory>
{
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override try
    {
        *ppvObject = nullptr;

        if (!pUnkOuter)
        {
            return winrt::make<ServerObject>().as(riid, ppvObject);
        }
        else
        {
            return CLASS_E_NOAGGREGATION;
        }
    }
    catch (...)
    {
        return winrt::to_hresult();
    }

    HRESULT STDMETHODCALLTYPE LockServer(BOOL) noexcept override
    {
        return S_OK;
    }
};

// {0A5A1E54-9538-4A1A-B9A6-2A2D953A3C52}
static const GUID CLSID_ServerObject =
{ 0xa5a1e54, 0x9538, 0x4a1a, { 0xb9, 0xa6, 0x2a, 0x2d, 0x95, 0x3a, 0x3c, 0x52 } };

int main()
{
    winrt::check_hresult(CoInitialize(nullptr));

    DWORD objectCookie;
    winrt::check_hresult(CoRegisterClassObject(CLSID_ServerObject, winrt::make<Factory>().get(), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &objectCookie));
    std::cout << "Server object factory registered\n";

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}