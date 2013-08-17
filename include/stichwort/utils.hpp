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

#ifndef STICHWORT_UTILS_H_
#define STICHWORT_UTILS_H_

namespace stichwort
{
	template <typename T>
	class optional
	{
	public:
		optional() : value_(), set_(false) {}
		optional(T v) : value_(v), set_(true) {}
		
		optional(const optional& other) : value_(other.value_) {}
		optional& operator=(const optional& other)
		{
			value_ = other.value_;
			return *this;
		}
		inline T value() const { return value_; }
		inline bool set() const { return set_; }
		inline operator bool() const { return set(); }
		inline T operator *() const { return value(); }
	private:
		T value_;
		bool set_;
	};

	namespace sfinae
	{
		typedef struct { int a; } yes;
		typedef struct { char a; } no;

		struct any_wrapper
		{
			template <class T> any_wrapper(const T&); 
		};
		no operator<<(const any_wrapper&, const any_wrapper&);
		no operator>>(const any_wrapper&, const any_wrapper&);

		template <typename S, typename T>
		struct supports_saving
		{
			template <typename Q> static yes saving_check(const Q&);
			static no saving_check(no);
			static S& s;
			static T& x;
			static const bool value = sizeof(saving_check(s << x)) == sizeof(yes);
		};
	}
}

#endif
