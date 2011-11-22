from wgraphic import *
from wlogic import *
from utils import *

def collide():
	return False
	
def update():
	logic = wlogic.getInstance()
	graphic = wgraphic.getInstance()

	id = logic.getWorkingID()
	
	graphic.setView(id)
	
	return True