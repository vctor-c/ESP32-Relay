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
	var keys = Object.keys(myObj);

	for (var i = 0; i < keys.length; i++) {
		var key = keys[i];
		if (key != "velocidade") {
			$("#"+key.toString()).html(myObj[key]);
			
		}else{
			atualizarKnob(myObj[key]);
		}
	}
}

// Aguarda o carregamento completo do documento
$(document).ready(function () {
	// Função para tratar o clique no botão "Liga"
	$(".botaoLiga").click(function () {
		websocket.send("Ligar");
	});

	// Função para tratar o clique nos botões de velocidade
	$(".botaoVelocidade").click(function () {
		// Implemente aqui a lógica para alterar a velocidade do ventilador
		var velocidade = $(this).text();
		if (velocidade == 1) {
			websocket.send("Velocidade1");
		} else if (velocidade == 2) {
			websocket.send("Velocidade2");
		} else {
			websocket.send("Velocidade3");
		}
	});

	// Função para tratar o clique nos botões de configuração
	$("#Man-auto").click(function () {
		var config = $(this).text();
		if (config == "Manual"){
			$(this).html("Automatico");
		}else{
			$(this).html("Manual");
		}
		// Implemente aqui a lógica para tratar a configuração selecionada
		console.log("Botão manual " + config + " clicado");
	});
	$("#Prog").click(function () {
		var config = $(this).text();
		window.location.replace("programacao.html");
		// Implemente aqui a lógica para tratar a configuração selecionada
		console.log("Botão prog " + config + " clicado");
	});
});


$(function () {
	$(".dial").knob({
		min: 0,
		max: 100,
		angleArc: 280,
		angleOffset: 220,
		width: 250,
		height: 250,
		release: function (v) {
			atualizarVelocidade(v);
		},
	});
});

function atualizarVelocidade(v) {

	websocket.send(map(v, 0, 100, 0, 255));
}

function atualizarKnob(valor) {
	$(".dial").val(map(valor, 0, 255, 0, 100)).trigger("change");
}

function map(value, inputMin, inputMax, outputMin, outputMax) {
	return (
		((value - inputMin) * (outputMax - outputMin)) / (inputMax - inputMin) +
		outputMin
	);
}
