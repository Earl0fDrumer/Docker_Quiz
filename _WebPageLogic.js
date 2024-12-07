var Topic;
var CorrectAnswers = 0;
var IncorrectAnswers = 0;

function AnswerTracker(isCorrect) {
    if (isCorrect) {
        CorrectAnswers++;
    } else {
        IncorrectAnswers++;
    }

    document.getElementById("CorrectAnswerTracker").innerText = "Correct Answers: " + CorrectAnswers;
    document.getElementById("IncorrectAnswerTracker").innerText = "Incorrect Answers: " + IncorrectAnswers;

}

function fetchTopics() {
    fetch("http://localhost:8200/topics")
    .then((resp) => {
        if (!resp.ok) {
            throw new Error("HTTP error: ${resp.status}");
        }
        return resp.json();
    })
    .then((text) => {
        document.getElementById("topic1").innerText = text.topic1;
        document.getElementById("topic2").innerText = text.topic2;
        document.getElementById("topic3").innerText = text.topic3;
        document.getElementById("topic4").innerText = text.topic4;
    })
    .catch((error) => {
        document.getElementById("topic1").innerText = "ERROR: Double check server";
        document.getElementById("topic2").innerText = "ERROR: Double check server";
        document.getElementById("topic3").innerText = "ERROR: Double check server";
        document.getElementById("topic4").innerText = "ERROR: Double check server";
    });
}

function loadTypeList(topic) {
    Topic = topic;
    document.getElementById("ListOfTopics").style.display = "none";
    document.getElementById("ListOfQuestionTypes").style.display = "block";
}

function QuestionSelector(Type) {
    if (Type == "FIB") {
        fetch("http://localhost:8200/" + Topic + "/FIB")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            displayFIB(text);
        })
        .catch((error) => {
            displayFIB("error");
        });
    } else if (Type == "MAT") {
        fetch("http://localhost:8200/" + Topic + "/MAT")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            displayMAT(text);
        })
        .catch((error) => {
            displayMAT("error");
        });
    } else if (Type == "MC") {
        fetch("http://localhost:8200/" + Topic + "/MC")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            displayMC(text);
        })
        .catch((error) => {
            displayMC("error")
        });
    } else if(Type == "TF") {
        fetch("http://localhost:8200/" + Topic + "/TF")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            displayTF(text);
        })
        .catch((error) => {
            displayTF("error");
        });
    } else if (Type == "RandType") {
        fetch("http://localhost:8200/" + Topic + "/random")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            if (text.questionTextFIB != null) {
                displayFIB(text);
            } else if (text.questionTextMAT != null) {
                displayMAT(text);
            } else if (text.questionTextMC != null) {
                displayMC(text);
            } else if (text.questionTextTF != null) {
                displayTF(text);
            }
        })
        .catch((error) => {
            if (text.questionTextFIB != null) {
                displayFIB("error");
            } else if (text.questionTextMAT != null) {
                displayMAT("error");
            } else if (text.questionTextMC != null) {
                displayMC("error");
            } else if (text.questionTextTF != null) {
                displayTF("error");
            }
        });
    } else if (Type == "FullyRand") {
        fetch("http://localhost:8200/random")
        .then((resp) => {
            if (!resp.ok) {
                throw new Error("HTTP error: ${resp.status}");
            }
            return resp.json();
        })
        .then((text) => {
            document.getElementById("ListOfTopics").style.display = "none";

            if (text.questionTextFIB != null) {
                displayFIB(text);
            } else if (text.questionTextMAT != null) {
                displayMAT(text);
            } else if (text.questionTextMC != null) {
                displayMC(text);
            } else if (text.questionTextTF != null) {
                displayTF(text);
            }
        })
        .catch((error) => {
            document.getElementById("ListOfTopics").style.display = "none";

            if (text.questionTextFIB != null) {
                displayFIB("error");
            } else if (text.questionTextMAT != null) {
                displayMAT("error");
            } else if (text.questionTextMC != null) {
                displayMC("error");
            } else if (text.questionTextTF != null) {
                displayTF("error");
            }
        });
    }
}

