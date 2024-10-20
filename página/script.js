function cargarDatos() {
  fetch("http://192.168.2.102:3000/recibir_datos")
    .then((response) => response.json())
    .then((data) => {
      console.log(data); // Imprime el objeto JSON completo para depuración

      // Accede a los datos de los sensores
      document.getElementById("sensor1").textContent = data.sensores[0];
      document.getElementById("sensor2").textContent = data.sensores[1];
      document.getElementById("sensor3").textContent = data.sensores[2];

      // Actualizar el estado de los LEDs según comandos
      actualizarLEDs(data.comandos); // Suponiendo que el campo 'commands' contiene el estado
    })
    .catch((error) => console.error("Error al cargar los datos:", error));
}

function actualizarLEDs(comandos) {
  const ledElements = [
    document.getElementById("led1"),
    document.getElementById("led2"),
    document.getElementById("led3"),
  ];

  // Reiniciar el estado de los LEDs
  ledElements.forEach((led) => {
    led.classList.remove("led-encendido");
    led.classList.add("led-apagado");
  });

  // Actualizar el estado de los LEDs según los comandos recibidos
  if (comandos[0] === "Encender primero") {
    ledElements[0].classList.remove("led-apagado");
    ledElements[0].classList.add("led-encendido-green");
  } else if (comandos[0] === "Apagar primero") {
    ledElements[0].classList.remove("led-encendido-green");
    ledElements[0].classList.add("led-apagado");
  }

  if (comandos[1] === "Encender segundo") {
    ledElements[1].classList.remove("led-apagado");
    ledElements[1].classList.add("led-encendido-yellow");
  } else if (comandos[1] === "Apagar segundo") {
    ledElements[1].classList.remove("led-encendido-yellow");
    ledElements[1].classList.add("led-apagado");
  }

  if (comandos[2] === "Encender tercero") {
    ledElements[2].classList.remove("led-apagado");
    ledElements[2].classList.add("led-encendido-red");
  } else if (comandos[2] === "Apagar tercero") {
    ledElements[2].classList.remove("led-encendido-red");
    ledElements[2].classList.add("led-apagado");
  }
}

// Cargar datos cada medio segundo
setInterval(cargarDatos, 100);
cargarDatos();
