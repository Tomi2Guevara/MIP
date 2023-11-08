from pathlib import Path
from tkinter import Tk, Canvas, Entry, Text, Button, PhotoImage
import time
import sys

OUTPUT_PATH = Path(__file__).parent
# debo cambiar el path según dónde se encuentren los assets
ASSETS_PATH = OUTPUT_PATH / Path(r"/Users/martinarobyculasso/Desktop/build_gui/assets/frame0")


def relative_to_assets(path: str) -> Path:
    return ASSETS_PATH / Path(path)


# Función para mandar mensajes al programa C++
def send_message_to_cpp(message):
    pipe_path = "/Users/martinarobyculasso/Desktop/pipe/my_pipe"  # debo cambiar el path según dónde se va a abrir el pipe
    try:
        with open(pipe_path, "w") as pipe:
            pipe.write(message + "\n")
        print(f"Sent message to C++ program: {message}")
    except Exception as e:
        print(f"Error sending message to C++ program: {e}")


# Define a global variable to store the value of entry_2
entry_2_value = ""


# Function to set custom read-only text in entry_3
def set_custom_read_only_text(text):
    entry_3.config(state="normal")  # Set state to normal to allow modification
    entry_3.delete(1.0, "end")  # Clear existing content
    entry_3.insert("end", text)  # Insert new text
    entry_3.config(state="disabled")  # Set state back to disabled


# Function to update entry_2_value whenever entry_2 content changes
def update_entry_2_value(event):
    global entry_2_value
    entry_2_value = entry_2.get()


# Define your button click functions
def button_1_clicked():
    send_message_to_cpp("conectar")


def button_2_clicked():
    send_message_to_cpp("desconectar")


def button_3_clicked():
    send_message_to_cpp("homing")


def button_4_clicked():
    send_message_to_cpp("getPos")


def button_5_clicked():
    send_message_to_cpp("reporte")


def button_6_clicked():
    send_message_to_cpp("motores on")


def button_7_clicked():
    send_message_to_cpp("modo manual")


def button_8_clicked():
    send_message_to_cpp("modo auto")


def button_9_clicked():
    send_message_to_cpp("salir")
    sys.exit()


def button_11_clicked():
    # Send "movLineal" to C++
    send_message_to_cpp("movLineal")

    # Wait for 1 second (you can adjust the time as needed)
    time.sleep(1)

    # Get values from entry_1, entry_4, entry_5, entry_6
    values = [entry_1.get(), entry_4.get(), entry_5.get(), entry_6.get()]

    # Convert to integers and create a vector
    int_vector = [int(value) for value in values]

    # Convert the vector to a string
    message = ' '.join(map(str, int_vector))

    # Send the message to C++
    send_message_to_cpp(message)


def button_10_clicked():
    send_message_to_cpp("ejecutarTray")
    time.sleep(1)
    send_message_to_cpp(entry_2_value)


def button_12_clicked():
    global entry_2_value
    # Get the content of entry_2
    entry_2_content = entry_2.get()
    entry_2_value = entry_2_content
    print(f"entry_2_value has been updated to: {entry_2_value}")


def button_13_clicked():
    send_message_to_cpp("motores off")


def button_14_clicked():
    send_message_to_cpp("gripper on")


def button_15_clicked():
    send_message_to_cpp("gripper off")


def button_16_clicked():
    send_message_to_cpp("aprendizaje on")
    time.sleep(1)
    send_message_to_cpp(entry_2_value)


def button_17_clicked():
    send_message_to_cpp("aprendizaje off")


def validate_entry1_input(P):
    if P == "" or P.isdigit() and 0 <= int(P) <= 200:
        return True
    return False


def validate_entry4_input(P):
    if P == "" or P.isdigit() and 0 <= int(P) <= 200:
        return True
    return False


def validate_entry5_input(P):
    if P == "" or P.isdigit() and 0 <= int(P) <= 200:
        return True
    return False


