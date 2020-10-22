
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Parser.h
     Discription: RCS Protocol Parser.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 12/21/2006
     Discription: Initial version

         Version: V1.10
          Author: Alven Lu
Last Modify Date: 12/20/2007
     Discription: Change for Ver=0x61

         Version: V2.00
          Author: Alven Lu
Last Modify Date: 3/13/2009
     Discription: Revised totally, try to support all version code.

*******************************************************************************/



#ifndef __RCS_PARSER_H__
#define __RCS_PARSER_H__


#include "RCS.h"

/* return 1: supported, 0: not support */
INT8U RCS_PatternCheck(RCS_t *rcs);

void RCS_Parser(RCS_t *rcs, INT8U inByte);
void RCS_ParserReset(RCS_t *rcs);

#endif /* #ifndef __RCS_PARSER_H__ */

/* EOF */



