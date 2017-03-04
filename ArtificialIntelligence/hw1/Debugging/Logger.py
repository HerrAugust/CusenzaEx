class Logger:
    file = 'log.txt'
    def writeLine(self, what):
        f = open(file, "w")
        what = what + "\n"
        f.write(what)
        f.close()

    def delete(self):
        pass