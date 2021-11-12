/*
 * Copyright (C) 2020 Erion Plaku
 * All Rights Reserved
 *
 *   Created by Erion Plaku
 *   www.robotmotionplanning.org
 *
 * Code should not be distributed or used without written permission from the
 * copyright holder.
 */

#ifndef Antipatrea__HashFn_HPP_
#define Antipatrea__HashFn_HPP_

#include <string>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <vector>

namespace Antipatrea
{
    static inline size_t HashCombine( const size_t v1, const size_t v2 )
    {
	return v1 ^ ( v2 + 0x9e3779b9 + ( v1 << 6 ) + ( v1 >> 2 ) );
    }

    template <typename Key> static inline size_t HashItems(const int n, const Key items[])
    {
	if(n == 0)
	    return 0;
	
	std::hash<Key> h;
	auto val = h(items[0]);
	for(int i = 1; i < n; ++i)
	    val = HashCombine(val, h(items[i]));
	return val;
    }

    template <typename Key> static inline size_t HashItems(const std::vector<Key> & items)
    {
	return HashItems<Key>(items.size(), &(items[0]));
    }
    
    
    size_t StringHash( const char *s, const int n );
    
    template <class Key> struct HashStruct { };
    
    template<> struct HashStruct<const std::string>
    { size_t operator()( const std::string &s ) const { return StringHash( s.c_str(), s.size() ); } };
    
    template<> struct HashStruct<std::string>
    { size_t operator()( std::string &s ) const { return StringHash( s.c_str(), s.size() ); } };
    
    template<> struct HashStruct<char*>
    { size_t operator()( const char* s ) const { return s ? StringHash( s, strlen( s ) ) : 0; } };
    
    template<> struct HashStruct<const char*>
    { size_t operator()( const char* s ) const { return s ? StringHash( s, strlen( s ) ) : 0; } };
}

namespace std
{
    template<typename Key1, typename Key2> struct hash< std::pair<Key1, Key2> >
    {
	size_t operator()( std::pair<Key1, Key2> x ) const
	{
	    return Antipatrea::HashCombine( hash<Key1>{}( x.first ), hash<Key2>{}( x.second ) );
	}
    };
}

#endif