def validate_entry6_input(P):
    if P == "" or P.isdigit() and 0 <= int(P) <= 50:
        return True
    return False


# Start
window = Tk()

window.geometry("1150x650")
window.configure(bg="#E5E5E5")

canvas = Canvas(
    window,
    bg="#E5E5E5",
    height=650,
    width=1150,
    bd=0,
    highlightthickness=0,
    relief="ridge"
)

canvas.place(x=0, y=0)
canvas.create_rectangle(
    0.0,
    0.0,
    1150.0,
    650.0,
    fill="#CCCBCB",
    outline="")

canvas.create_rectangle(
    65.0,
    62.0,
    267.0,
    262.0,
    fill="#8E8E8E",
    outline="")

canvas.create_text(
    93.0,
    27.0,
    anchor="nw",
    text="Conexión del Robot",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_rectangle(
    310.0,
    62.0,
    939.0,
    262.0,
    fill="#8E8E8E",
    outline="")

canvas.create_text(
    552.0,
    27.0,
    anchor="nw",
    text="Comandos On/Off",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

button_image_1 = PhotoImage(
    file=relative_to_assets("button_1.png"))
button_1 = Button(
    image=button_image_1,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_1_clicked(),
    relief="flat"
)
button_1.place(
    x=93.0,
    y=85.0,
    width=146.0,
    height=64.0
)

button_image_2 = PhotoImage(
    file=relative_to_assets("button_2.png"))
button_2 = Button(
    image=button_image_2,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_2_clicked(),
    relief="flat"
)
button_2.place(
    x=93.0,
    y=175.0,
    width=146.0,
    height=64.0
)

canvas.create_rectangle(
    64.0,
    335.0,
    266.0,
    623.0,
    fill="#8E8E8E",
    outline="")

canvas.create_rectangle(
    299.0,
    335.0,
    684.0,
    623.0,
    fill="#8E8E8E",
    outline="")

canvas.create_rectangle(
    717.0,
    335.0,
    1087.0,
    623.0,
    fill="#8E8E8E",
    outline="")

canvas.create_text(
    100.0,
    300.0,
    anchor="nw",
    text="Otros Comandos",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    870.0,
    300.0,
    anchor="nw",
    text="Terminal",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    375.0,
    300.0,
    anchor="nw",
    text="Configuración Movimiento Lineal",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    318.0,
    372.0,
    anchor="nw",
    text="Eje X",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    318.0,
    437.0,
    anchor="nw",
    text="Eje Y",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    318.0,
    502.0,
    anchor="nw",
    text="Eje Z",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    318.0,
    567.0,
    anchor="nw",
    text="Velocidad",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

button_image_3 = PhotoImage(
    file=relative_to_assets("button_3.png"))
button_3 = Button(
    image=button_image_3,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_3_clicked(),
    relief="flat"
)
button_3.place(
    x=92.0,
    y=358.0,
    width=146.0,
    height=64.0
)

button_image_4 = PhotoImage(
    file=relative_to_assets("button_4.png"))
button_4 = Button(
    image=button_image_4,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_4_clicked(),
    relief="flat"
)
button_4.place(
    x=92.0,
    y=448.0,
    width=146.0,
    height=64.0
)

button_image_5 = PhotoImage(
    file=relative_to_assets("button_5.png"))
button_5 = Button(
    image=button_image_5,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_5_clicked(),
    relief="flat"
)
button_5.place(
    x=92.0,
    y=538.0,
    width=146.0,
    height=64.0
)

canvas.create_rectangle(
    328.0,
    80.0,
    466.0,
    245.0,
    fill="#CCCBCB",
    outline="")

canvas.create_rectangle(
    480.0,
    80.0,
    618.0,
    245.0,
    fill="#CCCBCB",
    outline="")

canvas.create_rectangle(
    632.0,
    80.0,
    770.0,
    245.0,
    fill="#CCCBCB",
    outline="")

canvas.create_rectangle(
    784.0,
    80.0,
    922.0,
    245.0,
    fill="#CCCBCB",
    outline="")

canvas.create_text(
    365.0,
    94.0,
    anchor="nw",
    text="Motores",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    530.0,
    94.0,
    anchor="nw",
    text="Modo",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    675.0,
    94.0,
    anchor="nw",
    text="Efector",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    810.0,
    94.0,
    anchor="nw",
    text="Aprendizaje",
    fill="#000000",
    font=("Inter SemiBold", 16 * -1)
)

button_image_6 = PhotoImage(
    file=relative_to_assets("button_6.png"))
button_6 = Button(
    image=button_image_6,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_6_clicked(),
    relief="flat"
)
button_6.place(
    x=341.0,
    y=126.0,
    width=112.0,
    height=49.0
)

button_image_7 = PhotoImage(
    file=relative_to_assets("button_7.png"))
button_7 = Button(
    image=button_image_7,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_7_clicked(),
    relief="flat"
)
button_7.place(
    x=493.0,
    y=126.0,
    width=112.0,
    height=49.0
)

button_image_8 = PhotoImage(
    file=relative_to_assets("button_8.png"))
button_8 = Button(
    image=button_image_8,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_8_clicked(),
    relief="flat"
)
button_8.place(
    x=493.0,
    y=185.0,
    width=112.0,
    height=49.0
)

button_image_9 = PhotoImage(
    file=relative_to_assets("button_9.png"))
button_9 = Button(
    image=button_image_9,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_9_clicked(),
    relief="flat"
)
button_9.place(
    x=982.0,
    y=62.0,
    width=105.0,
    height=80.0
)

button_image_10 = PhotoImage(
    file=relative_to_assets("button_10.png"))
button_10 = Button(
    image=button_image_10,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_10_clicked(),
    relief="flat"
)
button_10.place(
    x=982.0,
    y=182.0,
    width=105.0,
    height=80.0
)

button_image_11 = PhotoImage(
    file=relative_to_assets("button_11.png"))
button_11 = Button(
    image=button_image_11,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_11_clicked(),
    relief="flat"
)
button_11.place(
    x=564.0,
    y=451.0,
    width=105.0,
    height=69.0
)

button_image_12 = PhotoImage(
    file=relative_to_assets("button_12.png"))
button_12 = Button(
    image=button_image_12,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_12_clicked(),
    relief="flat"
)
button_12.place(
    x=1013.0,
    y=566.0,
    width=55.0,
    height=35.0
)

button_image_13 = PhotoImage(
    file=relative_to_assets("button_13.png"))
button_13 = Button(
    image=button_image_13,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_13_clicked(),
    relief="flat"
)
button_13.place(
    x=341.0,
    y=185.0,
    width=112.0,
    height=49.0
)

button_image_14 = PhotoImage(
    file=relative_to_assets("button_14.png"))
button_14 = Button(
    image=button_image_14,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_14_clicked(),
    relief="flat"
)
button_14.place(
    x=645.0,
    y=126.0,
    width=112.0,
    height=49.0
)

button_image_15 = PhotoImage(
    file=relative_to_assets("button_15.png"))
button_15 = Button(
    image=button_image_15,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_15_clicked(),
    relief="flat"
)
button_15.place(
    x=645.0,
    y=185.0,
    width=112.0,
    height=49.0
)

button_image_16 = PhotoImage(
    file=relative_to_assets("button_16.png"))
button_16 = Button(
    image=button_image_16,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_16_clicked(),
    relief="flat"
)
button_16.place(
    x=797.0,
    y=126.0,
    width=112.0,
    height=49.0
)

button_image_17 = PhotoImage(
    file=relative_to_assets("button_17.png"))
button_17 = Button(
    image=button_image_17,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: button_17_clicked(),
    relief="flat"
)
button_17.place(
    x=797.0,
    y=185.0,
    width=112.0,
    height=49.0
)

entry1_validator = window.register(validate_entry1_input)
entry4_validator = window.register(validate_entry4_input)
entry5_validator = window.register(validate_entry5_input)
entry6_validator = window.register(validate_entry6_input)

entry_image_1 = PhotoImage(
    file=relative_to_assets("entry_1.png"))
entry_bg_1 = canvas.create_image(
    481.0,
    381.5,
    image=entry_image_1
)
entry_1 = Entry(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0,
    justify="center",
    validate="key",
    validatecommand=(entry1_validator, "%P")
)
entry_1.place(
    x=428.0,
    y=364.0,
    width=106.0,
    height=33.0
)

entry_image_2 = PhotoImage(
    file=relative_to_assets("entry_2.png"))
entry_bg_2 = canvas.create_image(
    874.5,
    583.5,
    image=entry_image_2
)
entry_2 = Entry(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0
)
entry_2.place(
    x=740.0,
    y=566.0,
    width=269.0,
    height=33.0
)

# Bind the update_entry_2_value function to the entry_2 widget
entry_2.bind("<KeyRelease>", update_entry_2_value)

entry_image_3 = PhotoImage(
    file=relative_to_assets("entry_3.png"))
entry_bg_3 = canvas.create_image(
    902.0,
    451.5,
    image=entry_image_3
)

entry_3 = Text(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0,
    state="disabled"  # Set the state to disabled to make it read-only
)
entry_3.place(
    x=740.0,
    y=357.0,
    width=324.0,
    height=187.0
)

custom_text = """Estas son las trayectorias precargadas para elmodo automático. Por favor indique cuál quiereejecutar y presione "Enviar" antes de 
presionar el botón "Ejecutar Trayectoria".

.txt
tray_001.txt
tray_02.txt
Tray_01.txt

De igual forma, si quiere encender el modo 
aprendizaje, indique primero el nombre del 
archivo a generar y presione "Enviar".
"""

# Usage example to display custom text
set_custom_read_only_text(custom_text)

entry_image_4 = PhotoImage(
    file=relative_to_assets("entry_4.png"))
entry_bg_4 = canvas.create_image(
    481.0,
    446.5,
    image=entry_image_4
)
entry_4 = Entry(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0,
    justify="center",
    validate="key",
    validatecommand=(entry4_validator, "%P")
)
entry_4.place(
    x=428.0,
    y=429.0,
    width=106.0,
    height=33.0
)

entry_image_5 = PhotoImage(
    file=relative_to_assets("entry_5.png"))
entry_bg_5 = canvas.create_image(
    481.0,
    511.5,
    image=entry_image_5
)
entry_5 = Entry(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0,
    justify="center",
    validate="key",
    validatecommand=(entry5_validator, "%P")
)
entry_5.place(
    x=428.0,
    y=494.0,
    width=106.0,
    height=33.0
)

entry_image_6 = PhotoImage(
    file=relative_to_assets("entry_6.png"))
entry_bg_6 = canvas.create_image(
    481.0,
    576.5,
    image=entry_image_6
)
entry_6 = Entry(
    bd=0,
    bg="#D9D9D9",
    fg="#000716",
    highlightthickness=0,
    justify="center",
    validate="key",
    validatecommand=(entry6_validator, "%P")
)
entry_6.place(
    x=428.0,
    y=559.0,
    width=106.0,
    height=33.0
)

canvas.create_rectangle(
    547.0,
    232.0,
    549.0,
    279.0,
    fill="#666262",
    outline="")

canvas.create_rectangle(
    547.0,
    275.0,
    1036.0000915527344,
    278.97967529296875,
    fill="#666262",
    outline="")

canvas.create_rectangle(
    1035.5,
    262.0,
    1035.5,
    277.0,
    fill="#000000",
    outline="")
window.resizable(False, False)
window.mainloop()
