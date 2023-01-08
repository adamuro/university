import { evaluate } from "mathjs";
import "./styles.css";

const expressionElement = document.getElementById("expression") as HTMLElement;
expressionElement.innerText = "";

bindEventListeners();

function bindEventListeners() {
  const buttons = document.getElementsByClassName("button") as HTMLCollectionOf<HTMLButtonElement>;

  Array.from(buttons).forEach((button) => {
    button.addEventListener("click", () => evalClick(button));
  });
}

function evalClick(button: HTMLButtonElement) {
  if (button.textContent === "DEL") return deleteExpressionLastCharacter();
  if (button.textContent === "AC") return clearExpression();
  if (button.textContent === "=") return evaluateExpression();
  appendToExpression(button.textContent!);
}

function deleteExpressionLastCharacter() {
  if (expressionElement.textContent?.length)
    expressionElement.textContent = expressionElement.textContent.slice(0, -1);
}

function clearExpression() {
  expressionElement.textContent = "";
}

function evaluateExpression() {
  try {
    expressionElement.textContent = evaluate(expressionElement.textContent || "0");
  } catch (e) {
    expressionElement.textContent = "Error";
  }
}

function appendToExpression(character: string) {
  expressionElement.textContent += character;
}
