"""
cviko 10
objekty a struktury
"""


class Circle(object):
    
    def __init__(self, size, position):
        self.size = size
        self.position = position


    def changeposition(self, position):
        self.position = position


    def changesize(self, size):
        self.size = size
