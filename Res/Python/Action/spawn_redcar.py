from kernel import *
from wgraphic import *
from wlogic import *
from winput import *
from utils import *

graphic = wgraphic.getInstance()
input = winput.getInstance()
logic = wlogic.getInstance()

id = kernel.uniqueID()
kernel.addEntity(id, "redcar")
mouse_pos = input.getMousePosition()
graphic.setPosition(id, mouse_pos)

logic.setWorkingID(id)