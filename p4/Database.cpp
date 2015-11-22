#include "Database.h"
using namespace std;

bool Database::specifySchema(const vector<FieldDescriptor>& schema)
{
	//Clear the current Database of everything
	clear();

	m_schema = schema;
	bool indexed = false;

	for (unsigned i = 0; i < m_schema.size(); i++)
	{
		if (m_schema[i].index == it_indexed)
			indexed = true;
		m_fieldIndex.push_back(new MultiMap);
	}
	return indexed;
}

bool Database::addRow(const vector<string>& rowOfData)
{
	if (rowOfData.size() != m_schema.size())
		return false;
	m_rows.push_back(rowOfData);

	//record position of row in vector
	int pos = 0;
	for (;pos < m_rows.size(); pos++)
		if (m_rows[pos] == rowOfData)
			break;

	for (unsigned i = 0; i < m_schema.size(); i++)
		if  (m_schema[i].index == it_indexed)
			m_fieldIndex[i]->insert(rowOfData[i], pos);

	return true;
}

bool Database::loadFromURL(string url)
{
	string page;
	if (!HTTP().get(url, page))
	{
		clear();
		return false;
	}
	if(!loadString(page))
	{
		clear();
		return false;
	}
	return true;
}

bool Database::loadFromFile(string filename)
{
	ifstream ifs;
	string file;
	string temp;
	ifs.open(filename.c_str(), ios::in);
	if (!ifs)
	{
		clear();
		return false;
	}
	while(getline(ifs, temp))
		file += temp + "\n";
	if(!loadString(file))
	{
		clear();
		return false;
	}
	ifs.close();
	return true;
}

int Database::getNumRows() const
{
	return m_rows.size();
}

bool Database::getRow(int rowNum, vector<string>& row) const
{
	if (rowNum >= m_rows.size())
		return false;
	row = m_rows[rowNum];
	return true;
}

int Database::search(const vector<SearchCriterion>& searchCriteria,
			   const vector<SortCriterion>& sortCriteria, vector<int>& results)
{
	vector<int> matchedRowNumber;
	if (searchCriteria.size() == 0)
		return Database::ERROR_RESULT;
	for (unsigned i = 0; i < searchCriteria.size(); i++)
	{
		//Check for match in schema;
		bool match = false;
		int schemaPos = 0;
		for (unsigned j = 0; j < m_schema.size(); j++)
		{
			if (searchCriteria[i].fieldName == m_schema[j].name)
				if (m_schema[j].index == it_indexed)
				{
					match = true;
					schemaPos = j;
					break;
				}
		}

		//Put all rows that fit current search criteria into int unordered set
		unordered_set<int> matchingRows;

		if (!match || (searchCriteria[i].minValue == "" && searchCriteria[i].maxValue == ""))
			return Database::ERROR_RESULT;

		if (searchCriteria[i].minValue != "" && searchCriteria[i].maxValue == "")
		{
			MultiMap::Iterator it = m_fieldIndex[schemaPos]->findEqualOrSuccessor(searchCriteria[i].minValue);
			for (;it.valid(); it.next())
				matchingRows.insert(it.getValue());
		}
		else if (searchCriteria[i].minValue == "" && searchCriteria[i].maxValue != "")
		{
			MultiMap::Iterator it = m_fieldIndex[schemaPos]->findEqualOrPredecessor(searchCriteria[i].maxValue);
			for (;it.valid(); it.prev())
				matchingRows.insert(it.getValue());
		}
		else
		{
			MultiMap::Iterator it = m_fieldIndex[schemaPos]->findEqualOrSuccessor(searchCriteria[i].minValue);
			while (it.valid())
			{
				matchingRows.insert(it.getValue());
				it.next();
				if (it.getKey() > searchCriteria[i].maxValue)
					break;
			}
		}

		//if only 1/first search criteria, then simply replace, otherwise, compare and then replace
		if (i == 0)
			for (unordered_set<int>::iterator it = matchingRows.begin(); it != matchingRows.end(); it++)
				matchedRowNumber.push_back(*it);
		else
		{
			vector<int> temp;
			for (unordered_set<int>::iterator it = matchingRows.begin(); it != matchingRows.end(); it++)
				for (unsigned j = 0; j < matchedRowNumber.size(); j++)
					if (matchedRowNumber[j] == *it)
						temp.push_back(*it);
			matchedRowNumber = temp;
		}
	}

	//Start sorting here
	vector<int> sortSchemas;
	vector<Database::OrderingType> orderSchemas;
	for (unsigned i = 0; i < sortCriteria.size(); i++)
	{
		//Check for match in schema;
		bool match = false;
		for (unsigned j = 0; j < m_schema.size(); j++)
		{
			if (sortCriteria[i].fieldName == m_schema[j].name)
				{
					match = true;
					sortSchemas.push_back(j);
					orderSchemas.push_back(sortCriteria[i].ordering);
					break;
				}
		}
		if (!match)
			return Database::ERROR_RESULT;
	}
	vector<string> rowstrings;
	for (unsigned j = 0; j < sortSchemas.size(); j++)
	{
		for (unsigned i = 0; i < matchedRowNumber.size(); i++)
		{
			vector<string> wholeRow;
			getRow(matchedRowNumber[i], wholeRow);
			rowstrings.push_back(wholeRow[sortSchemas[j]]);
		}
		if (orderSchemas[j] == ot_ascending)
			sort(rowstrings, 0, rowstrings.size());
		else
			sort(rowstrings, rowstrings.size(), 0);
	}

	results = matchedRowNumber;
	return 0;
}

