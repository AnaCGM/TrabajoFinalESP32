# README - Proyecto final arquitectura

## Descripción del Proyecto

Este proyecto, desarrollado por Esteban Diaz y Ana Carolina García, utiliza una ESP32 para implementar un sistema de medición de aceleración mediante un sensor de luz (fotoresistencia). El objetivo es calcular la aceleración de un objeto al caer desde una determinada altura.

## Configuración del Hardware

### Componentes Utilizados
- 2 fotoresistencias
- 2 LEDs
- ESP32

### Conexiones
- Pin 34: Conectado al primer sensor de luz (fotoresistencia)
- Pin 2: Conectado al primer LED de iluminación
- Pin 35: Conectado al segundo sensor de luz (fotoresistencia)
- Pin 16: Conectado al segundo LED de iluminación

## Funcionamiento del Código

### Configuración Inicial
El programa comienza con la configuración inicial en la función `setup()`. Se inicia la comunicación serial a 9600 baudios y se establecen los modos de los pines para los LEDs.

```cpp
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}
```

### Bucle Principal
En el bucle principal (`loop()`), se encienden los LEDs y se leen los valores de las fotoresistencias. Estos valores se mapean a un rango de 0 a 100 para representar el nivel de iluminación.

```cpp
void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);

  int analog_value1 = analogRead(fotoResistencia1);
  int iluminacion1 = map(analog_value1, 0, 4095, 0, 100);
  int analog_value2 = analogRead(fotoResistencia2);
  int iluminacion2 = map(analog_value2, 0, 4095, 0, 100);

  delay(1);
```

### Medición de Tiempo y Cálculo de Aceleración
Nota: una iluminacion de 100 significa completa oscuridad y 0 completa iluminación
Se verifica si la iluminación supera un umbral del 85% y si el tiempo de inicio (`tiempoInicio`) es cero. Si ambas condiciones se cumplen y ha pasado un tiempo mínimo de 5000 milisegundos, se inicia el contador de tiempo (`tiempoInicio`).

```cpp
  if (iluminacion1 > 85 && tiempoInicio == 0 && millis() > 5000) {
    tiempoInicio = millis();
  }
```

Si la iluminación del segundo sensor también supera el umbral y el tiempo de inicio no es cero, se calcula el tiempo transcurrido, se reinicia el contador de tiempo y se calcula la aceleración.

```cpp
  if (iluminacion2 > 85 && tiempoInicio != 0) {
    tiempoTranscurrido = (millis() - tiempoInicio);
    tiempoInicio = 0;
  }

  if (tiempoTranscurrido != 0) {
    tiempoTranscurrido /= 1000;
    aceleracion = (2 * altura) / (tiempoTranscurrido * tiempoTranscurrido);

    // Imprimir resultados en la consola serial
    Serial.print("El recorrido tomó ");
    Serial.print(tiempoTranscurrido * 1000); // muestra con 2 decimales
    Serial.println(" segundos.");
    Serial.print("La aceleración es ");
    Serial.print(aceleracion);
    Serial.println(" metros/segundos^2.");

    tiempoTranscurrido = 0;
  }
}
```

## Resultados y Conclusiones

Este proyecto proporciona una herramienta simple pero efectiva para medir la aceleración de un objeto en caída libre. Los resultados se imprimen en la consola serial, lo que permite un monitoreo detallado del tiempo de caída y la aceleración calculada.

### Nota Importante
El código asume que los sensores están correctamente calibrados y que la altura inicial es conocida. Asegúrate de ajustar estos valores según tus necesidades específicas antes de utilizar este proyecto en un entorno real.
