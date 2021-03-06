const express = require('express');
const mongoose = require('mongoose');
const User = require('../DBConnection/User');
const route = express.Router();

const io = require('socket.io-client');
// http://localhost:3009 => direccion del servidor al cual me quiero conectar
const socket = io("http://localhost:3009");

route.post('/', async(req, res) => {
    //const{command, date, ip_origin} = req.body;
    const{date, ip_origin} = req.body;
    
    let user = {};
    user.command = "rightward";
    user.date = date;
    user.ip_origin = ip_origin;

    let cmmdRWR = new User(user);
  await  cmmdRWR.save();
  res.json(cmmdRWR);

  socket.emit('message', user);
});

module.exports = route;