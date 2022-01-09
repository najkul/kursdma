/*
 * Parser_Complex.h
 *
 *  Created on: Jan 4, 2022
 *      Author: jlu
 */

#ifndef INC_PARSER_COMPLEX_H_
#define INC_PARSER_COMPLEX_H_

#define ENDLINE '\n'
#define CARRETURN '\r'

void ParserTakeLine(RingBuffer_t *Buf, uint8_t *Destination);
void Parser_Pars(uint8_t *DateToParse);

#endif /* INC_PARSER_COMPLEX_H_ */
