import libdemo
from ctypes import *
import numpy as np

class BaseEoS:

    def __init__(self, ident, ncomps, Tc, Vc):
        self.ident = ident
        self.ncomps = ncomps
        self.Tc = Tc
        self.Vc = Vc

        self.lib = None

    def pressure(self, T, V, n):
        p = np.array([0], dtype=np.float32)
        self.lib.pressure(T, V, n, p)
        return p[0]

    def Fideal(self, T, V, n, Ft=False, Fv=False, Fn=False):
        return None

class NotIdGas(BaseEoS):

    def __init__(self, ident, ncomps, Tc, Vc):
        super().__init__(ident, ncomps, Tc, Vc)
        self.lib = libdemo.NotIdGas(ident, ncomps, Tc, Vc)