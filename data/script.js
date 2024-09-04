var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
// Init web socket when the page loads
window.addEventListener("load", onload);

function onload(event) {
  iniciarWebSocket();
}

function getLeituras() {
  websocket.send("getLeituras");
}

function iniciarWebSocket() {
  console.log("Tentando abrir coneccao com WebSocket...");
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}
// When websocket is established, call the getReadings() function
function onOpen(event) {
  console.log("Conexao estabelecida");
  getLeituras();
}

function onClose(event) {
  console.log("Conexao fechada");
  setTimeout(initWebSocket, 2000);
}

// Function that receives the message from the ESP32 with the readings
function onMessage(event) {
  console.log(event.data);
  var myObj = JSON.parse(event.data);
  document.getElementById("ethmacAddress").value  = myObj.MAC || "N/A";
  document.getElementById("ethipAddress").value  = myObj.IP || "N/A";
  document.getElementById("ethgateway").value  = myObj.Gateway || "N/A";
  document.getElementById("ethsubnet").value  = myObj.Subnet || "N/A";
  document.getElementById("ethdns").value  = myObj.DNS || "N/A";

}


function openPage(pageName, elmnt, color) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablink");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].style.backgroundColor = "";
  }
  document.getElementById(pageName).style.display = "block";
  elmnt.style.backgroundColor = color;
}

// Get the element with id="defaultOpen" and click on it
document.getElementById("defaultOpen").click();

(function () {
  'use strict';

  // Seleciona todos os formulários que desejam a validação do Bootstrap
  var forms = document.querySelectorAll('.needs-validation');

  // Faz um loop e evita o envio do formulário caso seja inválido
  Array.prototype.slice.call(forms).forEach(function (form) {
    form.addEventListener('submit', function (event) {
      if (!form.checkValidity()) {
        event.preventDefault();
        event.stopPropagation();
      }

      form.classList.add('was-validated');
    }, false);
  });
})();

function toggleWifiPass() {
  var wifiMode = document.getElementById("wifiMode").value;
  var wifiPassOP = document.getElementById("wifiPassOP");

  if (wifiMode === "wifiAccessPoint") {
    wifiPassOP.style.display = "none";
  } else {
    wifiPassOP.style.display = "block";
  }
}

function showPass() {
  var x = document.getElementById("inputWifiPass");
  if (x.type === "password") {
    x.type = "text";
  } else {
    x.type = "password";
  }
}

