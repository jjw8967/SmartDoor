const { mongoose} = require('../mongo')

const noticeSchema = mongoose.Schema({
    text: {type: String, unique: true},
    check: {typd: Boolean, default: false}
});


module.exports = mongoose.model("notice", noticeSchema);

