# Example on how to monitor the pose of an object with Attribute (name, <objectValue>)
# In this example the pose is relative to the root node.
# 
# The examples use the JSON API that sends a messages via ZMQ to the SHERPA WM.  

import zmq
import sys
import time
import datetime
import json

### Variables ###

objectAttribute = "name"
objectValue = "rescuer"

### Communication Setup ###

# Set up the ZMQ REQ-REP communication layer for queries.
context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:22422")

### Query to get Ids of object and reference frame ####

# Get root node Id as reference
getRootNodeMsg = {
  "@worldmodeltype": "RSGQuery",
  "query": "GET_ROOT_NODE"
}

print("Sending query for root node Id: %s " % json.dumps(getRootNodeMsg))
socket.send_string(json.dumps(getRootNodeMsg))
result = socket.recv()
print("Received reply for root node Id: %s " % result)

msg = json.loads(result.decode('utf8'))
rootId = msg["rootId"]
print("rootId = %s " % rootId)
referenceId = rootId


# Get object Id 
getNodes = {
  "@worldmodeltype": "RSGQuery",
  "query": "GET_NODES",
  "attributes": [
    {"key": objectAttribute, "value": objectValue },
  ]
}

print("Sending query for object node Id(s): %s " % json.dumps(getNodes))
socket.send_string(json.dumps(getNodes))
result = socket.recv()
print("Received reply for object node Id(s): %s " % result)

msg = json.loads(result.decode('utf8'))
ids = msg["ids"]
print("ids = %s " % ids)



### Poll for updates. ###


# Of course we want to get the _latest_ information.
currentTimeStamp = datetime.datetime.now().strftime('%Y-%m-%dT%H:%M:%S')


