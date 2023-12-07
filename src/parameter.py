import math
import sys
import numpy as np

PI = math.acos(-1)

class Prograde:
    def __init__(self,time,semiin,semiout,eccin,eccout,Omgin,Omgout,omgin,omgout):
        self.time = time
        self.semiin = semiin
        self.semiout = semiout
        self.eccin = eccin
        self.eccout = eccout
        self.Omgin = Omgin
        self.Omgout = Omgout
        self.omgin = omgin
        self.omgout = omgout
    
    def semiratio(self):
        return self.semiin / self.semiout
    
    def q(self):
        return self.semiout(1-self.eccout) / self.semiin
    
    def netomgin(self):
        if math.cos(self.Omgin + self.omgin) > 0:
            return math.atan2(self.Omgin+self.omgin , 1)
        if math.cos(self.Omgin + self.omgin) < 0:
            return math.atan2(self.Omgin+self.omgin , -1)

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
    def __init__(self,time,semiin,semiout,eccin,eccout,Omgin,Omgout,omgin,omgout):
        self.time = time
        self.semiin = semiin
        self.semiout = semiout
        self.eccin = eccin
        self.eccout = eccout
        self.Omgin = Omgin
        self.Omgout = Omgout
        self.omgin = omgin
        self.omgout = omgout
    
    def semiratio(self):
        return self.semiin / self.semiout
    
    def q(self):
        return self.semiout(1-self.eccout) / self.semiin
    
    def netomgin(self):
        if math.cos(self.Omgin - self.omgin) > 0:
            return math.atan2(self.Omgin-self.omgin , 1)
        if math.cos(self.Omgin - self.omgin) < 0:
            return math.atan2(self.Omgin-self.omgin , -1)

    def netomgout(self):
        if math.cos(self.Omgout - self.omgout) > 0:
            return math.atan2(self.Omgout-self.omgout, 1)
        if math.cos(self.Omgout - self.omgout) < 0:
            return math.atan2(self.Omgout-self.omgout ,-1)
        
    def omgdiff(self):
        if Prograde.netomgin - Prograde.netomgout > 0:
            return Prograde.netomgin - Prograde.netomgout
        if Prograde.netomgin - Prograde.netomgout < 0:
            return Prograde.netomgin - Prograde.netomgout + 2*PI