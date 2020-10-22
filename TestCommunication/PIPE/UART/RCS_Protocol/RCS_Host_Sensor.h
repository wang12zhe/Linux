
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Host_PID.h
     Discription: RCS Protocol Host Commander.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 3/23/2009
     Discription: Initial version

*******************************************************************************/



#ifndef __RCS_HOST_SENSOR_H__
#define __RCS_HOST_SENSOR_H__


void SDCS_SensorCommandSend(RCS_t *rcs);


extern const RCS_CmdNode SCDC_Sensor_HostTable[];
extern const INT8U SCDC_Sensor_HostTotal;


#endif   /* #ifndef __RCS_HOST_PID_H__ */

/* EOF */

