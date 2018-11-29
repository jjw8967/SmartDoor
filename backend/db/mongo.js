const mongoose = require('mongoose')
const { DB } = require('../constants')


mongoose.connect(DB,{useNewUrlParser: true})
mongoose.connection.on('connected', () => {
    console.info(`Running mongoose v${mongoose.version}`)
})
// Auto Increment 플러그인

module.exports = {
    mongoose
}
