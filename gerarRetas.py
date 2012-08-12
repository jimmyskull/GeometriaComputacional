#!/usr/bin/python2
# Autor: Paulo Roberto Urio
# Data: 08/08/2012
import pyglet
from random import randint

window = pyglet.window.Window(resizable=True)
retas = []

@window.event
def on_draw():
	window.clear()
	pyglet.gl.glColor4f(1.0,0,0,1.0)
	for r in retas:
		pyglet.graphics.draw(2, pyglet.gl.GL_LINES, ('v2i', (r)))
		
@window.event
def on_key_press(symbol, modifiers):
	global retas
	retas = []
	a = lambda: randint(15, 600)
	c = randint(3, 20)
	print c
	for i in range(c):
		_r = (a(), a(), a(), a())
		for p in _r:
			print p,
		print
		retas += [_r]

on_key_press(0, 0)
try:
	pyglet.app.run()
except:
	pass
