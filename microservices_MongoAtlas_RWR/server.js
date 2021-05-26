const express = require('express');
const app = express();

const cors = require('cors');

const connectDB = require('./DBConnection/Connection');

connectDB();
app.use(cors());
app.use(express.json({extended: false}));
// para pruebas solamente
app.use('/api/userModel', require('./Api/User'));
app.enable('trust proxy');
app.use('/api/cmmdRWR', require('./Api/CommandRWR'));

const Port = process.env.Port || 3003;

app.listen(Port, () => console.log("server started"));
