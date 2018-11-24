<template>
    <div id="home">
        <!--항상 상단에 떠있는 bar-->
        <header-bar></header-bar>
        <div class="body">
            <list v-for="list in lists" :key="list" v-bind:msg="list.text" v-bind:set="0" v-bind:status="list.check" ></list>
            <md-button @click="onSubmit">Submit</md-button>
        </div>
        
    </div>
</template>

<script>
    import headerBar from './header.vue'
    import list from './list.vue'

    export default {
        name: 'home',
        data: ()=>{
            return{
                lists:[]
            }
        },
        created: function(){
            this.$http.get("http://localhost:8000/notice/get").then((data)=>{
                for(let i=0;i<data.data.length;i++){
                    let value={"text":data.data[i].text,"check":data.data[i].check}
                    console.log(value)
                    this.lists.push(value)
                }
            })
        },
        components: {
            headerBar,
            list
        },
        methods:{
            onSubmit: function(){
                this.$http.post("http://localhost:8000/notice/submit").then((data)=>{
                    if(data.data=="ok")
                        alert("Success")
                    else
                        alert("Failed")
                    window.location.reload()
            })
            }
        }
    }
</script>

<style>
.body{
    text-align: center;
    padding-top:30px;
}
</style>