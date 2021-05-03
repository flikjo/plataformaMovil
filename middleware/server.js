const app = require('express')();
const http = require('http').Server(app);
const io = require('socket.io')(http, {
    
    // cors = habilitos las direcciones que van a acceder al servidor
    cors: {
        origin: "http://localhost:3000",
        origin: "http://localhost:3001",
        origin: "http://localhost:3002",
        origin: "http://localhost:3003",
        methods: ["GET", "POST"],
        allowedHeaders: ["my-custom-header"],
        credentials: true
    },
});

const mongo = require('mongodb').MongoClient;
const express = require('express');

const logs = require('./Api/Command');
const connectDB = require('./DBConnection/Connection');
const URI = require('./DBConnection/Connection');


connectDB();

app.use(express.json({extended: false}));
app.enable('trust proxy');

const promesa = mongo.connect("mongodb+srv://root:sasa@testcluster.hznq8.mongodb.net/myFirstDatabase?retryWrites=true&w=majority", { useNewUrlParser: true, useUnifiedTopology: true });

io.on('connection', (socket) => {
    let stream = undefined;
    console.log('microservice conected');

    promesa.then(client => {
       
        // Select DB and Collection
        const db = client.db("myFirstDatabase")
        const collection = db.collection("logs");
        pipeline = [  /* filters */  ];
        // Define change stream
        const changeStream = collection.watch(pipeline);
      
        changeStream.on("change", function(event) {
            switch (event.operationType) {
                case "insert":

                    stream = { 
                        ip_origen: event.fullDocument.ip_origin,
                        comando: event.fullDocument.command,
                        fecha: event.fullDocument.date
                    }
                    socket.emit('respuesta', stream);
                break;
                
                case "delete":
                    console.log("se elimino algo");
                break
            }
            
        });
    });

    socket.on('message', msg => {
        console.log(msg);
        logs(msg);
        
    });  

    socket.on('ArduinoMessage', msg => {
        console.log(msg);
        const Ard_response = {
            ip_origin: msg.ip_origin,
            commadn: msg.command,
            date: new Date()
        }
        logs(Ard_response);
        
    });

    socket.on('disconnect', (msg) => {
        console.log('microservice disconected');
    })

    /*************************************/
    socket.on('connection', (data)=>{
        console.log(data);
    });

});



http.listen(3009, () => {
    console.log('listening on *:3009');
});


