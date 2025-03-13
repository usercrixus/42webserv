#include "MethodPost.hpp"

MethodPost::MethodPost(Request &request):
IMethod(request)
{
}

MethodPost::~MethodPost()
{
}

void MethodPost::handle()
{
	_response.setBody("POST method received with body:\n" + _request.getBody());
}