function displayFIB(text) {
    document.getElementById("ListOfQuestionTypes").style.display = "none";
    document.getElementById("FIB").style.display = "block";

    if (text == "error") {
        document.getElementById("FIBQuestion").innerText = "ERROR: Double check server";
        document.getElementById("word1").innerText = "ERROR: Double check server";
        document.getElementById("word2").innerText = "ERROR: Double check server";
        document.getElementById("word3").innerText = "ERROR: Double check server";
        document.getElementById("word4").innerText = "ERROR: Double check server";
        document.getElementById("word5").innerText = "ERROR: Double check server";
    } else {    
        document.getElementById("FIBQuestion").innerText = text.questionTextFIB;
        document.getElementById("word1").innerText = text.wordBank[0];
        document.getElementById("word2").innerText = text.wordBank[1];
        document.getElementById("word3").innerText = text.wordBank[2];
        document.getElementById("word4").innerText = text.wordBank[3];
        document.getElementById("word5").innerText = text.wordBank[4];
    }
}

function displayMAT(text) {
    document.getElementById("ListOfQuestionTypes").style.display = "none";
    document.getElementById("MAT").style.display = "block";

    if (text == "error") {
        document.getElementById("MATQuestion").innerText = "ERROR: Double check server";

        document.getElementById("termA").innerText = "ERROR: Double check server";
        document.getElementById("termB").innerText = "ERROR: Double check server";
        document.getElementById("termC").innerText = "ERROR: Double check server";
        document.getElementById("termD").innerText = "ERROR: Double check server";

        var result = document.getElementsByClassName("defA");
        Array.from(result).forEach(element => {
            element.innerText = "ERROR: Double check server";
        });
        var result = document.getElementsByClassName("defB");
        Array.from(result).forEach(element => {
            element.innerText = "ERROR: Double check server";
        });
        var result = document.getElementsByClassName("defC");
        Array.from(result).forEach(element => {
            element.innerText = "ERROR: Double check server";
        });
        var result = document.getElementsByClassName("defD");
        Array.from(result).forEach(element => {
            element.innerText = "ERROR: Double check server";
        });
    } else {    
        //Display Question
        document.getElementById("MATQuestion").innerText = text.questionTextMAT;

        //Display terms
        document.getElementById("termA").innerText = text.termA;
        document.getElementById("termB").innerText = text.termB;
        document.getElementById("termC").innerText = text.termC;
        document.getElementById("termD").innerText = text.termD;

         //Display definitions for each drop down menu
         var result = document.getElementsByClassName("defA");
         Array.from(result).forEach(element => {
             element.innerText = text.definitionA;
         });
         var result = document.getElementsByClassName("defB");
         Array.from(result).forEach(element => {
             element.innerText = text.definitionB;
         });
         var result = document.getElementsByClassName("defC");
         Array.from(result).forEach(element => {
             element.innerText = text.definitionC;
         });
         var result = document.getElementsByClassName("defD");
         Array.from(result).forEach(element => {
             element.innerText = text.definitionD;
         });
    }
}

function displayMC(text) {
    document.getElementById("ListOfQuestionTypes").style.display = "none";
    document.getElementById("MC").style.display = "block";

    if (text == "error") {
        document.getElementById("MCQuestion").innerText = "ERROR: Double check server";

        document.getElementById("option1").innerText = "ERROR: Double check server";
        document.getElementById("option2").innerText = "ERROR: Double check server";
        document.getElementById("option3").innerText = "ERROR: Double check server";
        document.getElementById("option4").innerText = "ERROR: Double check server";
    } else {    
        //Display Question
        document.getElementById("MCQuestion").innerText = text.questionTextMC;

        //Display options
        document.getElementById("option1").innerText = text.optionA;
        document.getElementById("option2").innerText = text.optionB;
        document.getElementById("option3").innerText = text.optionC;
        document.getElementById("option4").innerText = text.optionD;
    }
}

function displayTF(text) {
    
    document.getElementById("ListOfQuestionTypes").style.display = "none";
    document.getElementById("TF").style.display = "block";

    if (text == "error") {
        document.getElementById("TFQuestion").innerText = "ERROR: Double check server";

        document.getElementById("trueText").innerText = "ERROR: Double check server";
        document.getElementById("falseText").innerText = "ERROR: Double check server";
    } else {    
        //Display Question
        document.getElementById("TFQuestion").innerText = text.questionTextTF;

        //Display answers
        document.getElementById("trueText").innerText = text.trueText;
        document.getElementById("falseText").innerText = text.falseText;
    }
}