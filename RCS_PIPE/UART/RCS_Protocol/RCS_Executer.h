
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Build.h
     Discription: RCS Protocol Builder.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 3/23/2009
     Discription: Initial version

*******************************************************************************/



#ifndef __RCS_BUILD_H__
#define __RCS_BUILD_H__

/* return 1: success, 0: not support */
INT8U RCS_SendPackage(RCS_t *rcs);


/* return 1: support, 0: not support
 *
 * HOST_RECV only
 *
 */
INT8U RCS_Executer(RCS_t *rcs);


/* return 1: support, 0: not support
 *
 * HOST_SEND and SLAVE_SEND only
 *
 */
INT8U RCS_Builder(RCS_t *rcs, PFNCT_RCS *post_func);

#endif   /* #ifndef __RCS_BUILD_H__ */

/* EOF */

