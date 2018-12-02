const mongoose = require('mongoose')
const { DB } = require('../constants')

mongoose.Promise = global.Promise;
mongoose.connect(DB,{
    keepAlive: true,
    reconnectTries: Number.MAX_VALUE,
    useMongoClient: true   
})

mongoose.connection.on('connected', () => {
    console.info(`Running mongoose v${mongoose.version}`)
})
// Auto Increment 플러그인

module.exports = {
    mongoose
}
