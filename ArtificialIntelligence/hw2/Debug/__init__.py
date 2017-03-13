import subprocess


class Debug:
    def __init__(self, filename = "log.txt", path = subprocess.check_output(['xdg-user-dir', 'DESKTOP'])):
        self.filename = filename
        self.path = path

    def write(self, lines):
        f = open(self.path + "/" + self.filename, "w")
        f.writelines(lines)
        f.close()

    def readall(self):
        f = open(self.path + "/" + self.filename, "r")
        data = f.readlines()
        return data