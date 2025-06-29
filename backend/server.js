const express = require('express');
const cors = require('cors');
const path = require('path');

const app = express();
const port = 3000;

app.use(cors());
app.use(express.static(path.join(__dirname, '../frontend')));

// Initial states for 4 relays
let relays = {
  1: 'off',
  2: 'off',
  3: 'off',
  4: 'off'
};

// Get current status
app.get('/status', (req, res) => {
  res.json(relays);
});

// Toggle specific relay
app.get('/toggle/:id', (req, res) => {
  const id = parseInt(req.params.id);

  if (relays[id]) {
    relays[id] = relays[id] === 'on' ? 'off' : 'on';
    res.send(`Relay ${id} is now ${relays[id]}`);
  } else {
    res.status(400).send('Invalid Relay ID');
  }
});

app.listen(port, () => {
  console.log(`Server running at http://192.168.250.172:${port}`);
});