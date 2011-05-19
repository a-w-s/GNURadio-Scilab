#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Thu May 12 22:09:09 2011
##################################################

from gnuradio import gr
from gnuradio.eng_option import eng_option
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import slab
import wx

class top_block(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="Top Block")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 32000

		##################################################
		# Blocks
		##################################################
		self.gr_null_sink_0 = gr.null_sink(gr.sizeof_float*1)
		self.slab_sbhs_scilab_0 = slab.sbhs_scilab()

		##################################################
		# Connections
		##################################################
		self.connect((self.slab_sbhs_scilab_0, 0), (self.gr_null_sink_0, 0))

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = top_block()
	tb.Run(True)

