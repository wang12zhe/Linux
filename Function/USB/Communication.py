###  https://blog.csdn.net/chenjuelv0163/article/details/100840723
###  https://blog.csdn.net/qq_36272641/article/details/86244596
###  https://blog.csdn.net/weixin_42967006/article/details/108755972
###  https://blog.csdn.net/jiguangfan/article/details/8657913
###  https://www.cnblogs.com/alants/p/4454330.html
###  pip install pyusb

import usb.core
import usb.util
import sys
 
dev =  usb.core.find(idVendor= 0x0525, idProduct= 0xA4A6)

#print (dev)
cfg = dev.get_active_configuration()
intf = cfg[(0,0)]
ep = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT
)
#print("=======================================\n")
print (ep)
#print ('The length of data(write USB) is:', ep.write('WANTFORGETTXT'))
# ep_read = usb.util.find_descriptor(
#     intf,
#     # match the first IN endpoint
#     custom_match = \
#     lambda e: \
#         usb.util.endpoint_direction(e.bEndpointAddress) == \
#         usb.util.ENDPOINT_IN
# )
# data_len = ep_read.read(4)
# print ('Get USB data:',data_len)
# len = (data_len[3] << 24) + (data_len[2] << 16) + (data_len[1] << 8) + data_len[0]
# print ('data len is:',len)
