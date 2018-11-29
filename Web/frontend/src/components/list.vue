<template>
    <div id='list'>
        <div>
        <md-button v-if="set==1" @click="modify=true">{{msg}}</md-button>
        <md-button v-if="set==1" @click="onClear"><md-icon>clear</md-icon></md-button>
        <md-button v-if="set==0">{{msg}}</md-button>
        <md-button v-if="set==0" @click="onCheck"><md-icon>check</md-icon></md-button>
        <span v-if="check==true||status==true">확인</span>
        </div>
        <md-dialog-prompt
      :md-active.sync="modify"
      md-title="Modify"
      v-model="text"
      md-input-maxlength="30"
      md-confirm-text="Done"
      @md-confirm="onModify"
      />

    </div>
</template>

<script>

export default{
    name : 'list',
    data : ()=>{
        return{
            modify: false,
            text: "",
            check: false,
        }
    },
    created: function(){
        this.text=this.msg
    },
    methods:{
        onClear: function(){
            console.log(this.msg)
            this.$http.post("http://localhost:8000/notice/delete",{"text":this.msg}).then((data)=>{
                console.log(this.msg+" 삭제")
                window.location.reload()
            })
        },
        onModify: function(){
            console.log(this.text)
            if(this.text!=this.msg){
                this.$http.post("http://localhost:8000/notice/modify",{"text":this.msg,"modify":this.text}).then((data)=>{
                console.log(this.text+"로 수정")
                window.location.reload()
            })
            }
        },
        onCheck: function(){
            this.$http.post("http://localhost:8000/notice/check",{"text":this.msg}).then((data)=>{
                console.log(this.text+" 확인")
                this.check=true
            })
        }
    },
    props: ['msg','set','status']
}
</script>
<style>
</style>