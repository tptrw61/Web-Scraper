#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <curl/easy.h>

/* 
 * 
 * execution requires command line arguements
 * usage 1: prog_name <case-file>
 *       2: prog_name -i <case-number> ...
 *       3: prog_name -a <case-file> <case-number> ...
 *       4: prog_name -r <case-file> <case-number> ...
 *
 * 1) <case-file> is the name of the file containing all of the cases to be checked, as well as the case data.
 * 2) <case-number> is the case to be checked (supports multiple cases).
 *    This usage simply prints the most recent row of the table to the console.
 * 3) This usage checks all cases in <case-file>, then adds <case-number> to <case-file> (supports multiple cases).
 *    This usage can also be used with a new file to initialize it with <case-number> (and additional cases).
 * 4) This usage removes <case-number> and its data from <case-file>
 *
 */

size_t strCallback(void * packet, size_t size, size_t nmemb, void * strPtr);
std::string readSite(std::string url, int& ok);

void updateFile(std::string fname);
std::vector<std::string> getRecent(std::vector<std::string> cases);
void addToFile(std::string fname, std::vector<std::string> formattedCases);
void removeFromFile(std::string fname, std::vector<std::string> cases);

int main(int argc, char **argv) {
	int (*usage)(int) = [argv](int r){
		std::cerr << "Usage: " << argv[0] << " <case-file>" << std::endl;
		std::cerr << "       " << argv[0] << " -i <case-number> ..." << std::endl;
		std::cerr << "       " << argv[0] << " -a <case-file> <case-number> ..." << std::endl;
		std::cerr << "       " << argv[0] << " -r <case-file> <case-number> ..." << std::endl;
		return r;
	};
	std::string fileName;
	std::vector<std::string> caseNumbers;
	int which = 0; //which usage
	
	//check args
	if (argc < 2)
		return usage(1);
	std::string arg1 = argv[1];
	if (argc == 2 && arg1.compare("-i") != 0 && arg1.compare("-a") != 0 && arg1.compare("-r")) { //could also use (arg1.find("-") == 0)
		which = 1;
		fileName = argv[1];
	} else if (argc >= 3 && arg1.compare("-i") == 0) {
		which = 2;
		for (int i = 2; i < argc; ++i)
			caseNumbers.emplace_back(argv[i]);
	} else if (argc >= 4 && arg1.compare("-a") == 0) {
		which = 3;
		fileName = argv[2];
		for (int i = 3; i < argc; ++i)
			caseNumbers.emplace_back(argv[i]);
	} else if (argc >= 4 && arg1.compare("-r") == 0)  {
		which = 4;
		for (int i = 3; i < argc; ++i)
			caseNumbers.emplace_back(argv[i]);
	} else {
		return usage(argc);
	}

	curl_global_init(CURL_GLOBAL_ALL);
	
	switch (which) {
	case 1:
		updateFile(fileName);
		break;
	case 2:
		for (std::string s : getRecent(caseNumbers))
			std::cout << s << std::endl;
		break;
	case 3:
		updateFile(fileName);
		addToFile(getRecent(caseNumbers));
		break;
	case 4:
		removeFromFile(caseNumbers);
		break;
	default:
		std::cerr << "Internal error: execution terminated" << std::endl;
		return -1;
	}
	
	//std::string html = readSite(<URL>);
	
	return 0;
}
1


void updateFile(std::string fname) {}

std::vector<std::string> getRecent(std::vector<std::string> cases) { return std::vector<std::string>; }

void addToFile(std::string fname, std::vector<std::string> formattedCases) {}

void removeFromFile(std::string fname, std::vector<std::string> cases) {}









std::string readSite(std::string url, int& ok) {
	CURL * handle;
	CURLcode code;
	std::string text = "";
	handle = curl_easy_init();
	
	if (curl_easy_setopt(handle, CURLOPT_URL, url.c_str()) == CURLE_OUT_OF_MEMORY) {
		std::cout << err << std::endl;
		return "";
	}
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, strCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&text);
	curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, err);
	code = curl_easy_perform(handle);
	curl_easy_cleanup(handle);
	
	if (code == CURLE_OK) {
		return text;
	} else {
		std::cout << err << std::endl;
		return "";
	}
	
}

size_t strCallback(void * packet, size_t size, size_t nmemb, void * strPtr) {
	std::string packetStr = "";
	for (auto i = 0; i < size * nmemb; i++) {
		packetStr += ((char *)packet)[i];
	}
	std::string *str = (std::string *)strPtr;
	*str += packetStr;
	return packetStr.length();
}
