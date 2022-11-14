#ifndef __HEADER_SPLIT_H_
#define __HEADER_SPLIT_H_

/* HTML Header Split Function
 * Split for body buffor in name valus next 
 * resolve is name validation copy  
 */ 
void HeaderSplit_(char* body, char* name, char* resolve);

/* HTML Header Body Validation Body Split Function 
 * Split for Header include in validation body next 
 * resolve is body validation copy
 */

int HeaderSplit_to_Url(char* body, char* name, char* resolve);
#endif
