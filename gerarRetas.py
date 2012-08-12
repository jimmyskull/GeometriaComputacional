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
		p1 = (a(), a())
		p2 = (a(), a())
		if p1 > p2:
			p2, p1 = p1, p2
		for p in p1 + p2:
			print p,
		print
		retas += [p1 + p2]

on_key_press(0, 0)
try:
	pyglet.app.run()
except:
	pass

print 0

