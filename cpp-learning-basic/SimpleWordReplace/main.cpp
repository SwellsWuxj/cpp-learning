//form c++ primer 5th

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<memory>
#include<map>
#include<algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fstream;
using std::map;
using std::stringstream;
using std::shared_ptr;

class BuildMap
{
public:
	BuildMap(fstream &infile);
	shared_ptr<map<string, string>> getMap();
private:
	shared_ptr<map<string, string>> m_ruleMap;
};

BuildMap::BuildMap(fstream &infile) :m_ruleMap(new map<string, string>)
{
	string line, key, value;
	while (getline(infile, line))
	{
		stringstream inputLine(line);
		getline(inputLine, key, ' ');
		getline(inputLine, value);
		m_ruleMap->insert({ key, value });
	}
}

class TransForm
{
public:
	TransForm(BuildMap& ruleMap) :m_map(ruleMap){}
	fstream &getOutputFile(fstream& input);
private:
	shared_ptr<fstream> m_output;
	BuildMap m_map;
};


//TODO : let one line be a string,than seach for key words,than replace it with key's value
//
fstream& TransForm::getOutputFile(fstream& input)
{
	string outString;
	string line;
	string word;
	vector<string> vStr;
	while (getline(input, line))
	{
		vStr.clear();
		stringstream inputLine(line);
		while (inputLine >> word)
		{
			//assume the delimiter of word is ' '
			auto ruleMap = m_map.getMap();
			auto iter = ruleMap->find(word);
			if (iter != ruleMap->end())
				word = iter->second;
			vStr.push_back(word);
		}
		for (auto i : vStr)
			cout << i << " ";
		cout << endl;
	}
	return input;
}

shared_ptr<map<string, string>> BuildMap::getMap()
{
	return m_ruleMap;
}

int main()
{
	fstream rule("rule.txt");
	auto ruleMap = BuildMap(rule);
	auto trans = TransForm(ruleMap);
	trans.getOutputFile(fstream("input.txt"));
	system("pause");
	return 0;
}
