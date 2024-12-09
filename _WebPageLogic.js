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

    if (text === "error") {
        document.getElementById("FIBQuestion").innerText = "ERROR: Double check server";
        document.getElementById("word1").innerText = "ERROR: Double check server";
        document.getElementById("word2").innerText = "ERROR: Double check server";
        document.getElementById("word3").innerText = "ERROR: Double check server";
        document.getElementById("word4").innerText = "ERROR: Double check server";
        document.getElementById("word5").innerText = "ERROR: Double check server";

        // Optionally, set the values to something or leave them empty if "error"
        document.getElementById("word1").value = "";
        document.getElementById("word2").value = "";
        document.getElementById("word3").value = "";
        document.getElementById("word4").value = "";
        document.getElementById("word5").value = "";
    } else {
        document.getElementById("FIBQuestion").innerText = text.questionTextFIB;

        // Safely set each word and its value
        if (text.wordBank && text.wordBank.length > 0) {
            document.getElementById("word1").value = text.wordBank[0];
            document.getElementById("word1").innerText = text.wordBank[0];
        } else {
            document.getElementById("word1").value = "";
            document.getElementById("word1").innerText = "";
        }

        if (text.wordBank && text.wordBank.length > 1) {
            document.getElementById("word2").value = text.wordBank[1];
            document.getElementById("word2").innerText = text.wordBank[1];
        } else {
            document.getElementById("word2").value = "";
            document.getElementById("word2").innerText = "";
        }

        if (text.wordBank && text.wordBank.length > 2) {
            document.getElementById("word3").value = text.wordBank[2];
            document.getElementById("word3").innerText = text.wordBank[2];
        } else {
            document.getElementById("word3").value = "";
            document.getElementById("word3").innerText = "";
        }

        if (text.wordBank && text.wordBank.length > 3) {
            document.getElementById("word4").value = text.wordBank[3];
            document.getElementById("word4").innerText = text.wordBank[3];
        } else {
            document.getElementById("word4").value = "";
            document.getElementById("word4").innerText = "";
        }

        if (text.wordBank && text.wordBank.length > 4) {
            document.getElementById("word5").value = text.wordBank[4];
            document.getElementById("word5").innerText = text.wordBank[4];
        } else {
            document.getElementById("word5").value = "";
            document.getElementById("word5").innerText = "";
        }
    }

    const fibSubmitBtn = document.getElementById("fibSubmitBtn");
    fibSubmitBtn.onclick = function() {
        let selectedOption = document.getElementById("fibAnswerSelect").value;

        // Ensure Topic is set before fetch
        if (!Topic || Topic.length === 0) {
            alert("No topic selected.");
            return;
        }

        ConvertTopicFormat();

        fetch(`http://localhost:8200/${Topic}/FIB/validate`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ answer: selectedOption })
        })
        .then(resp => {
            if (!resp.ok) {
                throw new Error("Network response was not ok");
            }
            return resp.json();
        })
        .then(result => {
            console.log("Validation result from server:", result);
            if (result.isCorrect) {
                AnswerTracker(true);
                alert("Correct!");
            } else {
                AnswerTracker(false);
                alert("Incorrect! The correct answer is: " + result.correctAnswer);
            }
        })
        .catch(error => {
            console.error("Validation error:", error);
            alert("Error validating answer. Please try again.");
        });
    };
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

    const mcSubmitBtn = document.getElementById("mcSubmitBtn");
    mcSubmitBtn.onclick = function() {
        // Find selected radio button
        const radios = document.getElementsByName("MC");
        let selectedOption = "";
        for (let i = 0; i < radios.length; i++) {
            if (radios[i].checked) {
                selectedOption = radios[i].value; // should be 'a', 'b', 'c', or 'd'
                break;
            }
        }

        if (!selectedOption) {
            alert("Please select an answer.");
            return;
        }

        // Ensure Topic is set before fetch
        if (!Topic || Topic.length === 0) {
            alert("No topic selected.");
            return;
        }

        ConvertTopicFormat();

        fetch(`http://localhost:8200/${Topic}/MC/validate`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ answer: selectedOption })
        })
        .then(resp => {
            if (!resp.ok) {
                throw new Error("Network response was not ok");
            }
            return resp.json();
        })
        .then(result => {
            console.log("MC Validation result from server:", result);
            if (result.isCorrect) {
                AnswerTracker(true);
                alert("Correct!");
            } else {
                AnswerTracker(false);
                alert("Incorrect! The correct answer is: " + result.correctAnswer);
            }
        })
        .catch(error => {
            console.error("MC Validation error:", error);
            alert("Error validating answer. Please try again.");
        });
    };
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

function ConvertTopicFormat() {
    if (Topic == "DP")
        Topic = "DesignPatterns"
    else if (Topic == "OOD")
        Topic = "ObjectOrientedDesign"
    else if (Topic == "SE")
        Topic = "SoftwareEngineering"
    else if (Topic == "VC")
        Topic = "VersionControl"
}