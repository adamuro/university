let todos = [];
let idSequence = 0;

const todoInputElement = document.getElementById("todo-input");
const todoListElement = document.getElementById("todo-list");
const todosCountElement = document.getElementById("todo-count");

loadTodos();
updateRemainingTodosCount();

function clearTodoInputValue() {
  todoInputElement.value = "";
}

function createTodo() {
  return { id: idSequence++, name: todoInputElement.value, done: false };
}

function saveTodos() {
  const todosJson = JSON.stringify(todos);

  localStorage.setItem("todos", todosJson);
  localStorage.setItem("id", idSequence.toString());
}

function loadTodos() {
  const todosJson = localStorage.getItem("todos");

  idSequence = localStorage.getItem("id") || 0;
  todos = JSON.parse(todosJson) || [];
  todos.forEach((todo) => {
    const todoElement = createTodoElement(todo);
    todoListElement.appendChild(todoElement);
  });
}

function updateRemainingTodosCount() {
  todosCountElement.textContent = todos.filter((todo) => !todo.done).length;
}

function createTodoElement({ id, name, done }) {
  const text = document.createElement("span");
  text.classList.add("todo__text");
  text.textContent = name;

  const toggleButton = document.createElement("button");
  toggleButton.classList.add("button", `button--${done ? "edit" : "submit"}`);
  toggleButton.setAttribute("id", `${id}-toggle-btn`);
  toggleButton.addEventListener("click", () => toggleTodo(id));
  toggleButton.type = "button";
  toggleButton.textContent = done ? "Todo" : "Done";

  const removeButton = document.createElement("button");
  removeButton.addEventListener("click", () => removeTodo(id));
  removeButton.classList.add("button", "button--danger");
  removeButton.type = "button";
  removeButton.textContent = "Remove";

  const actions = document.createElement("div");
  actions.classList.add("todo__actions");
  actions.appendChild(toggleButton);
  actions.appendChild(removeButton);

  const todo = document.createElement("li");
  if (done) todo.classList.add("todo_list__item--done");
  todo.classList.add("todo_list__item");
  todo.setAttribute("id", id);
  todo.appendChild(text);
  todo.appendChild(actions);

  return todo;
}

function addTodo() {
  if (!todoInputElement.value) return;

  const todo = createTodo();
  const todoElement = createTodoElement(todo);

  todoListElement.appendChild(todoElement);
  todos.push(todo);

  clearTodoInputValue();
  updateRemainingTodosCount();
  saveTodos();
}

function removeTodo(id) {
  const todoElement = document.getElementById(id);

  todoListElement.removeChild(todoElement);
  todos = todos.filter((todo) => todo.id !== id);

  updateRemainingTodosCount();
  saveTodos();
}

function removeAllTodos() {
  todoListElement.innerHTML = "";
  todos = [];

  updateRemainingTodosCount();
  saveTodos();
}

function toggleTodo(id) {
  const todo = todos.find((todo) => todo.id === id);
  const todoElement = document.getElementById(id);
  const toggleButtonElement = document.getElementById(`${id}-toggle-btn`);

  if (todo.done) {
    toggleButtonElement.textContent = "Done";
    toggleButtonElement.classList.add("button--submit");
    toggleButtonElement.classList.remove("button--edit");
    todoElement.classList.remove("todo_list__item--done");
  } else {
    toggleButtonElement.textContent = "Todo";
    toggleButtonElement.classList.add("button--edit");
    toggleButtonElement.classList.remove("button--submit");
    todoElement.classList.add("todo_list__item--done");
  }

  todos = todos.map((todo) => (todo.id === id ? { ...todo, done: !todo.done } : todo));

  updateRemainingTodosCount();
  saveTodos();
}
