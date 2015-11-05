#pragma once

#include <iostream>
#include <string>
#include <vector>

class File
{
	friend class Folder;

	std::string name;
	char* type;
};

class Folder
{
	std::string name;
	Folder* parent;								//pointer to parent folder
	std::vector<Folder*> subs;					//pointers to subfolders
	std::vector<File*> files;					//pointers to files

	bool insertFolder(Folder& _folder);			//put folder in vector
	bool checkDupliSubs(std::string _name);		//check for duplicate folders
	bool deleteContents();
	std::string getPathName();					//get pathname recursively

public:
	Folder();
	~Folder();
	Folder(Folder* _parent, std::string _name);	//create folder under specified parent folder
	Folder* newSubFolder(std::string _name);	//create folder under current folder
	Folder* getParentDir();
	Folder* getSubDir(std::string _name);
	bool deleteSubFolder(std::string _name);
	void DIR();									//list contents of directory
	void PWD();									//print working directory
};

Folder::Folder()
{

}

Folder::~Folder()
{
	//cascading delete
	deleteContents();
	std::cout << "Folder " << name << " deleted" << std::endl;
}

Folder::Folder(Folder* _parent, std::string _name)
{
	parent = _parent;
	name = _name;
}

Folder* Folder::newSubFolder(std::string _name)
{
	Folder* folder = nullptr;

	if (!checkDupliSubs(_name))
	{
		folder = new Folder();
		folder->parent = this;
		folder->name = _name;
	}

	insertFolder(*folder);

	return folder;
}

bool Folder::deleteSubFolder(std::string _name)
{
	for (auto i = subs.begin(); i != subs.end(); ++i)
	{
		if ((*i)->name == _name)
		{	
			delete *i;
			subs.erase(i);
			return true;
		}
	}
	return false;
}

bool Folder::deleteContents()
{
	for (auto &t : files)
	{
		delete t;
	}
	for (auto &t : subs)
	{
		delete t;
	}
	parent = nullptr;
	files.clear();
	subs.clear();

	return true;
}

Folder* Folder::getParentDir()
{
	return parent;
}

Folder* Folder::getSubDir(std::string _name)
{
	Folder* folder = nullptr;

	for (auto &t : subs)
	{
		if (t->name == _name)
		{
			folder = t;
		}
	}
	return folder;
}

bool Folder::insertFolder(Folder& _folder)
{
	for (auto i = subs.begin(); i != subs.end(); ++i)
	{
		if (_folder.name.compare((*i)->name) < 0)
		{
			subs.insert(i, &_folder);
			return true;
		}
	}
	subs.push_back(&_folder);

	return true;
}

bool Folder::checkDupliSubs(std::string _name)
{
	for (auto &t : subs)
	{
		if (t->name == _name)
		{
			return true;
		}
	}
	return false;
}

void Folder::DIR()
{
	for (auto &t : subs)
	{
		std::cout << t->name << std::endl;
	}
	for (auto &t : files)
	{
		std::cout << t->name << "." << t->type << std::endl;
	}
}

void Folder::PWD()
{
	std::cout << getPathName() << std::endl;
}

std::string Folder::getPathName()
{
	std::string str;
	if (parent != nullptr) str = parent->getPathName();

	return str + name + "/";
}