const taskInput = document.querySelector(".task-input input");
const clearAll = document.querySelector(".clear-btn");
const taskBox = document.querySelector(".task-box");
const tasksInfo = document.querySelector('#tasks_info_span');

let todos = JSON.parse(localStorage.getItem("todo-list"));

const updateTaskMessage = () => {
   tasksInfo.innerHTML = `Tasks remaining: ${todos.reduce((accumulator, currentTask) => {
      if (currentTask.status === 'todo')
         return accumulator + 1;
      return accumulator;
   }, 0)}`;
}

const showTodo = () => {
   let liTag = "";
   updateTaskMessage();
   if(todos) {
      todos.forEach((todo, id) => {
      liTag +=`<li class="task ${todo.status == 'done' ? 'done' : 'todo'}">
                  <label for="${id}">
                    <p>${todo.name}</p>
                  </label>
                  <div>
                     <button onclick='changeStatus(${id})'>
                        ${todo.status == 'done' ? 'Revert' : 'Done'}
                     </button>
                     <button onclick='removeTask(${id})'>
                        Remove
                     </button>
                  <div>
               </li>`;
      });
   }
   taskBox.innerHTML = liTag || `<span>You don't have any tasks</span>`;
}

showTodo();

const changeStatus = (taskId) => {
   todos[taskId].status === 'done' ?
      todos[taskId].status = 'todo' :
      todos[taskId].status = 'done';
   localStorage.setItem("todo-list", JSON.stringify(todos))
   showTodo();
}

const removeTask = (deleteId) => {
   todos.splice(deleteId, 1);
   localStorage.setItem("todo-list", JSON.stringify(todos));
   showTodo();
}

const clearFunc = () => {
   todos.splice(0, todos.length);
    localStorage.setItem("todo-list", JSON.stringify(todos));
    showTodo();
}

taskInput.addEventListener("keyup", e => {
    let userTask = taskInput.value;
    if(e.key == "Enter" && userTask) {
      todos = !todos ? [] : todos;
      let taskInfo = {name: userTask, status: "todo"};
      todos.push(taskInfo);
      taskInput.value = "";
      localStorage.setItem("todo-list", JSON.stringify(todos));
      showTodo();
    }
});