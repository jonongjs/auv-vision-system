// ChainSerializer.cpp
//
// Responsible for serialization of the filter chains

#include "ChainSerializer.h"
#include "ImageFilterBase.h"
#include "FilterChain.h"
extern "C" {
#include "jsmn.h"
}
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

// Helper function
string wrapString(const string& str) {
	return "\"" + str + "\"";
}


FilterChain* ChainSerializer::loadChain(const string& filename, FilterCreator *creator)
{
	ifstream fin(filename.c_str());
	if (!fin) return 0;

	string jsonstr;
	getline(fin, jsonstr, '\0');

	jsmn_parser p;
	jsmn_init(&p);

	int numTokens = 25;
	jsmntok_t *tokens = 0;
	int result = JSMN_SUCCESS;
	do {
		delete [] tokens;
		numTokens *= 2;
		tokens = new jsmntok_t[numTokens];

		result = jsmn_parse(&p, jsonstr.c_str(), tokens, numTokens);
		if (result == JSMN_ERROR_PART || result == JSMN_ERROR_INVAL)
			break;
	} while (result == JSMN_ERROR_NOMEM); // Retry until we read all tokens

	if (result == JSMN_SUCCESS) {
		FilterChain *fChain = new FilterChain(creator);
		assert(tokens[0].type == JSMN_OBJECT);
		assert(tokens[0].size >= 2);
		// Child should be an array of filters
		if (jsonstr.substr(tokens[1].start, tokens[1].end-tokens[1].start) == "filters") {
			assert(tokens[2].type == JSMN_ARRAY);
			int numChildren = tokens[2].size;
			int child = 0;
			int n = 3;
			while (child < numChildren) {
				++child;
				int index = n++;

				string type = jsonstr.substr(tokens[index].start, tokens[index].end-tokens[index].start);
				ImageFilterBase *f = fChain->appendNewFilter(type);

				index = n++; ++child;
				int size = tokens[index].size;
				assert(tokens[index].type == JSMN_OBJECT);
				for (int i=0; i<size; i+=2) {
					index = n++;
					string propName = jsonstr.substr(tokens[index].start, tokens[index].end-tokens[index].start);
					index = n++;
					string value = jsonstr.substr(tokens[index].start, tokens[index].end-tokens[index].start);

					f->setProperty(propName, value);
				}
			}
		}
		delete [] tokens;
		return fChain;
	}

	delete [] tokens;
	return 0;
}

bool ChainSerializer::saveChain(const string& filename, FilterChain* filterChain)
{
	ofstream fout(filename.c_str());

	if (!fout) return false;

	fout << "{\n"
		<< "\"filters\": [\n";

	const FilterChain::Chain& chain = filterChain->getChain();
	FilterChain::Chain::const_iterator filter;
	for (filter=chain.begin(); filter!=chain.end(); ++filter) {
		if (filter != chain.begin()) {
			fout << ",\n";
		}
		fout << wrapString( (*filter)->name ) << ":"
			<< "{ ";

		const FilterProperties& properties = (*filter)->getFilterProperties();
		FilterProperties::const_iterator prop;
		for (prop=properties.begin(); prop!=properties.end(); ++prop) {
			if (prop != properties.begin()) {
				fout << ", ";
			}
			fout << wrapString( prop->name ) << ":"
				<< wrapString( (*filter)->getProperty(prop->name) );
		}

		fout << " }";
	}

	fout << "\n]\n"
		<< "}" << endl;

	return true;
}
