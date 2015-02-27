#include <iostream>
using namespace std;

#include "fp.h"

int main(int argc,char *argv[])
{
	using namespace fp;
	char filename[128]="/media/sdcard/yesterday.mp3";
	get_file_name(filename);
	get_file_extesion(filename);
	return 0;
}
