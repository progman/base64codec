//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 0.0.9
// Alexey Potehin <gnuplanet@gmail.com>, http://www.gnuplanet.ru/doc/cv
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#ifndef BASE64_H_INCLUDE
#define BASE64_H_INCLUDE
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <stdio.h>
#include <string>
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
size_t base64_encode(const void *p, size_t size, std::string &target, bool split=false, size_t split_size=19);

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
size_t base64_encode(const std::string &source, std::string &target, bool split=false, size_t split_size=19);

/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 decode
 * \param [in] p source base64 pointer
 * \param [in] size source base64 size
 * \param [in] target target text result
 * \return     text result size
 */
size_t base64_decode(const void *p, size_t size, std::string &target);

/**
 * \file       base64.hpp
 * \Author     gnuplanet@gmail.com
 * \brief      base64 decode
 * \param [in] source source base64
 * \param [in] target target text result
 * \return     text result size
 */
size_t base64_decode(const std::string &source, std::string &target);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#endif
