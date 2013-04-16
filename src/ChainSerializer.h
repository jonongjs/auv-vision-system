// ChainSerializer.h
//
// Responsible for serialization of the filter chains

#ifndef CHAINSERIALIZER_H
#define CHAINSERIALIZER_H

#include <string>

class FilterChain;
class FilterCreator;

class ChainSerializer
{
	public:
		FilterChain* loadChain(const std::string& filename, FilterCreator* creator);
		bool saveChain(const std::string& filename, FilterChain* filterChain);
};

#endif//CHAINSERIALIZER_H
