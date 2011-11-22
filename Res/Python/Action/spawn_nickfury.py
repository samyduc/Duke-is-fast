from kernel import *
from wgraphic import *
from winput import *
from utils import *

graphic = wgraphic.getInstance()
input = winput.getInstance()

id = kernel.uniqueID()
kernel.addEntity(id, "nickfury")
mouse_pos = input.getMousePosition()
graphic.setPosition(id, mouse_pos)
graphic.setAction(id, "move")