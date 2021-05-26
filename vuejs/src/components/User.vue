<template lang="html">
  <div class="users">
    <div>
      <h1>LOGOS</h1>
    </div>
    <div>
      <b-card no-body>
        <b-tabs pills card vertical>
          <b-tab title="Control" active><b-card-text>
            <div class="div1">
              <canvas class="canvas1" id="myCanvas" width="500" height="500"></canvas>
            </div>
            <div class="div1">
              <b-button v-on:click="izquierda" class="btn1" pill variant="primary"><b-icon icon="caret-left-square" scale="1"></b-icon></b-button>
              <b-button v-on:click="arriba" class="btn2" pill variant="primary"><b-icon icon="caret-up-square" scale="1"></b-icon></b-button>
              <b-button v-on:click="abajo" class="btn3" pill variant="primary"><b-icon icon="caret-down-square" scale="1"></b-icon></b-button>
              <b-button v-on:click="derecha" class="btn4" pill variant="primary"><b-icon icon="caret-right-square" scale="1"></b-icon></b-button>
            </div>
          </b-card-text></b-tab>
          <b-tab title="Movimientos"><b-card-text>
            <table class="table">
              <thead>
                <tr>
                  <th scope="col">#</th>
                  <th scope="col">IP</th>
                  <th scope="col">Movimiento</th>
                  <th scope="col">Fecha</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="log in logs" :key="logs._id">
                  <th scope="row">0</th>
                  <td>{{log.ip_origin}}</td>
                  <td>{{log.command}}</td>
                  <td>{{log.date}}</td>
                </tr>
              </tbody>
            </table>
                        
          </b-card-text></b-tab>
        </b-tabs>
      </b-card>
    </div>
  </div>
</template>
<script>

import axios from "axios";

export default {
  data () {
    return {
      logs: [],
      baseURL: 'http://localhost:3000',
      page: 1,
      perPage: 10,
      pages: [],
      xinicio: 250,
      xfinal: 250,
      yinicio: 250,
      yfinal: 250,
      
    }
  },
  created() {
    this.getLogs();
  },
  

  methods: {
    
    izquierda: function () {
      var a = document.getElementById("myCanvas");
      var atx = a.getContext("2d");
      atx.moveTo(this.xfinal, this.yfinal);
      this.xfinal=this.xfinal-50;
      this.yfinal=this.yfinal;
      atx.lineTo(this.xfinal, this.yfinal);
      atx.stroke();
      console.log("x Final ="+ this.xfinal + "y Final ="+ this.yfinal)
      const cmmd_frw = {
          command: 'leftward',
          date: new Date(),
          ip_origin: "182.1.6.59",
      }

      const headers = { "Access-Control-Allow-Origin": 'http://localhost:3002/api/cmmdLWR' }

      axios.post("http://localhost:3002/api/cmmdLWR", cmmd_frw, {headers}).then((result) => {
              console.log(result);
            });
    },
    arriba: function () {
      var a = document.getElementById("myCanvas");
      var atx = a.getContext("2d");
      atx.moveTo(this.xfinal, this.yfinal);
      this.xfinal=this.xfinal;
      this.yfinal=this.yfinal-50;
      atx.lineTo(this.xfinal, this.yfinal);
      atx.stroke();
      console.log("x Final ="+ this.xfinal + "y Final ="+ this.yfinal)

      const cmmd_frw = {
          command: 'forward',
          date: new Date(),
          ip_origin: "82.10.69.158",
      }

      const headers = { "Access-Control-Allow-Origin": 'http://localhost:3001/api/cmmdFRW' }

      axios.post("http://localhost:3001/api/cmmdFRW", cmmd_frw, {headers}).then((result) => {
              console.log(result);
            });

    },
    abajo: function () {
      var a = document.getElementById("myCanvas");
      var atx = a.getContext("2d");
      atx.moveTo(this.xfinal, this.yfinal);
      this.xfinal=this.xfinal;
      this.yfinal=this.yfinal+50;
      atx.lineTo(this.xfinal, this.yfinal);
      atx.stroke();
      console.log("x Final ="+ this.xfinal + "y Final ="+ this.yfinal)

      const cmmd_frw = {
          command: 'backward',
          date: new Date(),
          ip_origin: "175.2.7.60",
      }

      const headers = { "Access-Control-Allow-Origin": 'http://localhost:3000/api/cmmdBWR' }

      axios.post("http://localhost:3000/api/cmmdBWR", cmmd_frw, {headers}).then((result) => {
              console.log(result);
            });
    },
    derecha: function () {
      var a = document.getElementById("myCanvas");
      var atx = a.getContext("2d");
      atx.moveTo(this.xfinal, this.yfinal);
      this.xfinal=this.xfinal+50;
      this.yfinal=this.yfinal;
      atx.lineTo(this.xfinal, this.yfinal);
      atx.stroke();
      console.log("x Final ="+ this.xfinal + "y Final ="+ this.yfinal) 
      const cmmd_frw = {
          command: 'rightward',
          date: new Date(),
          ip_origin: "182.1.6.59",
      }

      const headers = { "Access-Control-Allow-Origin": 'http://localhost:3003/api/cmmdRWR' }

      axios.post("http://localhost:3003/api/cmmdRWR", cmmd_frw, {headers}).then((result) => {
              console.log(result);
            });
    },
    addUser(e) {
      e.preventDefault();
      console.log('agregando')
    },
    async getLogs () {
      const res = await this.axios.get(`${this.baseURL}/logs`);
      this.logs = res.data.logs;
    }
  }
}
  
</script>

<style lang="css">
  .users {
    background: #21252970;
    color: #fff;
    padding: 0 75px 0 75px;
    width: 90%;
    height: 782px;
    margin: auto;
    display: block;
  }

  a{
    color: #000;
  }
  .nav-pills .nav-link.active{
    color: #fff;
    background-color: #ff070775;
  }
  .btn1{
    margin: 10px 10px 10px 10px;
  }
  .btn2{
    margin: 10px 10px 10px 10px;
  }
  .btn3{
    margin: 10px 10px 10px 10px;
  }
  .btn4{
    margin: 10px 10px 10px 10px;
  }
  .div1{
    border-width: 2px;
    border-style: solid;
    border-color: black;
    width: 69%;
    margin: auto;
  }
  .canvas1{
    padding-top: 59px;
  }
</style>
