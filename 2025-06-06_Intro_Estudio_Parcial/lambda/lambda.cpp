#include <iostream>

int main() {
    int k = 10; // Parámetro fijo
    
    // Capturamos 'k' por valor (copia) y recibimos 'x' como argumento
    auto suma_k = [k](int x) { return x + k; };
    
    std::cout << suma_k(5); // Salida: 15 (5 + 10)
    return 0;
}

/* [=]: Captura todas las variables del entorno por valor (copia).

[&]: Captura todas las variables del entorno por referencia.

[var]: Captura solo var por valor.

[&var]: Captura solo var por referencia.

[this]: Captura el puntero this para acceder a miembros de una clase.

[captura](parámetros) -> tipo_retorno { cuerpo }

[captura]: Especifica qué variables del entorno exterior se pueden usar dentro de la lambda.

(parámetros): Los argumentos que recibe la función (opcional si no se necesitan).

-> tipo_retorno (opcional): El tipo de retorno (puede omitirse si se infiere).

{ cuerpo }: El código que ejecuta la lambda. */