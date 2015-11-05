/*
 * Author: Agostino Mascitti <agostino690@gmail.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file
 * @ingroup grove
 * @brief Morse interpreter using Internet example
 *
 * This project shows how to use Grove Touch or Button sensor to read a string
 * and than pass it to your computer through Internet.
 *
 * @hardware Sensors used:
 * Grove Touch (GroveTouch)
 * Grove Button (GroveButton)
 * Grove LCD (Jhd1313m1)
 *
 * @ld -lupm-i2clcd -lupm-grove
 *
 * @date 24/ott/2015
 */
 
#ifndef CLIENT_H_
#define CLIENT_H_

bool sendToComputer(const char*);

#endif /* CLIENT_H_ */
