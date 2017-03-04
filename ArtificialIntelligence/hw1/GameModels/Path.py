#represents a single-child tree
#Usage: p = Path()
#       p.addChild("c1")
#       p.addChild("c2")
#       p.removeChild()
#       print p
#       for e in p.getChildren():
#           print e
class Path:
    def __init__(self):
        self.children = []

    def pop(self):
        del self.children[len(self.children)-1]

    def push(self, what):
        self.children.append(what)

    def getChildren(self):
        return self.children
