from wgraphic import *
from wlogic import *
from utils import *

def collide_single(entity):
	graphic = wgraphic.getInstance()
	logic = wlogic.getInstance()
	id = entity.getID()
	point = logic.getLastMove(graphic.getWorkingID())
	point2 = graphic.getPosition(id)
	entity.setMove(point)

def collide():
	graphic = wgraphic.getInstance()
	id = graphic.getWorkingID()

	while(True):
		collision = graphic.getCollisionList()
		if(collision == None):
			break
		else:
			collide_single(collision)
	return False
	
def update():
	return True