document.addEventListener("DOMContentLoaded", function () {
	$("#add-programacao").click(function () {
		$("#dialog-form").modal("show");
	});
	$("#confirm-button").click(function () {
		if (validateForm()) {
			addToList();
			resetForm();
			$("#dialog-form").modal("hide");
		} else {
			alert("Preencha todos os campos antes de confirmar.");
		}
	});

	$("#condition").change(function () {
		var selectedCondition = $(this).val();
		$(".input-container").hide();

		if (selectedCondition === "data-hora") {
			$("#date-time-picker").show();
		} else if (selectedCondition === "temperatura") {
			$("#temperature-input").show();
		} else if (selectedCondition === "humidade") {
			$("#humidity-input").show();
		}
	});

	$("#nav-click").click(function () {
		var config = $(this).text();
		window.location.replace("index.html");
		// Implemente aqui a lógica para tratar a configuração selecionada
		console.log("Botão prog " + config + " clicado");
	});

	function validateForm() {
		var selectedAction = $("#action").val();
		var selectedCondition = $("#condition").val();

		if (selectedAction === "" || selectedCondition === "") {
			return false;
		}

		if (selectedCondition === "data-hora") {
			var dateTimeValue = $("#date-time").val();
			return dateTimeValue !== "";
		} else if (selectedCondition === "temperatura") {
			var temperatureValue = $("#temperature").val();
			return temperatureValue !== "";
		} else if (selectedCondition === "humidade") {
			var humidityValue = $("#humidity").val();
			return humidityValue !== "";
		}

		return true;
	}

	function addToList() {
		var selectedActionText = $("#action option:selected").text();
		var selectedActionValue = $("#action").val();
		var selectedConditionText = $("#condition option:selected").text();
		var selectedConditionValue = $("#condition").val();
		var conditionValue = "";

		if (selectedConditionValue === "data-hora") {
			conditionValue = $("#date-time").val();
		} else if (selectedConditionValue === "temperatura") {
			conditionValue = $("#temperature").val() + " °C";
		} else if (selectedConditionValue === "humidade") {
			conditionValue = $("#humidity").val() + " g/m³";
		}

		// Criar um novo item da lista
		var listItem = document.createElement("li");
		listItem.className = "list-group-item";

		// Criar o card para o item
		var card = document.createElement("div");
		card.className = "card mb-3";

		// Criar o corpo do card
		var cardBody = document.createElement("div");
        cardBody.className = "card-body d-flex justify-content-between align-items-center";

		// Adicionar conteúdo ao card
		cardBody.innerHTML =
			"<li><strong>" +
			selectedActionText +
			"</strong> com <strong>" +
			selectedConditionText +
			"</strong>: " +
			conditionValue +
			"</li>" +
            "<button class='btn btn-danger btn-sm' onclick='removeItem(this)'>Remover</button>";

		// Adicionar corpo do card ao card
		card.appendChild(cardBody);

		// Adicionar card ao item da lista
		listItem.appendChild(card);

		// Adicionar item à lista
		$("#result-list").append(listItem);
	}

	function resetForm() {
		$("#action").val("");
		$("#condition").val("");
		$(".input-container").hide();
		$("#date-time").val("");
		$("#temperature").val("");
		$("#humidity").val("");
	}
});

function removeItem(button) {
    $(button).closest(".card").remove();
  }