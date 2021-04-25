var http = require('http'); // Import Node.js core module
const cors = require('cors');
const express = require('express');
const bot = require('./botAddon/build/Release/bot.node');
const app = express();
const port = 5000;

let initialState6 = [
	[0, 1, 1, 1, 1, 0],
	[2, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 2],
	[0, 1, 1, 1, 1, 0],
];

let initialState8 = [
	[0, 1, 1, 1, 1, 1, 1, 0],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[2, 0, 0, 0, 0, 0, 0, 2],
	[0, 1, 1, 1, 1, 1, 1, 0],
];

let boardState = initialState8;

app.use(express.json());

app.use((req, res, next) => {
	res.header('Access-Control-Allow-Headers', '*');
	res.header('Access-Control-Allow-Origin', '*');
	next();
});

app.get('/', (req, res) => {
	console.log('/');
	res.send('Hello World!');
});

app.post('/humanmove', (req, res) => {
	console.log('/humanmove');
	const i = req.body.i, j = req.body.j, i2 = req.body.i2, j2 = req.body.j2;
	boardState[i2][j2] = boardState[i][j];
	boardState[i][j] = 0;
	console.log(req.body);
	console.log(boardState);
	res.status(200).send('OK');
});

app.get('/move', (req, res) => {
	console.log('/move');
	const move = bot.moveBot1(boardState, 2);
	boardState[move.i2][move.j2] = boardState[move.i][move.j];
	boardState[move.i][move.j] = 0;
	console.log(move);
	console.log(boardState);

	res.status(200).json({ i: move.i, j: move.j, i2: move.i2, j2: move.j2 });
});


app.listen(port, () => {
	console.log(`Server is listening at http://localhost:${port}`);
});
