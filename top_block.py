#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Sun Jul  3 02:46:48 2016
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import fosphor
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import math
import numpy
import sip
import sys


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.variable_constellation_0_1 = variable_constellation_0_1 = digital.constellation_calcdist(([1+0j,0.707+0.707j, -0.707+0.707j, 0+1j, 0.707-0.707j, 0-1j, -1+0j, -0.707-0.707j]), ([0, 1, 2, 3, 4, 5, 6, 7]), 4, 1).base()
        self.variable_constellation_0_0 = variable_constellation_0_0 = digital.constellation_calcdist(([0.707+0.707j, -0.707-0.707j]), ([0, 1]), 4, 1).base()
        self.variable_constellation_0 = variable_constellation_0 = digital.constellation_calcdist(([0.707+0.707j, -0.707+0.707j, -0.707-0.707j, 0.707-0.707j]), ([0, 1, 2, 3]), 4, 1).base()
        self.samp_rate = samp_rate = 10000
        self.EbN0 = EbN0 = 10

        ##################################################
        # Blocks
        ##################################################
        self.root_raised_cosine_filter_0_0 = filter.fir_filter_ccf(4, firdes.root_raised_cosine(
        	1, samp_rate, samp_rate/4, 0.35, 10*4))
        self.root_raised_cosine_filter_0 = filter.interp_fir_filter_ccf(4, firdes.root_raised_cosine(
        	1, samp_rate, samp_rate/4, 0.35, 10*4))
        self.qtgui_time_sink_x_1_0_0_1_0_0 = qtgui.time_sink_f(
        	24*2, #size
        	samp_rate/10, #samp_rate
        	"Tx Bits", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_1_0_0_1_0_0.set_update_time(.10)
        self.qtgui_time_sink_x_1_0_0_1_0_0.set_y_axis(-1, 1)
        
        self.qtgui_time_sink_x_1_0_0_1_0_0.set_y_label("Amplitude", "")
        
        self.qtgui_time_sink_x_1_0_0_1_0_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_1_0_0_1_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1_0_0_1_0_0.enable_autoscale(True)
        self.qtgui_time_sink_x_1_0_0_1_0_0.enable_grid(False)
        self.qtgui_time_sink_x_1_0_0_1_0_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_1_0_0_1_0_0.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1_0_0_1_0_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_1_0_0_1_0_0_win = sip.wrapinstance(self.qtgui_time_sink_x_1_0_0_1_0_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_1_0_0_1_0_0_win)
        self.qtgui_time_sink_x_1_0_0_1_0 = qtgui.time_sink_f(
        	24*2, #size
        	samp_rate/10, #samp_rate
        	"RX bits", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_1_0_0_1_0.set_update_time(.10)
        self.qtgui_time_sink_x_1_0_0_1_0.set_y_axis(-1, 1)
        
        self.qtgui_time_sink_x_1_0_0_1_0.set_y_label("Amplitude", "")
        
        self.qtgui_time_sink_x_1_0_0_1_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_1_0_0_1_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1_0_0_1_0.enable_autoscale(True)
        self.qtgui_time_sink_x_1_0_0_1_0.enable_grid(False)
        self.qtgui_time_sink_x_1_0_0_1_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_1_0_0_1_0.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1_0_0_1_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1_0_0_1_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1_0_0_1_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1_0_0_1_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1_0_0_1_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1_0_0_1_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1_0_0_1_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_1_0_0_1_0_win = sip.wrapinstance(self.qtgui_time_sink_x_1_0_0_1_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_1_0_0_1_0_win)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title("")
        
        labels = ["BER", "", "", "", "",
                  "", "", "", "", ""]
        units = ["x10^-4", "", "", "", "",
                 "", "", "", "", ""]
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
                  ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1e4, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        for i in xrange(1):
            self.qtgui_number_sink_0.set_min(i, 0)
            self.qtgui_number_sink_0.set_max(i, 10)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])
        
        self.qtgui_number_sink_0.enable_autoscale(True)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_number_sink_0_win)
        self.qtgui_const_sink_x_2 = qtgui.const_sink_c(
        	1024, #size
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_const_sink_x_2.set_update_time(0.10)
        self.qtgui_const_sink_x_2.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_2.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_2.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_2.enable_autoscale(True)
        self.qtgui_const_sink_x_2.enable_grid(False)
        
        if not True:
          self.qtgui_const_sink_x_2.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
                  "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_2.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_2.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_2.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_2.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_2.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_2.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_2.set_line_alpha(i, alphas[i])
        
        self._qtgui_const_sink_x_2_win = sip.wrapinstance(self.qtgui_const_sink_x_2.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_const_sink_x_2_win)
        self.fosphor_qt_sink_c_0 = fosphor.qt_sink_c()
        self.fosphor_qt_sink_c_0.set_fft_window(window.WIN_BLACKMAN_hARRIS)
        self.fosphor_qt_sink_c_0.set_frequency_range(0, samp_rate)
        self._fosphor_qt_sink_c_0_win = sip.wrapinstance(self.fosphor_qt_sink_c_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._fosphor_qt_sink_c_0_win)
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(variable_constellation_0_1)
        self.digital_chunks_to_symbols_xx_0_0 = digital.chunks_to_symbols_bc(([1+0j,0.707+0.707j, -0.707+0.707j, 0+1j, 0.707-0.707j, 0-1j, -1+0j, -0.707-0.707j]), 1)
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(3)
        self.blocks_pack_k_bits_bb_0 = blocks.pack_k_bits_bb(3)
        self.blocks_delay_1 = blocks.delay(gr.sizeof_char*1, 30)
        self.blocks_char_to_float_0_0 = blocks.char_to_float(1, 1)
        self.blocks_char_to_float_0 = blocks.char_to_float(1, 1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.blks2_error_rate_0 = grc_blks2.error_rate(
        	type='SER',
        	win_size=100000,
        	bits_per_symbol=2,
        )
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, 10000)), True)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, 1.0 / math.sqrt(2*2.0 * digital.constellation_8psk().bits_per_symbol() * 10**(EbN0/10)), 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0, 0))    
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_delay_1, 0))    
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_pack_k_bits_bb_0, 0))    
        self.connect((self.blks2_error_rate_0, 0), (self.qtgui_number_sink_0, 0))    
        self.connect((self.blocks_add_xx_0, 0), (self.root_raised_cosine_filter_0_0, 0))    
        self.connect((self.blocks_char_to_float_0, 0), (self.qtgui_time_sink_x_1_0_0_1_0, 0))    
        self.connect((self.blocks_char_to_float_0_0, 0), (self.qtgui_time_sink_x_1_0_0_1_0_0, 0))    
        self.connect((self.blocks_delay_1, 0), (self.blks2_error_rate_0, 0))    
        self.connect((self.blocks_delay_1, 0), (self.blocks_char_to_float_0_0, 0))    
        self.connect((self.blocks_pack_k_bits_bb_0, 0), (self.digital_chunks_to_symbols_xx_0_0, 0))    
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.blks2_error_rate_0, 1))    
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.blocks_char_to_float_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0_0, 0), (self.root_raised_cosine_filter_0, 0))    
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))    
        self.connect((self.root_raised_cosine_filter_0, 0), (self.blocks_add_xx_0, 1))    
        self.connect((self.root_raised_cosine_filter_0, 0), (self.fosphor_qt_sink_c_0, 0))    
        self.connect((self.root_raised_cosine_filter_0_0, 0), (self.digital_constellation_decoder_cb_0, 0))    
        self.connect((self.root_raised_cosine_filter_0_0, 0), (self.qtgui_const_sink_x_2, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()


    def get_variable_constellation_0_1(self):
        return self.variable_constellation_0_1

    def set_variable_constellation_0_1(self, variable_constellation_0_1):
        self.variable_constellation_0_1 = variable_constellation_0_1

    def get_variable_constellation_0_0(self):
        return self.variable_constellation_0_0

    def set_variable_constellation_0_0(self, variable_constellation_0_0):
        self.variable_constellation_0_0 = variable_constellation_0_0

    def get_variable_constellation_0(self):
        return self.variable_constellation_0

    def set_variable_constellation_0(self, variable_constellation_0):
        self.variable_constellation_0 = variable_constellation_0

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_1_0_0_1_0.set_samp_rate(self.samp_rate/10)
        self.qtgui_time_sink_x_1_0_0_1_0_0.set_samp_rate(self.samp_rate/10)
        self.root_raised_cosine_filter_0_0.set_taps(firdes.root_raised_cosine(1, self.samp_rate, self.samp_rate/4, 0.35, 10*4))
        self.fosphor_qt_sink_c_0.set_frequency_range(0, self.samp_rate)
        self.root_raised_cosine_filter_0.set_taps(firdes.root_raised_cosine(1, self.samp_rate, self.samp_rate/4, 0.35, 10*4))

    def get_EbN0(self):
        return self.EbN0

    def set_EbN0(self, EbN0):
        self.EbN0 = EbN0
        self.analog_noise_source_x_0.set_amplitude(1.0 / math.sqrt(2*2.0 * digital.constellation_8psk().bits_per_symbol() * 10**(self.EbN0/10)))


def main(top_block_cls=top_block, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
