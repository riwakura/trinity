import math
import sys
import numpy as np

PI = math.acos(-1)

class XY:
    def __init__(self, _mass, _x, _y, _z, _vx, _vy, _vz):
        self.mass = _mass
        self.x = _x
        self.y = _y
        self.z = _z
        self.vx = _vx
        self.vy = _vy
        self.vz = _vz

class Prograde:
    def __init__(self,_time,_semiin,_semiout,_eccin,_eccout,_rot_horin,_rot_horout,_omgin,_omgout):
        self.time = _time
        self.semiin = _semiin
        self.semiout = _semiout
        self.eccin = _eccin
        self.eccout = _eccout
        self.rot_horin = _rot_horin
        self.rot_horout = _rot_horout
        self.omgin = _omgin
        self.omgout = _omgout
    
    def semiratio(self):
        return self.semiin / self.semiout
    
    def q(self):
        return self.semiout(1-self.eccout) / self.semiin
    
    def netomgin(self):
        if math.cos(self.rot_horin + self.omgin) > 0:
            return math.atan2(self.rot_horin+self.omgin , 1)
        if math.cos(self.rot_horin + self.omgin) < 0:
            return math.atan2(self.rot_horin+self.omgin , -1)

    def netomgout(self):
        if math.cos(self.Omgout + self.omgout) > 0:
            return math.atan2(self.Omgout+self.omgout, 1)
        if math.cos(self.Omgout + self.omgout) < 0:
            return math.atan2(self.Omgout+self.omgout ,-1)
        
    def omgdiff(self):
        if Prograde.netomgin - Prograde.netomgout > 0:
            return Prograde.netomgin - Prograde.netomgout
        if Prograde.netomgin - Prograde.netomgout < 0:
            return Prograde.netomgin - Prograde.netomgout + 2*PI
        
class Retrograde:
    def __init__(self,_time,_semiin,_semiout,_eccin,_eccout,_rot_horin,_rot_horout,_omgin,_omgout):
        self.time = _time
        self.semiin = _semiin
        self.semiout = _semiout
        self.eccin = _eccin
        self.eccout = _eccout
        self.rot_horin = _rot_horin
        self.rot_horout = _rot_horout
        self.omgin = _omgin
        self.omgout = _omgout
    
    def semiratio(self):
        return self.semiin / self.semiout
    
    def q(self):
        return self.semiout(1-self.eccout) / self.semiin
    
    def netomgin(self):
        if math.cos(self.Omgin - self.omgin) > 0:
            return math.atan2(self.rot_horout-self.omgin , 1)
        if math.cos(self.Omgin - self.omgin) < 0:
            return math.atan2(self.rot_horout-self.omgin , -1)

    def netomgout(self):
        if math.cos(self.rot_horout - self.omgout) > 0:
            return math.atan2(self.rot_horout-self.omgout, 1)
        if math.cos(self.rot_horout - self.omgout) < 0:
            return math.atan2(self.rot_horout-self.omgout ,-1)
        
    def omgdiff(self):
        if Prograde.netomgin - Prograde.netomgout > 0:
            return Prograde.netomgin - Prograde.netomgout
        if Prograde.netomgin - Prograde.netomgout < 0:
            return Prograde.netomgin - Prograde.netomgout + 2*PI