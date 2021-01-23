const BG_COLOUR = "#231f20";
const SNAKE_COLOUR = "#c2c2c2";
const FOOD_COLOUR = "#e66919";

const socket = io('http://localhost:3000');

socket.on('init', handleInit);
socket.on('gameState', handleGameState);
socket.on('gameOver', handleGameOver);
socket.on('gameCode', handleGameCode);
socket.on('unknownGame', handleUnknownGame);
socket.on('tooManyPlayers', handleTooManyPlayers);
socket.on('showRoomList', displayList);
socket.on('gameRoomNickname', displayNicknames);

const gameScreen = document.getElementById('gameScreen');
const initialScreen = document.getElementById('initialScreen');
const newGameButton = document.getElementById('newGameButton');
const joinGameButton = document.getElementById('joinGameButton');
const gameCodeInput = document.getElementById('gameCodeInput');
const gameCodeDisplay = document.getElementById('gameCodeDisplay');
const showRoomListButton = document.getElementById('showRoomList');
const roomScreen = document.getElementById('roomScreen');
const nicknameInput = document.getElementById('nicknameInput');
const nicknamesDisplay = document.getElementById('nicknames');

newGameButton.addEventListener('click', newGame);
joinGameButton.addEventListener('click', joinGame);
showRoomListButton.addEventListener('click', showRoomList);

CLIENT_NICKNAME = "";

function newGame() {
   CLIENT_NICKNAME = nicknameInput.value;
   nicknamesDisplay.innerText = CLIENT_NICKNAME + " VS. "
   socket.emit('newGame', CLIENT_NICKNAME);
   init();
}

function joinGame() {
   const code = gameCodeInput.value;
   CLIENT_NICKNAME = nicknameInput.value;
   socket.emit('joinGame', code, CLIENT_NICKNAME);
   init();
}

function displayNicknames(nickname1, nickname2) {
   nicknamesDisplay.innerText = nickname1 + " VS. " + nickname2;
}

function showRoomList() {
   socket.emit('showRoomList');
}

function displayList(roomList) {
   roomScreen.innerHTML = '';
   for (let name of roomList) {
      console.log(name);
      var button = document.createElement('button' + name);
      button.type = 'submit';
      button.innerHTML = name;
      button.className = 'btn btn-dark';
      button.onclick = function () {
         CLIENT_NICKNAME = nicknameInput.value;
         socket.emit('joinGame', name, CLIENT_NICKNAME);
         init();
      }
      roomScreen.appendChild(button);
   }
}

let canvas, ctx;
let playerNumber;
let gameActive = false;

function init() {

   initialScreen.style.display = "none";
   gameScreen.style.display = "block";

   canvas = document.getElementById('canvas');
   ctx = canvas.getContext('2d');

   canvas.width = canvas.height = 600;

   ctx.fillStyle = BG_COLOUR;
   ctx.fillRect(0, 0, canvas.height, canvas.width);
   
   document.addEventListener('keydown', keydown);
   gameActive = true;
}

function keydown(e) {
   socket.emit('keydown', e.keyCode);
}

function paintGame(state) {
   ctx.fillStyle = BG_COLOUR;
   ctx.fillRect(0, 0, canvas.width, canvas.height);

   const food = state.food;
   const gridsize = state.gridsize;
   const size = canvas.width / gridsize;

   ctx.fillStyle = FOOD_COLOUR;
   ctx.fillRect(food.x * size, food.y * size, size, size);

   paintPlayer(state.players[0], size, SNAKE_COLOUR);
   paintPlayer(state.players[1], size, 'red');
}

function paintPlayer(playerState, size, colour) {
   const snake = playerState.snake;

   ctx.fillStyle = colour;
   for (let cell of snake) {
      ctx.fillRect(cell.x * size, cell.y * size, size, size);
   }
}

function handleInit(number) {
   playerNumber = number;
}

function handleGameState(gameState) {
   if (!gameActive)
      return;
   gameState = JSON.parse(gameState);
   requestAnimationFrame(() => paintGame(gameState));
}

function handleGameOver(data) {
   if (!gameActive)
      return;
   
   data = JSON.parse(data);
   if (data.winner === playerNumber) {
      alert("You win!");
   }
   else {
      alert("You lose.");
   }
   gameActive = false;
}
function handleGameCode(gameCode) {
   gameCodeDisplay.innerText = gameCode; 
}

function handleUnknownGame() {
   reset();
   alert("Unknown game code");
}

function handleTooManyPlayers() {
   reset();
   alert("This game is already in progress.");
}

function reset() {
   playerNumber = null;
   gameCodeInput.value = "";
   gameCodeDisplay.innerText = "";
   initialScreen.style.display = "block";
   gameScreen.style.display = "none";
}

//module.exports = { displayList };