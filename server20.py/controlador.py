from serial_port import SerialPort
import time
import sys
from excepciones import ErrorConexion, ModoInvalido, ErrorMotores, LimitVelLin, ErrorWorkSpace

class Controlador:
    def __init__(self):
        self.efectorFinal = "Gripper"
        self.dimensiones = None
        self.velLinMax= 50 #mm/s
        self.estadoConexion = False
        self.estadoMotores = False
        self.estadoEfector = False
        self.modoTrabajo = "Manual"
        self.posEfector = {"X":0.00,"Y":170.00,"Z":120.00}
        self.horaConexion = None
        self.fechaConexion = None
        self.grabarTrayectoria = False
        self.record = ""


    def getEstadoConexion(self):
        if self.estadoConexion == True:
            return "Activa"
        else:
            return "Inactiva"
    def getEstadoMotores(self):
        if self.estadoMotores == True:
            return "Activados"
        else:
            return "Desactivados"
    def getPosEfector(self):
        return "X: " + str(self.posEfector["X"]) + " Y: " + str(self.posEfector["Y"]) + " Z: " + str(self.posEfector["Z"])
    def getHoraConexion(self):
        return self.horaConexion
    def getFechaConexion(self):
        return self.fechaConexion
    def getModo(self):
        return self.modoTrabajo


#defino valores por defecto para el puerto y el baudrate por si no se los paso
    def conectar(self, port="/dev/cu.usbmodem1101", baudrate=115200):
        try:
            if self.estadoConexion == True:
                raise ErrorConexion
            else:
                self.serial = SerialPort(port, baudrate)
                time.sleep(2)
                respuesta=self.serial.read(1)
                respuesta+="INFO: conexion exitosa\n"
        except ErrorConexion as e:
            return "ERROR: el robot ya esta conectado"
        except:
            return ("ERROR: no se pudo conectar el robot")
        else:
            self.estadoConexion = True
            self.horaConexion = time.strftime("%H:%M:%S")
            self.fechaConexion = time.strftime("%d/%m/%y")
            respuesta+="INFO: Robot conectado en el puerto "+ port
            return respuesta

    def desconectar(self):
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            else:
                self.serial.close()
        except ErrorConexion as e:
            return "ERROR: el robot ya esta desconectado"
        except:
            return ("ERROR: no se pudo desconectar el robot")
        else:
            self.estadoConexion = False
            return ("INFO: robot desconectado")

    def cambiarModo(self, modo):

        if modo == "auto":
            self.modoTrabajo = "Automatico"
            return ("INFO: modo automatico activado")
        elif modo == "manual":
            self.modoTrabajo = "Manual"
            return ("INFO: modo manual activado")
        else:
            return ("ERROR: modo invalido")

    def activarMotores(self):
        #debo verificar que el robot este conectado
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            else:
                self.serial.write("M17")
                respuesta=self.serial.read()
        except ErrorConexion:
            return ("ERROR: no se puede activar los motores, el robot no esta conectado")
        except:
            return ("ERROR: no se pudo activar los motores")
        else:
            self.estadoMotores = True
            return ("INFO: MOTORS ENABLED")
            #return respuesta

    def desactivarMotores(self):
        #debo verificar que el robot este conectado
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            else:
                self.serial.write("M18")
                respuesta=self.serial.read()
        except ErrorConexion as e:
            return str(e)
        except:
            return ("ERROR: no se pudo desactivar los motores")
        else:
            self.estadoMotores = False
            return ("INFO: MOTORS DISABLED")
            #return respuesta

    def homing(self):
        #verifico que el robot este conectado y en modo manual
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Automatico":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            else:
                if self.grabarTrayectoria: self.record += "G28"
                self.serial.write("G28")
                self.posEfector = {"X":0.00,"Y":170.00,"Z":120.00}
                respuesta=self.serial.read()
                #Elimino los ulimos dos caracteres que son caracteres \n
                respuesta = respuesta[:-2]

        except ErrorConexion as e:
            return str(e)
        except ModoInvalido as e:
            return str(e)
        except ErrorMotores as e:
            return str(e)
        else:
            return respuesta


    def getCurrentPosition(self):
        #verifico que el robot este conectado
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            else:
                self.serial.write("M114")
                respuesta=self.serial.read()
                #despues de INFO:  hay dos espacios en blanco dejo uno solo
                respuesta = respuesta.replace("INFO:  ","INFO: ")
        except ErrorConexion as e:
            return str(e)
        except:
            return ("ERROR: no se pudo obtener la posición actual")
        else:
            return respuesta
            #return str(self.posEfector)


    def movimientoLineal(self, posFinal, vel=20):
        #verifico que el robot este conectado, en modo manual, con los motores activados y que la velocidad este dentro del rango
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Automatico":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            elif vel > self.velLinMax:
                raise LimitVelLin
            else:
                comando="G0X" + str(posFinal[0]) + "Y" + str(posFinal[1]) + "Z" + str(posFinal[2]) + "-F" + str(vel)
                self.serial.write(comando)
                respuesta=self.serial.read()
                #verifico si está dentro del espacio de trabajo
                if "ERROR" in respuesta:
                    raise ErrorWorkSpace
                else:
                    self.posEfector = {"X":posFinal[0],"Y":posFinal[1],"Z":posFinal[2]}
                    if self.grabarTrayectoria: self.record += comando

                #respuesta = "INFO: movimiento lineal realizado con exito\nINFO: CURRENT POSITION: " + str(self.posEfector)
        except LimitVelLin as e:
                    return str(e)
        except ErrorConexion as e:
            return str(e)
        except ModoInvalido as e:
            return str(e)
        except ErrorMotores as e:
            return str(e)
        except ErrorWorkSpace as e:
            return str(e)
        #except:
         #   return ("ERROR: no se pudo realizar el movimiento lineal")
        else:
            return respuesta


    '''def movimientoLineal(self,posFinal):
        #verificaciones
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Automatico":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            else:
                self.serial.write("G0X" + str(posFinal[0]) + "Y" + str(posFinal[1]) + "Z" + str(posFinal[2]))
                self.posEfector = {"x":posFinal[0],"y":posFinal[1],"z":posFinal[2]}
                #respuesta=self.serial.read() hay un caracter mal
                respuesta = "INFO: movimiento lineal realizado con éxito\nINFO: CURRENT POSITION: " + str(self.posEfector)
        except ErrorConexion as e:
            return e
        except ModoInvalido as e:
            return e
        except ErrorMotores as e:
            return e
        except:
            return ("ERROR: no se pudo realizar el movimiento lineal")
        else:
            return respuesta'''


    #para el efector hacemos algo similar a los motores
    def activarEfector(self):
        #verifico que el robot este conectado, en modo manual y con los motores activados
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Automatico":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            else:
                if self.grabarTrayectoria: self.record += "M3"
                self.serial.write("M3")
                respuesta=self.serial.read()
                self.estadoEfector = True
        except ErrorConexion as e:
            return str(e)
        except ModoInvalido as e:
            return str(e)
        except ErrorMotores as e:
            return str(e)
        except:
            return ("ERROR: no se pudo activar el efector")
        else:
            return respuesta

    def desactivarEfector(self):
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Automatico":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            else:
                if self.grabarTrayectoria: self.record += "M5"
                self.serial.write("M5")
                respuesta=self.serial.read()
                self.estadoEfector = False
        except ErrorConexion as e:
            return str(e)
        except ModoInvalido as e:
            return str(e)
        except ErrorMotores as e:
            return str(e)
        except:
            return ("ERROR: no se pudo desactivar el efector")
        else:
            return respuesta

    def aprenderTrayectoria(self, flag, fileName):
        #verificaciones
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            else:
                if flag:
                    self.grabarTrayectoria = True
                    self.record = ""
                    return ("INFO: se esta grabando la trayectoria")
                else:
                    self.grabarTrayectoria = False
                    #creo un archivo y guardor la trayectoria en el directorio trayectorias
                    archivo = open("./trayectorias/"+fileName+".txt", "w")
                    archivo.write(self.record)
                    archivo.close()
                    self.record = ""
                    return ("INFO: trayectoria guardada con exito")

        except ErrorConexion as e:
            return str(e)
        except:
            return ("ERROR: no se pudo grabar la trayectoria")


