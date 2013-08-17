/** Stichwort
 * A simple library for named parameters in C++
 *
 * Copyright (c) 2013, Sergey Lisitsyn <lisitsyn.s.o@gmail.com>
 * All rights reserved.
 *
 * Distributed under the BSD 2-clause license:
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STICHWORT_KEYWORDS_H_
#define STICHWORT_KEYWORDS_H_

#include <stichwort/parameter.hpp>

namespace stichwort
{
	struct DefaultValue
	{
		DefaultValue() { }
	};

	template <typename ValueType> 
	struct Keyword : public KeywordBase
	{
		typedef ValueType Type;
		Keyword(const Identifier& id, const ValueType& def) : 
			KeywordBase(id), default_value(def) { }
		Keyword(const Keyword& pk);
		Keyword& operator=(const Keyword& pk); 
		Parameter operator=(const ValueType& value) const
		{ return Parameter::create(identifier,value); }
		Parameter operator=(const DefaultValue&) const
		{ return Parameter::create(identifier,default_value); }
		ValueType default_value;
	};
	
	struct Forwarder
	{
		Forwarder() { }
		Forwarder(const Forwarder&);
		Forwarder& operator=(const Forwarder&);
		Parameters operator[](Parameters parameters) const
		{ return parameters; }
	};

	namespace
	{
		const DefaultValue take_default;
		const Forwarder kwargs;
	}
}
#endif
