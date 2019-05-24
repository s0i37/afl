#!/usr/bin/python2
import pydot
from sys import argv
from magic import Magic

if len(argv) != 2:
	print "%s out/plot_data" % argv[0]
	exit()

graph = pydot.Dot(graph_type='digraph')
magic = Magic()
found = set()
last_case = 0
last_crashes = 0
last_hangs = 0
with open(argv[1]) as f:
	for line in f:
		if line.startswith('#'):
			continue
		testcase = int( line.split(', ')[2] )
		newcase = int( line.split(', ')[3] )
		crashes = int( line.split(', ')[7] )
		hangs = int( line.split(', ')[8] )
		filetype = magic.id_filename('queue/id_%06d'%testcase)
		graph.add_node( pydot.Node(testcase, label='%d (%s)'%(testcase,filetype)) )
		if crashes > last_crashes:
			graph.add_node( pydot.Node("crash_%d"%crashes, style="filled", fillcolor='#ff0000' ) )
			graph.add_edge( pydot.Edge(testcase, "crash_%d"%crashes) )
		if hangs > last_hangs:
			graph.add_node( pydot.Node("hang_%d"%hangs, style="filled", fillcolor='#777777' ) )
			graph.add_edge( pydot.Edge(testcase, "hang_%d"%hangs) )
		if not last_case:
			last_case = newcase
		for case in xrange(last_case, newcase):
			if not case in found:
				found.add(case)
				graph.add_edge( pydot.Edge(testcase, case) )
		last_case = newcase
		last_crashes = crashes
		last_hangs = hangs

graph.write_dot('plot_data.dot')
print 'xdot plot_data.dot'
