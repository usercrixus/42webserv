#include "MethodDelete.hpp"

MethodDelete::MethodDelete(Request &request):
IMethod(request)
{
}

MethodDelete::~MethodDelete()
{
}

void MethodDelete::handle()
{
	_response.setBody("DELETE method received for path: " + _request.getPath());
}
