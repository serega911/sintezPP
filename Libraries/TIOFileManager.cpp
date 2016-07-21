#include "../Libraries/TIOFileManager.h"
#include "../Libraries/TSingletons.h"
#include <direct.h>
#include <windows.h>

const std::string								pss::TIOFileManager::s_globalFolder = "..\\Results";

std::string pss::TIOFileManager::getFolder()
{
	return s_globalFolder;
}

void pss::TIOFileManager::writeToFile(eOutputFileType type, const IContainer & container)
{
	auto file = m_oFiles.find(type);
	if (file != m_oFiles.end())
	{
		*(file->second) << std::endl;
		container.writeToFile(*(file->second));
	}
	else
	{
		std::ofstream* out = new std::ofstream;
		std::string fullName = m_containingFolder + "\\" + m_fileNames.at(type);
		out->open(fullName.c_str(), std::ofstream::out);
		m_oFiles.insert({type, out});
		container.writeToFile(*out);
	}
}


bool pss::TIOFileManager::loadFromFile(eOutputFileType type, IContainer & container)
{
	auto file = m_iFiles.find(type);
	if (file != m_iFiles.end())
	{
		if (!file->second->eof())
		{
			container.loadFromFile(*(file->second));
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{	
		std::string fullName = m_containingFolder + "\\" + m_fileNames.at(type);
		std::ifstream* in = new std::ifstream(fullName.c_str());
		m_iFiles.insert({ type, in });
		if ((!in->eof()) && !in->fail())
		{
			container.loadFromFile(*in);
			return true;
		}
		else
		{
			return false;
		}
	} 
}

void pss::TIOFileManager::writeSolutionData()
{
	std::ofstream* file = new std::ofstream;
	m_oFiles.insert({ eOutputFileType::INITIAL_DATA, file });
	std::string fullName = m_containingFolder + "\\" + m_fileNames.at(eOutputFileType::INITIAL_DATA);
	file->open(fullName.c_str(), std::ofstream::out);

	SYSTEMTIME st;
	GetLocalTime(&st);
	*file << "Started:	" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << std::endl;

	const auto& generalData = pss::TSingletons::getInstance()->getGeneralData();
	const auto& initialData = pss::TSingletons::getInstance()->getInitialData();

	*file << initialData._w << ' ' 
		<< initialData._numberOfPlanetaryGears << ' '
		<< generalData._numberOfLinks << ' '
		<< generalData._numberOfFrictions << ' '
		<< generalData._numberOfBrakes << '\n';
	file->flush();
}

pss::TIOFileManager::TIOFileManager()
{
	init();
}

pss::TIOFileManager* pss::TIOFileManager::getInstance()
{
	static pss::TIOFileManager ioFileManager;
	return &ioFileManager;
}

pss::TIOFileManager::~TIOFileManager()
{
	auto file = m_oFiles.find(eOutputFileType::INITIAL_DATA);
	if (file != m_oFiles.end() && file->second->is_open())
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		*(file->second) << "Finished:	" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << std::endl;
	}

	for (auto& it : m_oFiles)
		it.second->close();
	for (auto& it : m_oFiles)
		delete (it.second);
	m_oFiles.clear();
}

void pss::TIOFileManager::init()
{
	m_fileNames[eOutputFileType::FAIL_0] = "failed_0.log";
	m_fileNames[eOutputFileType::FAIL_FREE] = "failed_free.log";
	m_fileNames[eOutputFileType::FAIL_N] = "failed_N.log";
	m_fileNames[eOutputFileType::FAIL_REPETTION] = "failed_repetition.log";
	m_fileNames[eOutputFileType::INITIAL_DATA] = "solution_data.init";
	m_fileNames[eOutputFileType::DONE] = "done.pkp";
	m_fileNames[eOutputFileType::DONE_K] = "done_K.pkp";

	const auto& initialData = pss::TSingletons::getInstance()->getInitialData();
	auto folder = "w" + std::to_string( initialData._w ) + "n" + std::to_string( initialData._numberOfPlanetaryGears );

	m_containingFolder = s_globalFolder + "\\" + folder;

	_mkdir(s_globalFolder.c_str());
	_mkdir(m_containingFolder.c_str());
}
