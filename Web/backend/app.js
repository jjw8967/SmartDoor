const express = require('express')
const bodyParser = require('body-parser')
const fs = require('fs')

require('./db/mongo') //connect db
const notice = require('./routes/notice')
const home = require('./routes/main')

const app = express()
app.set('views',__dirname+'/views');
app.set('view engine','ejs');
app.engine('html',require('ejs').renderFile);

app.use((req, res, next) =>{
    res.header("Access-Control-Allow-Origin", "*")
    res.header('Access-Control-Allow-Methods', 'GET, PUT, POST, DELETE, OPTIONS');
    res.header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type")
    next()
})
app.use(express.static('public'));
app.use(bodyParser.urlencoded({extended: true}))
app.use(bodyParser.json())
app.use('/notice', notice)
app.use('/',home)

app.listen(8000,(err)=>{
    console.log("starting http://localhost:8000");
})


module.exports = app
