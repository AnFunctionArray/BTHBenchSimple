#include <Hstring.h>
#include <setjmp.h>
#include <inspectable.h>
#include <crtdbg.h>
#define startinfintiteloop for(;;)

#define activateclassdirect(name, ptr, iid) activateclassdirect((name), sizeof (name), &(ptr), &(iid))

#define activateclasslight(name, ptr, iid) activateclasslight((name), sizeof (name), &(ptr), &(iid))

#define activateclasslight2(name, ptr, iid)  \
activateclasslight2((name), sizeof (name), &(ptr), &(iid))

extern QueryInterface(), stub(), AddRef(), Release(), GetIids(),
GetRuntimeClassName(), GetTrustLevel(), QueryInterfaceWithInner();

extern HSTRING (createreference)();

static HSTRING(*_createreference)() = createreference;

#define createreferencewithsize(string, size, ref) _createreference((string), (size), (&ref))

#define createreference(string, ref) createreference((string), sizeof (string), (&ref))

struct stdifaceopts {
	unsigned int shouldbefreed : 1;
};

struct stdiftrailer {
	const IID** implements; ULONG count; struct baseinterface* pBase;
	size_t szExternal; HSTRING classname; HRESULT(*QueryInterfaceHookOnMatch)(struct standardinterfacepart* This,
		REFIID riid, char** ppvObject);
};

struct standardinterfacepart {
	IUnknownVtbl* lpVtblornull; struct stdiftrailer;
};

struct baseinterface {
	struct stdifaceopts;
	struct standardinterfacepart interfaces[1];
};