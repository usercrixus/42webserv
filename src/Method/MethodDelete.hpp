#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"


class MethodDelete : public IMethod
{
	private:
		bool deleteFile(const std::string& path);

	public:
		MethodDelete(Request &request);
		~MethodDelete();

		void handle();
};

#endif // METHODDELETE_HPP
