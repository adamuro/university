let todos = [];
let ID = 0;

const todoInput = document.getElementById("todo-input");
const todoList = document.getElementById("todo-list");

function clearInputValue() {
  todoInput.value = "";
}

function createTodo() {
  return { id: ID++, name: todoInput.value, done: false };
}

function createTodoElement({ id, name, done }) {
  const text = document.createElement("span");
  text.textContent = name;

  const toggleButton = document.createElement("button");
  toggleButton.type = "button";
  toggleButton.textContent = done ? "Todo" : "Done";
  toggleButton.classList.add("button", "button--submit");

  const removeButton = document.createElement("button");
  removeButton.type = "button";
  removeButton.textContent = "Remove";
  removeButton.classList.add("button", "button--danger");
  removeButton.addEventListener("click", () => removeTodo(id));

  const actions = document.createElement("div");
  actions.classList.add("todo_actions");
  actions.appendChild(toggleButton);
  actions.appendChild(removeButton);

  const todo = document.createElement("li");
  todo.setAttribute("id", id);
  todo.classList.add("todo_list__item");
  if (done) todo.classList.add("todo_list__item--done");
  todo.appendChild(text);
  todo.appendChild(actions);

  return todo;
}

function addTodo() {
  clearInputValue();

  const todo = createTodo();
  const todoElement = createTodoElement(todo);

  todos.push(todo);
  todoList.appendChild(todoElement);
}

function removeTodo(id) {
  const todoElement = document.getElementById(id);

  todos = todos.filter((todo) => todo.id !== id);
  todoList.removeChild(todoElement);
}
