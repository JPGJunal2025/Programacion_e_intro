import pandas as pd
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas
from reportlab.lib.units import inch

# Datos de la tabla
data = [
    ["bool", "1 bit (usualmente 8)", "true (1) o false (0)", "Lógico"],
    ["char", "8 bits", "-128 a 127 / 0 a 255", "Entero (carácter)"],
    ["short", "16 bits", "-32,768 a 32,767", "Entero"],
    ["unsigned short", "16 bits", "0 a 65,535", "Entero"],
    ["int", "32 bits", "-2,147,483,648 a 2,147,483,647", "Entero"],
    ["unsigned int", "32 bits", "0 a 4,294,967,295", "Entero"],
    ["long", "32 o 64 bits*", "Depende del sistema", "Entero"],
    ["unsigned long", "32 o 64 bits*", "Igual que long sin negativos", "Entero"],
    ["long long", "64 bits", "-2^63 a 2^63 - 1", "Entero"],
    ["unsigned long long", "64 bits", "0 a 2^64 - 1", "Entero"],
    ["float", "32 bits", "±1.2e-38 a ±3.4e38", "Flotante"],
    ["double", "64 bits", "±2.3e-308 a ±1.7e308", "Flotante"],
    ["long double", "80/96/128 bits†", "Depende del compilador", "Flotante"]
]


columns = ["Tipo de dato", "Tamaño típico", "Rango aproximado", "Categoría"]

df = pd.DataFrame(data, columns=columns)

# Crear PDF
def export_to_pdf(dataframe, filename):
    c = canvas.Canvas(filename, pagesize=letter)
    width, height = letter
    c.setFont("Helvetica", 10)

    margin = 0.5 * inch
    y = height - margin
    line_height = 14

    c.drawString(margin, y, "Tabla de tipos de datos en C++ (ordenados de menor a mayor por tamaño/rango)")
    y -= line_height * 2

    # Encabezados
    for col_index, column in enumerate(dataframe.columns):
        c.drawString(margin + col_index * 2.2 * inch, y, column)
    y -= line_height

    # Filas
    for _, row in dataframe.iterrows():
        for col_index, item in enumerate(row):
            c.drawString(margin + col_index * 2.2 * inch, y, str(item))
        y -= line_height
        if y < margin:
            c.showPage()
            y = height - margin

    c.save()

export_to_pdf(df, "tipos_de_datos_cpp.pdf")
