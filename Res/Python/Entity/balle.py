from wgraphic import *
from wlogic import *
from utils import *


def collide():
	#graphic = wgraphic.getInstance()
	return False
	
def update():
	graphic = wgraphic.getInstance()
	logic = wlogic.getInstance()
	id = logic.getWorkingID()
	
	#move = logic.getLastMove(id)
	
	#graphic.setMove(id, logic.getLastMove(id))
	
	return True