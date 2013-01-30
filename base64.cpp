//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 0.0.6
// Alexey Potehin http://www.gnuplanet.ru/doc/cv
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <stdint.h>
#include "base64.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
static char base64_encode_table[64]=
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
static unsigned char base64_decode_table[256]=
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
// encode data to base64
std::string base64_encode(const void *p, size_t size, bool split)
{
	std::string temp;
	temp.reserve(size / (4.0/3.0));


	uint8_t *buf = (uint8_t*)p;
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

		int base64_index1 = (a >> (6*3)) & 63;
		int base64_index2 = (a >> (6*2)) & 63;
		int base64_index3 = (a >> (6*1)) & 63;
		int base64_index4 = (a >> (6*0)) & 63;

		if (index < size)
		{
			temp += base64_encode_table[base64_index1];
			temp += base64_encode_table[base64_index2];
			temp += base64_encode_table[base64_index3];
			temp += base64_encode_table[base64_index4];

			if (((index/19)*19) == index)
			{
				if (split != false)
				{
					temp += "\n";
				}
			}
		}
		else
		{
			if ((((size/3)*3)+0) == size)
			{
				temp += base64_encode_table[base64_index1];
				temp += base64_encode_table[base64_index2];
				temp += base64_encode_table[base64_index3];
				temp += base64_encode_table[base64_index4];
				break;
			}
			if ((((size/3)*3)+1) == size)
			{
				temp += base64_encode_table[base64_index1];
				temp += base64_encode_table[base64_index2];
				temp += "=";
				temp += "=";
				break;
			}
			if ((((size/3)*3)+2) == size)
			{
				temp += base64_encode_table[base64_index1];
				temp += base64_encode_table[base64_index2];
				temp += base64_encode_table[base64_index3];
				temp += "=";
				break;
			}
		}
	}

	if (split != false)
	{
		temp += "\n";
	}

	return temp;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// encode string to base64
std::string base64_encode(const std::string& base64, bool split)
{
	return base64_encode(base64.c_str(), base64.size(), split);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// decode base64 to string
size_t base64_decode(const void *p, size_t size, std::string& out)
{
	out.clear();
	out.reserve(size * (4.0/3.0));


	uint32_t a = 0;
	size_t a_index = 0;
	size_t tail_count = 0;
	const unsigned char *p_base64 = (const unsigned char*)p;


	for (size_t i = 0; i < size; i++, p_base64++)
	{
		uint32_t j = base64_decode_table[*p_base64];

		if ((j == uint32_t(-1)) && (*p_base64 != '=')) continue;


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
				out += char((a >> 16) & 0xFF);
			}

			if ((tail_count == 0) || (tail_count == 1))
			{
				out += char((a >>  8) & 0xFF);
			}

			if (tail_count == 0)
			{
				out += char((a >>  0) & 0xFF);
			}
		}
		a = a << 6;
	}


	return out.size();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// decode base64 to string
size_t base64_decode(const std::string& base64, std::string& out)
{
	return base64_decode(base64.c_str(), base64.size(), out);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
