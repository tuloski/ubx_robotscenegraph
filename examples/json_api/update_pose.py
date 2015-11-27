# Example on how to update an existing pose.
# 
# The examples use the JSON API that sends a messages via
# ZMQ to the SHERPA WM.  

import zmq
import random
import sys
import time
import json

# The port is defined by the system composition (sherpa_world_model.usc) file
# via the ``local_json_in_port`` variable. 
# e.g.
# local local_json_in_port = "12911"  
port = "12911" 
if len(sys.argv) > 1:
    port =  sys.argv[1]
    int(port)

# Set up the ZMQ PUB-SUB communication layer.
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:%s" % port)

# JSON message to update an existing Transform. Note that the Transform
# (and thus the id)  must
# exist beforehands, otherwise this operation does not succeed.
# in this case the "id": "3304e4a0-44d4-4fc8-8834-b0b03b418d5b"
# denotes the Transform that is cereaten in the add_pose.py example.
transforUpdateMsg = {
  "@worldmodeltype": "RSGUpdate",
  "operation": "UPDATE_TRANSFORM",
  "node": {    
    "@graphtype": "Connection",
    "@semanticContext":"Transform",
    "id": "3304e4a0-44d4-4fc8-8834-b0b03b418d5b",
    "history" : [
      {
        "stamp": {
          "@stamptype": "TimeStampDate",
          "stamp": "2015-07-01T16:35:87Z",
        },
        "transform": {
          "type": "HomogeneousMatrix44",
          "matrix": [
            [1,0,0,34.97],
            [0,1,0,39.23],
            [0,0,1,0.0999],
            [0,0,0,1] 
          ],
          "unit": "m"
        }
      }
    ], 	    
  }
}

# Send message.
time.sleep(1)
print (json.dumps(transforUpdateMsg))
socket.send_string(json.dumps(transforUpdateMsg))  
time.sleep(1) 

