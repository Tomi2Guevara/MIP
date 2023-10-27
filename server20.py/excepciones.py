#defino mis propias excepciones

class ErrorConexion(Exception):
    """Raised when the robot is not connected"""
    def __init__(self, message="ERROR: el robot no esta conectado"):
        self.message = message
        super().__init__(self.message)
    
    def __str__(self):
        return f'{self.message}'
    pass

class ModoInvalido(Exception):
    """Raised when the mode is automatic"""
    def __init__(self, message="ERROR: el robot esta en modo automatico"):
        self.message = message
        super().__init__(self.message)
    def __str__(self):
        return f'{self.message}'
    pass

class ErrorMotores(Exception):
    """Raised when the motors are disabled"""
    #esta excepcion se levanta cuando se intenta realizar un movimiento con los motores desactivados
    #podemos definin un mensaje de error personalizado
    def __init__(self, message="ERROR: los motores estan desactivados"):
        self.message = message
        super().__init__(self.message)
    #esto es para que se muestre el mensaje de error personalizado
    def __str__(self):
        return f'{self.message}'
    pass

class LimitVelLin(Exception):
    """Raised when the linear speed is out of range"""
    def __init__(self, message="ERROR: la velocidad lineal esta fuera de rango, v<50 mm/s"):
        self.message = message
        super().__init__(self.message)
    def __str__(self):
        return f'{self.message}'
    pass

class ErrorWorkSpace(Exception):
    """Raised when the workspace is not defined"""
    def __init__(self, message="ERROR: punto fuera del espacio de trabajo"):
        self.message = message
        super().__init__(self.message)
    def __str__(self):
        return f'{self.message}'
    pass