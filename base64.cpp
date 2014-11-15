//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 0.0.9
// Alexey Potehin <gnuplanet@gmail.com>, http://www.gnuplanet.ru/doc/cv
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <stdint.h>
#include "base64.hpp"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
static char base64_encode_table[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
static unsigned char base64_decode_table[256] =
{
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   62, 0xff, 0xff, 0xff,   63,
	  52,   53,   54,   55,   56,   57,   58,   59,   60,   61, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

	0xff,    0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
	  15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
	  41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51, 0xff, 0xff, 0xff, 0xff, 0xff,

	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 encode
 * \param [in] p source text pointer
 * \param [in] size source text size
 * \param [in] target target base64 result
 * \param [in] split flag enable split base64 result
 * \param [in] split_size split size
 * \return     base64 result size
 */
size_t base64_encode(const void *p, size_t size, std::string &target, bool split, size_t split_size)
{
	target.reserve(target.size() + (size / (4.0/3.0)));


	uint8_t *buf = (uint8_t *)p;
	size_t index = 0;


	for (;;)
	{
		uint32_t a = 0;

		if (index < size)
		{
			a = a | buf[index++];
		}
		a = a << 8;

		if (index < size)
		{
			a = a | buf[index++];
		}
		a = a << 8;

		if (index < size)
		{
			a = a | buf[index++];
		}

		target += base64_encode_table[(a >> (6*3)) & 63];
		target += base64_encode_table[(a >> (6*2)) & 63];
		target += base64_encode_table[(a >> (6*1)) & 63];
		target += base64_encode_table[(a >> (6*0)) & 63];

		if (index >= size)
		{
			break;
		}

		if ((index % split_size) == 0)
		{
			if (split != false)
			{
				target += "\n";
			}
		}
	}


	if ((size % 3) == 1)
	{
		target[target.size() - 2] = '=';
		target[target.size() - 1] = '=';
	}
	if ((size % 3) == 2)
	{
		target[target.size() - 1] = '=';
	}


	if (split != false)
	{
		target += "\n";
	}

	return target.size();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 encode
 * \param [in] source source text
 * \param [in] target target base64 result
 * \param [in] split flag enable split base64 result
 * \param [in] split_size split size
 * \return     base64 result size
 */
size_t base64_encode(const std::string &source, std::string &target, bool split, size_t split_size)
{
	return base64_encode(source.c_str(), source.size(), target, split, split_size);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 decode
 * \param [in] p source base64 pointer
 * \param [in] size source base64 size
 * \param [in] target target text result
 * \return     text result size
 */
size_t base64_decode(const void *p, size_t size, std::string &target)
{
	target.reserve(target.size() + (size / (4.0/3.0)));


	uint32_t a = 0;
	size_t a_index = 0;
	size_t tail_count = 0;
	const unsigned char *p_base64 = (const unsigned char *)p;


	for (size_t i = 0; i < size; i++, p_base64++)
	{
		uint32_t j = base64_decode_table[*p_base64];

		if ((j == 0xff) && (*p_base64 != '='))
		{
			continue;
		}

		if (*p_base64 != '=')
		{
			a = a | j;
		}
		else
		{
			tail_count++;
		}

		a_index++;
		if (a_index == 4)
		{
			a_index = 0;

			if ((tail_count == 0) || (tail_count == 1) || (tail_count == 2))
			{
				target += char((a >> 16) & 0xFF);
			}

			if ((tail_count == 0) || (tail_count == 1))
			{
				target += char((a >>  8) & 0xFF);
			}

			if (tail_count == 0)
			{
				target += char((a >>  0) & 0xFF);
			}
		}
		a = a << 6;
	}


	return target.size();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 decode
 * \param [in] source source base64
 * \param [in] target target text result
 * \return     text result size
 */
size_t base64_decode(const std::string &source, std::string &target)
{
	return base64_decode(source.c_str(), source.size(), target);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
