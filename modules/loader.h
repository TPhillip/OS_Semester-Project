#include <string>

using namespace std;

class Loader{
private:
	string filename;
public:
	Loader();
	void readFile(string fname);
};