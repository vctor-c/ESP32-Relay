var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
// Init web socket when the page loads
window.addEventListener("load", onload);

document.getElementById("formEth").addEventListener("submit", envioEth);
function envioEth(event) {
  event.preventDefault();
  var escritaEth = {
    ethMac: document.getElementById("ethmacAddress").value,
    ethIP: document.getElementById("ethipAddress").value,
    ethGateway: document.getElementById("ethgateway").value,
    ethSubnet: document.getElementById("ethsubnet").value,
    ethDns: document.getElementById("ethdns").value
  };
  envioJson(escritaEth)
}

document.getElementById("formProtocol").addEventListener("submit", envioProcol);
function envioProcol(event) {
  event.preventDefault();
  var escritaRelay = {
    relay1: document.getElementById("Relay1").value,
    relay2: document.getElementById("Relay2").value,
    relay3: document.getElementById("Relay3").value,
    relay4: document.getElementById("Relay4").value,
    relay5: document.getElementById("Relay5").value,
    relay6: document.getElementById("Relay6").value,
    relay7: document.getElementById("Relay7").value,
    relay8: document.getElementById("Relay8").value
  };
  envioJson(escritaRelay)
}
document.getElementById("formWifi").addEventListener("submit", envioWifi);
function envioWifi(event) {
  event.preventDefault();
  var wifiModeResult;

  if (document.getElementById("wifiMode").value === "wifiAccessPoint") {
    wifiModeResult = true;
  } else if (document.getElementById("wifiMode").value === "wifiClient") {
    wifiModeResult = false;
  }
  var escritaWifi = {
    wifiIP: document.getElementById("wifiIpAddress").value,
    wifiGateway: document.getElementById("wifiGateway").value,
    wifiSubnet: document.getElementById("wifiSubnet").value,
    wifiSSID: document.getElementById("wifiSSID").value,
    wifiPass: document.getElementById("inputWifiPass").value,
    wifiModeOP: wifiModeResult,
  };
  envioJson(escritaWifi)
}


function envioJson(jsonData) {
  // Envia o JSON via WebSocket
  if (websocket.readyState === WebSocket.OPEN) {
    websocket.send(JSON.stringify(jsonData));
    console.log("Dados enviados via WebSocket: ", jsonData);
  } else {
    console.log("Conexão WebSocket não está aberta.");
  }
}

function onload(event) {
  iniciarWebSocket();
}

function getLeituras() {
  websocket.send("getLeiturasEth");
  websocket.send("getLeiturasWifi");
  websocket.send("getLeiturasProtocol");
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
  setTimeout(iniciarWebSocket, 2000);
}

// Function that receives the message from the ESP32 with the readings
function onMessage(event) {
  console.log(event.data);
  var myObj = JSON.parse(event.data);
  switch (myObj.Leituras) {
    case "Eth":
      document.getElementById("ethmacAddress").value = myObj.EthMAC || "N/A";
      document.getElementById("ethipAddress").value = myObj.EthIP || "N/A";
      document.getElementById("ethgateway").value = myObj.EthGateway || "N/A";
      document.getElementById("ethsubnet").value = myObj.EthSubnet || "N/A";
      document.getElementById("ethdns").value = myObj.EthDNS || "N/A";
    case "Wifi":
      document.getElementById("wifiIpAddress").value = myObj.WifiIP || "N/A";
      document.getElementById("wifiGateway").value = myObj.WifiGateway || "N/A";
      document.getElementById("wifiSubnet").value = myObj.WifiSubnet || "N/A";
      document.getElementById("wifiSSID").value = myObj.WifiSSID || "N/A";
      if (myObj.WifiapMode) {
        document.getElementById("wifiMode").value = "wifiAccessPoint";
      } else {
        document.getElementById("wifiMode").value = "wifiClient";
      }
      toggleWifiPass();
    case "Protocol":
      document.getElementById("Relay1").value = myObj.Relay1 || "N/A";
      document.getElementById("Relay2").value = myObj.Relay2 || "N/A";
      document.getElementById("Relay3").value = myObj.Relay3 || "N/A";
      document.getElementById("Relay4").value = myObj.Relay4 || "N/A";
      document.getElementById("Relay5").value = myObj.Relay5 || "N/A";
      document.getElementById("Relay6").value = myObj.Relay6 || "N/A";
      document.getElementById("Relay7").value = myObj.Relay7 || "N/A";
      document.getElementById("Relay8").value = myObj.Relay8 || "N/A";
  }

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
  var wifiClienteOP = document.getElementById("wifiClientMode");

  if (wifiMode === "wifiAccessPoint") {
    wifiClienteOP.style.display = "none";
  } else {
    wifiClienteOP.style.display = "block";
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