# Vamos a hacer una funcion para separar G28G0X25.0Y54.0Z56.0-F20M3 en G28, G0X25.0Y54.0Z56.0-F20, M3 es decir separamos cunado es una letra mayuscula G o M

    def ejecutarTrayectoria(self, fileName):
        #verificaciones
        try:
            if self.estadoConexion == False:
                raise ErrorConexion
            elif self.modoTrabajo == "Manual":
                raise ModoInvalido
            elif self.estadoMotores == False:
                raise ErrorMotores
            else:
                archivo = open(fileName, "r")
                trayectoria = archivo.read()
                archivo.close()
                #separamos la trayectoria
                trayectoria = self.separarTrayectoria(trayectoria)
                #print(trayectoria)
                #ejecutamos la trayectoria
                respuesta=""
                for comando in trayectoria:
                    self.serial.write(comando)
                    try:
                        respuesta+= self.serial.read()
                    except:
                        print("caracter raro")
                respuesta += "INFO: trayectoria ejecutada con exito"
                return respuesta

        except ErrorConexion as e:
            return str(e)
        except ModoInvalido as e:
            return "ERROR: pasar a modo automatico para ejecutar trayectorias"
        except ErrorMotores as e:
            return str(e)
        except:
            return ("ERROR: no se pudo ejecutar la trayectoria")

#funcion aparte para separar la trayectoria en comandos GCode
    def separarTrayectoria(self, trayectoria):
        trayectoriaSeparada = []
        comando = ""
        for caracter in trayectoria:
            if caracter.isupper() and (caracter == "G" or caracter == "M"):
                trayectoriaSeparada.append(comando)
                comando = caracter
            else:
                comando += caracter
        trayectoriaSeparada.append(comando)
        #elimino el primer elemento que es vacio
        trayectoriaSeparada.pop(0)
        return trayectoriaSeparada




















