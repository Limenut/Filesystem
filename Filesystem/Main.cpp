#include "Folder.h"

int main()
{
	Folder* currentFolder = new Folder(nullptr, "root");
	currentFolder->newSubFolder("OS");
	currentFolder->newSubFolder("users");
	currentFolder->newSubFolder("program files");

	currentFolder->DIR();

	currentFolder = currentFolder->getSubDir("users");
	currentFolder->newSubFolder("newb");

	currentFolder = currentFolder->getSubDir("documents");
	currentFolder->PWD();

	currentFolder = currentFolder->getParentDir()->getParentDir();

	delete currentFolder;
}