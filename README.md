# Plataforma Móvil Arduino
plataforma movil arduino, open CV, Vue js, node js

## Microservicios

los microservicios requieren [node.js](https://nodejs.org/en/) y express
  
## Comunicacion 
    
   - [Socket-io](https://socket.io/), desde y hacia la plataforma movil
   - [MongoDB](https://www.mongodb.com/es/cloud/atlas), persistencia de datos 
    
  instalar todas las dependencias 

  |  | Docs |
  | ------ | ------ |
  | Express | https://expressjs.com/es/ |
  | mongoose | https://mongoosejs.com/ |
  | nodemon | https://www.npmjs.com/package/nodemon |
  | socket.io | https://socket.io/ |
  | socket.io-client | https://socket.io/docs/v3/client-api/index.html |
  | [cors] | https://www.npmjs.com/package/cors | 
  ```sh
     npm install 
  ```
  
## Despliegue Cloud
  
  ### Docker 
  
  el software es sencillo de desplegar e instalar mediante Docker
  
  ```sh
  Docker run --network host flikjo/middleware 
  ```
  
  ### AWS 
  
   Se despliega sobre un instancia EC2 (Free tier), descargando las imagenes desde [Docker-Hub](https://hub.docker.com/)
  

    
  
  

