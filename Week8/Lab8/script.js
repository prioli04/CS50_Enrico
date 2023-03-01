window.addEventListener("load", triviaButtonClick)

let buttons = document.getElementsByClassName("triviaButton")
let submit = document.getElementById("submitPart2")

submit.addEventListener("click", inputColor)

function triviaButtonClick(){
    for (let i = 0; i < buttons.length; i++){
        buttons[i].addEventListener("click", buttonColor)
    }
}
    
function buttonColor(e){ 
    if (e.target.innerText === "91"){
        e.target.style.backgroundColor = "green"
        questionAppend("triviaQuestion", "Correct!")
    }
    else{
        e.target.style.backgroundColor = "red"
        questionAppend("triviaQuestion", "Incorrect!")
    }
    
    for (let j = 0; j < buttons.length; j++){
        removeButtonClick(buttons[j])
    }
}

function inputColor() {
    let answer = document.getElementById("input")

    if (answer.value.toLowerCase() === "interlagos") {
        answer.style.backgroundColor = "green"
        questionAppend("part2", "Correct!")
    }
    else {
        answer.style.backgroundColor = "red"
        questionAppend("part2", "Incorrect!")
    }
}

function removeButtonClick(button) {
    button.removeEventListener("click", buttonColor)
}

function questionAppend(element_id, value) {
    let question = document.getElementById(element_id)
    let idBr = question.innerHTML.indexOf("<br>")
    
    if (idBr >= 0) {
        question.innerHTML = question.innerHTML.slice(0, idBr)
    }
    
    question.innerHTML = question.innerHTML + "<br>" + value
}