const express = require('express');
const router = express.Router();
const noticeModel = require('../db/models/notice')

router.get('/',function(req,res){
    noticeModel.find().then((data)=>{
        console.log(data)
        res.render('index',{
            length: data.length,
            notices : data
        })
    })

});

router.get('/setting',(req,res)=>{
    noticeModel.find().then((data)=>{
        console.log(data)
        res.render('set',{
            length: data.length,
            notices : data,
        })
    })

})

router.post("/delete",(req,res,next)=>{
    noticeModel.deleteOne(req.body).then(()=>{
        res.redirect('/setting')
    })
})

router.post("/create",(req,res,next)=>{
    console.log(req.body)
    noticeModel.create(req.body).then((data)=>{
        res.send(data)
    })
})

router.get("/get",(req,res,next)=>{
    noticeModel.find().then((data)=>{
        console.log(data)
        res.send(data)
    })
})

router.get("/submit",(req,res,next)=>{
	console.log("ok submit")
	let exec = require("child_process").exec, child;
	child = exec("~/Desktop/servo-motor/SmartDoor/app/write_door",(err,stdout,stderr)=>{
	console.log("stdout:" + stdout);
	console.log("stderr:" + stderr);
	if(err !== null)
		console.log("exec error:"+ err);
	})
	res.send("ok");

	/*
	child = exec("~/Desktop/servo-motor/SmartDoor/app/app_motor open",(err,stdout,stderr)=>{
	console.log("stdout:" + stdout);
	console.log("stderr:" + stderr);
	if(err !== null)
		console.log("exec error:"+ err);
	})

	setTimeout(()=>{
		let exec = require("child_process").exec, child;
		
		child = exec("~/Desktop/servo-motor/SmartDoor/app/app_motor close",(err,stdout,stderr)=>{
			console.log("stdout:" + stdout);
			console.log("stderr:" + stderr);
			if(err !== null)
				console.log("exec error:"+ err);
		})
		res.send("ok");	
	},3000);
		
	*/

})
module.exports = router;

/*

router.post("/delete",(req,res,next)=>{
    noticeModel.deleteOne(req.body).then(()=>{
        res.send("ok")
    })
})

router.post("/modify",(req,res,next)=>{
    noticeModel.update(req.body[0],{"text":req.body.modify}).then(()=>{
        console.log(req.body)
        res.send("ok")
    })
})

router.post("/check",(req,res,next)=>{
    noticeModel.update(req.body,{"check":true}).then(()=>{
        console.log(req.body)
        res.send("ok")
    })
})
router.post("/submit",(req,res,next)=>{
    noticeModel.find().then((data)=>{
        for(let i=0;i<data.length;i++){
            if(data[i].check=="false"){
                res.send("err")
            }
            console.log(data[i].check)
        }
        noticeModel.find().then((data)=>{
            console.log(data)
            noticeModel.updateMany(data.body,{"check":false}).then(()=>{
                res.send("ok")
            })
        })
    })
})
module.exports = router;
*/
