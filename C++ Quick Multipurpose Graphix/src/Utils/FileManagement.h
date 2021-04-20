#pragma once

#include <string>

namespace FileTools
{

	void write(std::string name, std::string type, std::string data)
	{
		FILE* dest = fopen((name + '.' + type).c_str(), "wb");
		if (dest == 0)
		{
			perror(("Writing to " + name + "." + type + " failed.").c_str());
			return;
		}
		
		fwrite(data.c_str(), strlen(data.c_str()), 1, dest);
		
		fclose(dest);
	}

	void write(std::string name, std::string type, const char * data)
	{
		FILE* dest = fopen((name + '.' + type).c_str(), "wb");
		if (dest == 0)
		{
			perror(("Writing to " + name + "." + type + " failed.").c_str());
			return;
		}

		fwrite(data, strlen(data), 1, dest);

		fclose(dest);
	}

}