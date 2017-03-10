class File:
    
    def __init__(self, path = "", filename = "input"):
        self.filepath = path
        self.filename = filename
    
    def readAll(self):
        lines = []
        with open(self.filepath + self.filename, "r") as f:
            for line in f:
                lines.append(line)
        lines = reversed(lines)
        return lines
        
    def writeLine(self, lines): #expects list of string
        with open(self.filepath + self.filename, "w") as f:
            f.writelines(lines)
        
    def textToMatrix(self):
        content = self.readAll() #list of string
        matrix = []
        for line in content:
            line = line.strip()
            row = line.split(" ")
            row = map(int, row)
            matrix.append(row)
        return matrix
        