bool Database::loadString(string content)
{
	vector<FieldDescriptor> newSchema;
	int pos = 0;

	//use first line to specify schema
	string firstLine;

	for (; pos < content.size(); pos++)
		if (content[pos] != '\n')
			firstLine += content[pos];
		else
			break;
	
	string firstToken;
	string delimit = ",\n";
	Tokenizer f(firstLine, delimit);
	while (f.getNextToken(firstToken))
	{
		FieldDescriptor fd;
			
		if (firstToken[firstToken.size()-1] == '*')
		{
			string fdName;
			for (unsigned i = 0; i < firstToken.size()-1; i++)
				fdName += firstToken[i];
			fd.name = fdName;
			fd.index = it_indexed;
		}
		else
		{
			fd.name = firstToken;
			fd.index = it_none;
		}

		newSchema.push_back(fd);
	}

	specifySchema(newSchema);

	//takes rest of content and inserts into rows
	pos++;
	while (pos < content.size())
	{
		vector<string> newRow;
		string curLine;
		string token;
		for (; pos < content.size(); pos++)
			if (content[pos] != '\n')
				curLine += content[pos];
			else
				break;

		Tokenizer t(curLine, delimit);
		while (t.getNextToken(token))
			newRow.push_back(token);

		if (newRow.size() != m_schema.size())
			return false;
		
		m_rows.push_back(newRow);
		pos++;
	}
	return true;

}

void Database::clear()
{
	m_schema.clear();
	m_rows.clear();

	for (unsigned i = 0; i < m_fieldIndex.size(); i++)
		delete m_fieldIndex[i];

	m_fieldIndex.clear();
}

void Database::sort(std::vector<string>& rowValues, int first, int last)
{
	if (last-first >= 1)
	{
		int i = first, j = last;
		string tmp;
		string pivot = rowValues[(i+j) / 2];

		//partition
		while (i <= j) 
		{
			while (rowValues[i] < pivot)
				i++;
			while (rowValues[j] > pivot)
				j--;
			if (i <= j) 
			{
				tmp = rowValues[i];
				rowValues[i] = rowValues[j];
				rowValues[j] = tmp;
				i++;
				j--;
			}
		}

		if (first < j)
			sort(rowValues, first, j);
		if (i < last)
			sort(rowValues, i, last);
	}
}

