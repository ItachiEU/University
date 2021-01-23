const io = require('socket.io')();
const { initGame, gameLoop, getUpdatedVelocity } = require('./game');
const { FRAME_RATE } = require('./constants');
const { makeid } = require('./utiljs');
//const { displayList } = require('./index');

const state = {};
const clientRooms = {};
const roomNicknames = {};

data = [];

io.on('connection', client => {
   dataRaw = Object.keys(io.sockets.adapter.rooms);
   for (let name of dataRaw) {
      if (name.length <= 6)
         data.push(name.substr(0));
   }
   data = [...new Set(data)];
   data = data.filter(nm => dataRaw.includes(nm));

   client.on('keydown', handleKeyDown);
   client.on('newGame', handleNewGame);
   client.on('joinGame', handleJoinGame);
   client.on('showRoomList', handleShowRoomList);

   function handleShowRoomList() {
      client.emit('showRoomList', data);
   }

   function handleJoinGame(roomName, nickname) {
      const room = io.sockets.adapter.rooms[roomName];

      let allUsers;
      if (room) {
         allUsers = room.sockets;
      }
      let numClients = 0;
      if (allUsers) {
         numClients = Object.keys(allUsers).length;
      }

      if (numClients === 0) {
         client.emit('unknownGame');
         return;
      }
      else if (numClients > 1) {
         client.emit('tooManyPlayers');
         return;
      }

      clientRooms[client.id] = roomName;

      client.join(roomName);
      client.number = 2;
      client.emit('gameCode', roomName);

      var clients = io.sockets.adapter.rooms[roomName].sockets;
      for (var clientID in clients) {
         var clientSocket = io.sockets.connected[clientID];
         clientSocket.emit('gameRoomNickname', roomNicknames[roomName], nickname);
      }
      client.emit('init', 2);

      startGameInterval(roomName);
   }

   function handleNewGame(nickname) {
      let roomName = makeid(5);
      clientRooms[client.id] = roomName;
      client.emit('gameCode', roomName);

      state[roomName] = initGame();

      client.join(roomName);
      roomNicknames[roomName] = nickname;
      client.number = 1;
      client.emit('init', 1);
   }

   function handleKeyDown(keyCode) {
      const roomName = clientRooms[client.id];

      if (!roomName) {
         return;
      }

      try {
         keyCode = parseInt(keyCode);
      }
      catch (e) {
         console.log(e);
         return;
      }

      const vel = getUpdatedVelocity(keyCode);

      if (vel) {
         state[roomName]
            .players[client.number - 1]
            .vel = vel;
      }
   }
});

function startGameInterval(roomName) {
   const intervalId = setInterval(() => {
      const winner = gameLoop(state[roomName]);

      if (!winner) {
         emitGameState(roomName, state[roomName]);
      }
      else {
         emitGameOver(roomName, winner);
         state[roomName] = null;
         clearInterval(intervalId);
      }
   }, 1000/ FRAME_RATE);
}

function emitGameState(roomName, state){
   io.sockets.in(roomName)
      .emit('gameState', JSON.stringify(state));
}

function emitGameOver(roomName, winner) {
   io.sockets.in(roomName)
      .emit('gameOver', JSON.stringify({ winner }));
}

io.listen(3000);