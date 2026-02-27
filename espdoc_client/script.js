const btnLed = document.querySelector("#btnLed");
const msgLed = document.querySelector("#msgLed");


//função que o ESP ficará chamando para atualizar o led
async function consultaStatusLed() {
    let response= await fetch("http://127.0.0.1:5050/status");
    let data = await response.json();
    return data;
};


//Atualiza o estado do botão
function atualizarStatusMsg() {
    consultaStatusLed().then(res => {
        msgLed.textContent = `Status: ${res.led}`;

        if (res.led === "ON") {
            btnLed.style.backgroundColor = "blue";
            btnLed.style.boxShadow = "1px 1px 20px blue";
        } else {
            btnLed.style.backgroundColor = "white";
            btnLed.style.color = "black";
            btnLed.style.boxShadow = "1px 1px 20px white";
        }
    });
};


//altera o estado do led (usado apenas pelo client)
async function toggleStatusLed() {
    await fetch("http://127.0.0.1:5050/toggle", {
        method: "POST"
    })

    atualizarStatusMsg();
};



///////////////////////////////////////////////////////////

atualizarStatusMsg();

btnLed.addEventListener("click", () => {
    toggleStatusLed();
});



